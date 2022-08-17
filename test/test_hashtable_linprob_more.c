/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/hashtable.h>
#include <upo/error.h>


#define MAX(x,y) ((x) > (y) ? (x) : (y))


static int int_compare(const void *a, const void *b);
#ifdef UPO_DEBUG
static void int_key_value_print(void *key, void *value, void *info);
#endif // UPO_DEBUG
static void count_key_visit(void *key, void *value, void *info);

static void test_keys();
static void test_traverse();


int int_compare(const void *a, const void *b)
{
    const int *aa = a;
    const int *bb = b;

    return (*aa > *bb) - (*aa < *bb);
}

#ifdef UPO_DEBUG
void int_key_value_print(void *key, void *value, void *info)
{
    FILE *stream = info ? info : stderr;
    int *ikey = key;
    int *ivalue = value;

    if (ikey != NULL)
    {
        fprintf(stream, "Key: %d", *ikey);
    }
    else
    {
        fprintf(stream, "Key: (nil)");
    }
    fprintf(stream, " -> ");
    if (ivalue != NULL)
    {
        fprintf(stream, "Value: %d", *ivalue);
    }
    else
    {
        fprintf(stream, "Value: (nil)");
    }
    fputc('\n', stream);
}
#endif // UPO_DEBUG

void count_key_visit(void *key, void *value, void *info)
{
    size_t *counter = info;

    assert( info != NULL );

    (void) value;

    if (key != NULL)
    {
        *counter += 1;
    }
}

void test_keys()
{
    int keys1[] = {0,1,2,3,4,5,6,7,8,9};
    int keys2[] = {0,10,20,30,40,50,60,70,80,90};
    int keys3[] = {0,1,2,3,4,10,11,12,13,14};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    size_t m = MAX( MAX(sizeof keys1/sizeof keys1[0], sizeof keys1/sizeof keys2[0]), sizeof keys1/sizeof keys3[0] );
    size_t n = 0;
    size_t i = 0;
    upo_ht_linprob_t ht;
    upo_ht_key_list_t key_list;

    /* HT: empty hash table */

    ht = upo_ht_linprob_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    key_list = upo_ht_linprob_keys(ht);
    assert( key_list == NULL );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: no collision */

    ht = upo_ht_linprob_create(2*m*UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys1/sizeof keys1[0];

    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys1[i], &values[i]);
    }

    /* Keys */
    key_list = upo_ht_linprob_keys(ht);
    assert( key_list != NULL );
    /* Check that each key is in the list */
    for (i = 0; i < n; ++i)
    {
        upo_ht_key_list_node_t *node = NULL;

        for (node = key_list;
             node != NULL && int_compare(&keys1[i], node->key) != 0;
             node = node->next)
        {
            ; /* empty */
        }
        assert( node != NULL );
    }
    while (key_list != NULL)
    {
        upo_ht_key_list_t tmp = key_list;
        key_list = key_list->next;
        free(tmp);
    }

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys1[i], 0);
    }

    /* Keys */
    key_list = upo_ht_linprob_keys(ht);
    assert( key_list == NULL );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: all collisions */

    ht = upo_ht_linprob_create(m*UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys2[i], &values[i]);
    }

    /* Keys */
    key_list = upo_ht_linprob_keys(ht);
    assert( key_list != NULL );
    /* Check that each key is in the list */
    for (i = 0; i < n; ++i)
    {
        upo_ht_key_list_node_t *node = NULL;

        for (node = key_list;
             node != NULL && int_compare(&keys2[i], node->key) != 0;
             node = node->next)
        {
            ; /* empty */
        }
        assert( node != NULL );
    }
    while (key_list != NULL)
    {
        upo_ht_key_list_t tmp = key_list;
        key_list = key_list->next;
        free(tmp);
    }

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys2[i], 0);
    }

    /* Keys */
    key_list = upo_ht_linprob_keys(ht);
    assert( key_list == NULL );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: mix */

    ht = upo_ht_linprob_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys3[i], &values[i]);
    }

    /* Keys */
    key_list = upo_ht_linprob_keys(ht);
    assert( key_list != NULL );
    /* Check that each key is in the list */
    for (i = 0; i < n; ++i)
    {
        upo_ht_key_list_node_t *node = NULL;

        for (node = key_list;
             node != NULL && int_compare(&keys3[i], node->key) != 0;
             node = node->next)
        {
            ; /* empty */
        }
        assert( node != NULL );
    }
    while (key_list != NULL)
    {
        upo_ht_key_list_t tmp = key_list;
        key_list = key_list->next;
        free(tmp);
    }

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys3[i], 0);
    }

    /* Keys */
    key_list = upo_ht_linprob_keys(ht);
    assert( key_list == NULL );

    upo_ht_linprob_destroy(ht, 0);
}

void test_traverse()
{
    int keys1[] = {0,1,2,3,4,5,6,7,8,9};
    int keys2[] = {0,10,20,30,40,50,60,70,80,90};
    int keys3[] = {0,1,2,3,4,10,11,12,13,14};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    size_t m = MAX( MAX(sizeof keys1/sizeof keys1[0], sizeof keys1/sizeof keys2[0]), sizeof keys1/sizeof keys3[0] );
    size_t n = 0;
    size_t i;
    upo_ht_linprob_t ht;
    size_t key_counter = 0;

    /* HT: empty hash table */

    ht = upo_ht_linprob_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == 0 );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: no collision */

    ht = upo_ht_linprob_create(2*m*UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys1/sizeof keys1[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys1[i], &values[i]);
    }

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == n );

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys1[i], 0);
    }

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == 0 );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: all collisions */

    ht = upo_ht_linprob_create(m*UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys2[i], &values[i]);
    }

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == n );

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys2[i], 0);
    }

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == 0 );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: mix */

    ht = upo_ht_linprob_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys3[i], &values[i]);
    }

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == n );

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys3[i], 0);
    }

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == 0 );

    upo_ht_linprob_destroy(ht, 0);
}


int main()
{
    printf("Test case 'keys... ");
    fflush(stdout);
    test_keys();
    printf("OK\n");

    printf("Test case 'traverse'... ");
    fflush(stdout);
    test_traverse();
    printf("OK\n");


    return 0;
}
