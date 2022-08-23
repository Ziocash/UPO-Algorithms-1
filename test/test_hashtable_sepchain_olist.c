/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file test/test_hashtable_olist.c
 *
 * \brief Implementation for the hash table with ordered list testing.
 *
 * \author Simone Gattini, Federico Barbero, Anton Iliev
 *
 * \copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 *  This file is part of UPOalglib.
 *
 *  UPOalglib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  UPOalglib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/hashtable.h>
#include <upo/error.h>


#define MAX(x,y) ((x) > (y) ? (x) : (y))


static int str_compare(const void *a, const void *b);
static int int_compare(const void *a, const void *b);

static void test_create_destroy();
static void test_put_get_contains_delete();
static void test_insert_get_contains_delete();
static void test_clear();
static void test_empty();
static void test_size();
static void test_hash_funcs();
static void test_null();

int str_compare(const void *a, const void *b)
{
    const char **aa = (const char**) a;
    const char **bb = (const char**) b;

    return strcmp(*aa, *bb);
}

int int_compare(const void *a, const void *b)
{
    const int *aa = a;
    const int *bb = b;

    return (*aa > *bb) - (*aa < *bb);
}

void test_create_destroy()
{
    upo_ht_sepchain_olist_t ht;

    ht = upo_ht_sepchain_olist_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_str_kr2e, str_compare);

    assert( ht != NULL );

    upo_ht_sepchain_olist_destroy(ht, 0);

    ht = upo_ht_sepchain_olist_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_str_kr2e, str_compare);

    assert( ht != NULL );

    upo_ht_sepchain_olist_destroy(ht, 1);
}

int main(void)
{
    printf("Test case 'create/destroy'... ");
    fflush(stdout);
    test_create_destroy();
    printf("OK\n");

    return EXIT_SUCCESS;
}