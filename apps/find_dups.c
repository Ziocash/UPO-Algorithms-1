/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file apps/find_dups.c
 *
 * \brief An application to find duplicates in string arrays.
 *
 * \author Simone Gattini, Federico Barbero, Anton Iliev
 *
 * \copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include "find_dups.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <upo/hashtable.h>

int str_cmp(const void *a, const void *b)
{
    const char *aa = *(char **)a;
    const char *bb = *(char **)b;

    return strcmp(aa, bb);
}

upo_strings_list_t upo_find_dups(const char **strs, size_t n)
{
    if (strs == NULL)
        return NULL;
    upo_strings_list_t list = NULL;
    upo_ht_sepchain_t table = upo_ht_sepchain_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_str_kr2e, str_cmp);
    for (size_t i = 0; i < n; i++)
    {
        char *dup = NULL;
        if ((dup = upo_ht_sepchain_put(table, &strs[i], &strs[i])) != NULL)
            upo_dups_create_list(&list, dup);
    }
    upo_ht_sepchain_destroy(table, 0);
    return list;
}

upo_strings_list_t upo_find_idups(const char **strs, size_t n, int ignore_case)
{
    if (strs == NULL)
        return NULL;
    if (!ignore_case)
        return upo_find_dups(strs, n);

    upo_strings_list_t list = NULL;
    upo_ht_sepchain_t table = upo_ht_sepchain_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_str_kr2e, str_cmp);
    size_t size = n * sizeof(char *);
    char **strs_copy = malloc(size);
    memset(strs_copy, '\0', size);
    for (size_t i = 0; i < n; i++)
    {
        strs_copy[i] = upo_to_lower_case(strs[i]);
        char *dup = NULL;
        if ((dup = upo_ht_sepchain_put(table, &strs_copy[i], &strs_copy[i])) != NULL)
            upo_dups_create_list(&list, &strs[i]);
        
    }

    for (size_t i = 0; i < n; i++)
        free(strs_copy[i]);

    upo_ht_sepchain_destroy(table, 0);
    free(strs_copy);
    return list;
}

void *upo_to_lower_case(const char *src)
{
    char *lowered = malloc(sizeof(char) * (strlen(src) + 1));
    memset(lowered, '\0', sizeof(char) * (strlen(src) + 1));
    strcpy(lowered, src);
    char *temp = lowered;
    for (; *temp; ++temp)
        *temp = tolower(*temp);
    return lowered;
}

void upo_dups_create_list(upo_strings_list_t *list, void *str)
{
    if (*list == NULL)
    {
        *list = malloc(sizeof(upo_strings_list_node_t));
        (*list)->value = str;
        (*list)->next = NULL;
    }
    else
    {
        upo_strings_list_node_t *node = (*list);
        while (node->next != NULL)
            node = node->next;
        upo_strings_list_node_t *new_node = malloc(sizeof(upo_strings_list_node_t));
        new_node->value = str;
        new_node->next = NULL;
        node->next = new_node;
    }
}

void upo_destroy_dup_list(upo_strings_list_t *list)
{
    assert(list != NULL);
    assert(*list != NULL);

    while (*list != NULL)
    {
        upo_strings_list_node_t *node = *list;
        *list = (*list)->next;
        free(node);
    }

    *list = NULL;
}

void upo_check_list(upo_strings_list_t list, const char **expected_strs)
{
    upo_strings_list_node_t *node = list;
    size_t index = 0;
    while (node != NULL)
    {
        assert(str_cmp(node->value, &expected_strs[index++]) == 0);
        node = node->next;
    }
}

int main(void)
{
    printf("Test null... ");
    upo_strings_list_t list = upo_find_dups(NULL, sizeof(NULL));
    assert(list == NULL);
    list = upo_find_idups(NULL, sizeof(NULL), 0);
    assert(list == NULL);
    list = upo_find_idups(NULL, sizeof(NULL), 1);
    assert(list == NULL);
    printf("OK\n");

    printf("Test duplicates on string array... ");
    const char *strings[] = {"Tre", "tigri", "contro", "tre", "tigri"};
    list = upo_find_dups(strings, sizeof(strings) / sizeof(char *));
    assert(list != NULL);
    const char *expected[] = {"tigri"};
    upo_check_list(list, expected);

    upo_destroy_dup_list(&list);

    assert(list == NULL);
    printf("OK\n");

    printf("Test duplicates ignoring case on string array... ");
    list = upo_find_idups(strings, sizeof(strings) / sizeof(char *), 1);
    assert(list != NULL);
    const char *ignore_case_expected[] = {"tre", "tigri"};
    upo_check_list(list, ignore_case_expected);

    upo_destroy_dup_list(&list);

    assert(list == NULL);

    list = upo_find_idups(strings, sizeof(strings) / sizeof(char *), 0);
    assert(list != NULL);
    upo_check_list(list, expected);

    upo_destroy_dup_list(&list);

    assert(list == NULL);
    printf("OK\n");

    return EXIT_SUCCESS;
}