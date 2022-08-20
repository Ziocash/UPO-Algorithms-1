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
#include <upo/hashtable.h>

upo_strings_list_t upo_find_dups(const char **strs, size_t n)
{
    if(strs == NULL)
        return NULL;
    upo_strings_list_t list = NULL;
    //upo_ht_sepchain_t table = upo_ht_sepchain_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_str_kr2e, );
    return list;
}

upo_strings_list_t upo_find_idups(const char **strs, size_t n, int ignore_case)
{
    upo_strings_list_t list = NULL;
    return list;
}

void upo_dups_create_list(upo_strings_list_t *list)
{
    
}

int main(void)
{
    upo_strings_list_t list = upo_find_dups(NULL, sizeof(NULL));
    assert(list == NULL);
    list = upo_find_idups(NULL, sizeof(NULL), 0);
    assert(list == NULL);
    list = upo_find_idups(NULL, sizeof(NULL), 1);
    assert(list == NULL);

    char *strings[] = {"Tre", "tigri", "contro", "tre", "tigri"};

    return EXIT_SUCCESS;
}