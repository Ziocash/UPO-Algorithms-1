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
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/bst.h>
#include <upo/error.h>


static int int_compare(const void *a, const void *b);

static int check_key_list(upo_bst_key_list_t key_list, int *keys, size_t n, int lo_key, int hi_key);

static void test_min_max();
static void test_delete_min_max();
static void test_floor_ceiling();
static void test_bst_property();


int int_compare(const void *a, const void *b)
{
    const int *aa = a;
    const int *bb = b;

    return (*aa > *bb) - (*aa < *bb);
}


int check_key_list(upo_bst_key_list_t key_list, int *keys, size_t n, int lo_key, int hi_key)
{
    assert( key_list != NULL );

    int *sorted_keys = NULL;
    int *check_keys = NULL;
    size_t i = 0;
    size_t j = 0;

    sorted_keys = malloc(n*sizeof(int));
    if (sorted_keys == NULL)
    {
        perror("Unable to allocate memory for sorted keys");
        abort();
    }
    memcpy(sorted_keys, keys, n*sizeof(int));
    qsort(sorted_keys, n, sizeof(int), int_compare);

    check_keys = malloc(n*sizeof(int));
    if (check_keys == NULL)
    {
        perror("Unable to allocate memory for check keys");
        abort();
    }
    memset(check_keys, 0, n*sizeof(int));

    i = 0;
    upo_bst_key_list_node_t *pn = key_list;
    // For each returned key, find the matching BST key and mark it
    while (pn != NULL)
    {
        int *key = pn->key;

        assert( key != NULL );
        assert( *key >= lo_key && *key <= hi_key );

        for (j = 0; j < n && sorted_keys[j] < *key; ++j)
            ; // empty
        if (j < n)
        {
            // check: no duplicate in the returned list
            assert( check_keys[j] == 0 );

            check_keys[j] += 1;
        }

        pn = pn->next;
        ++i;
    }
    // Check that every BST key in the range [lo_key,hi_key] has been found in the previous loop
    for (j = 0; j < n && sorted_keys[j] <= hi_key; ++j)
    {
        if (sorted_keys[j] >= lo_key)
        {
            assert( check_keys[j] == 1 );
        }
    }

    free(check_keys);
    check_keys = NULL;
    free(sorted_keys);
    sorted_keys = NULL;

    return 1;
}

void test_min_max()
{
    int keys1[] = {4,3,2,1,0,5,6,7,8,9};
    int keys2[] = {0,1,2,3,4,5,6,7,8,9};
    int keys3[] = {9,8,7,6,5,4,3,2,1,0};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int min_key = 0;
    int max_key = 9;
    size_t n = 0;
    size_t i;
    upo_bst_t bst;
    int *key = NULL;

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    /* BST: empty tree */

    key = upo_bst_min(bst);
    assert( key == NULL );
    key = upo_bst_max(bst);
    assert( key == NULL );

    /*
     * BST:
     *         4
     *        / \
     *       3   5
     *      /     \
     *     2       6
     *    /         \
     *   1           7
     *  /             \
     * 0               8
     *                  \
     *                   9
     */

    n = sizeof keys1/sizeof keys1[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys1[i], &values[i]);
    }
    /* Search */
    key = upo_bst_min(bst);
    assert( key != NULL );
    assert( *key == min_key );
    key = upo_bst_max(bst);
    assert( key != NULL );
    assert( *key == max_key );

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *   0
     *    \
     *     1
     *      \
     *       2
     *        \
     *         3
     *          \
     *           4
     *            \
     *             5
     *              \
     *               6
     *                \
     *                 7
     *                  \
     *                   8
     *                    \
     *                     9
     */

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys2[i], &values[i]);
    }
    /* Search */
    key = upo_bst_min(bst);
    assert( key != NULL );
    assert( *key == min_key );
    key = upo_bst_max(bst);
    assert( key != NULL );
    assert( *key == max_key );

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *                     9
     *                    /
     *                   8
     *                  /
     *                 7
     *                /
     *               6
     *              /
     *             5
     *            /
     *           4
     *          /
     *         3
     *        /
     *       2
     *      /
     *     1
     *    /
     *   0
     */

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys3[i], &values[i]);
    }
    /* Search */
    key = upo_bst_min(bst);
    assert( key != NULL );
    assert( *key == min_key );
    key = upo_bst_max(bst);
    assert( key != NULL );
    assert( *key == max_key );

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}

void test_delete_min_max()
{
    int keys1[] = {4,3,2,1,0,5,6,7,8,9};
    int keys2[] = {0,1,2,3,4,5,6,7,8,9};
    int keys3[] = {9,8,7,6,5,4,3,2,1,0};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int min_key = 0;
    int max_key = 9;
    size_t n = 0;
    size_t i;
    upo_bst_t bst;
    int *key = NULL;

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    /* BST: empty tree */

    upo_bst_delete_min(bst, 0);
    key = upo_bst_min(bst);
    assert( key == NULL );
    upo_bst_delete_max(bst, 0);
    key = upo_bst_max(bst);
    assert( key == NULL );

    /*
     * BST:
     *         4
     *        / \
     *       3   5
     *      /     \
     *     2       6
     *    /         \
     *   1           7
     *  /             \
     * 0               8
     *                  \
     *                   9
     */

    n = sizeof keys1/sizeof keys1[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys1[i], &values[i]);
    }
    /* Delete & Search */
    upo_bst_delete_min(bst, 0);
    key = upo_bst_min(bst);
    assert( key != NULL );
    assert( *key != min_key );
    upo_bst_delete_max(bst, 0);
    key = upo_bst_max(bst);
    assert( key != NULL );
    assert( *key != max_key );

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *   0
     *    \
     *     1
     *      \
     *       2
     *        \
     *         3
     *          \
     *           4
     *            \
     *             5
     *              \
     *               6
     *                \
     *                 7
     *                  \
     *                   8
     *                    \
     *                     9
     */

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys2[i], &values[i]);
    }
    /* Delete & Search */
    upo_bst_delete_min(bst, 0);
    key = upo_bst_min(bst);
    assert( key != NULL );
    assert( *key != min_key );
    upo_bst_delete_max(bst, 0);
    key = upo_bst_max(bst);
    assert( key != NULL );
    assert( *key != max_key );

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *                     9
     *                    /
     *                   8
     *                  /
     *                 7
     *                /
     *               6
     *              /
     *             5
     *            /
     *           4
     *          /
     *         3
     *        /
     *       2
     *      /
     *     1
     *    /
     *   0
     */

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys3[i], &values[i]);
    }
    /* Delete & Search */
    upo_bst_delete_min(bst, 0);
    key = upo_bst_min(bst);
    assert( key != NULL );
    assert( *key != min_key );
    upo_bst_delete_max(bst, 0);
    key = upo_bst_max(bst);
    assert( key != NULL );
    assert( *key != max_key );

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}

void test_floor_ceiling()
{
    int keys[] = {8,6,4,2,0,10,12,14,16,18};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int min_key = 0;
    int mid_key = 8;
    int max_key = 18;
    int ref_key = -1;
    size_t n = 0;
    size_t i;
    upo_bst_t bst = NULL;
    int *key = NULL;

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    /* BST: empty tree */

    ref_key = min_key;
    key = upo_bst_floor(bst, &ref_key);
    assert( key == NULL );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key == NULL );

    ref_key = mid_key;
    key = upo_bst_floor(bst, &ref_key);
    assert( key == NULL );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key == NULL );

    ref_key = max_key;
    key = upo_bst_floor(bst, &ref_key);
    assert( key == NULL );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key == NULL );

    /*
     * BST:
     *         8
     *        / \
     *       6  10
     *      /     \
     *     4      12
     *    /         \
     *   2          14
     *  /             \
     * 0              16
     *                  \
     *                  18
     */

    n = sizeof keys/sizeof keys[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys[i], &values[i]);
    }

    /* Search */

    ref_key = min_key-1;
    key = upo_bst_floor(bst, &ref_key);
    assert( key == NULL );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == min_key );

    ref_key = min_key;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == min_key );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == min_key );

    ref_key = min_key+1;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == min_key );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == (min_key+2) );

    ref_key = mid_key-1;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == mid_key-2 );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == mid_key );

    ref_key = mid_key;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == mid_key );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == mid_key );

    ref_key = mid_key+1;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == mid_key );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == (mid_key+2) );

    ref_key = max_key-1;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == (max_key-2) );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == max_key );

    ref_key = max_key;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == max_key );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == max_key );

    ref_key = max_key+1;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == max_key );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key == NULL );

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}

void test_keys_range()
{
    int keys[] = {8,6,4,2,0,10,12,14,16,18};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int min_key = 0;
    int mid_key = 8;
    int max_key = 18;
    int ref_lo_key = -1;
    int ref_hi_key = -1;
    size_t n = sizeof keys/sizeof keys[0];
    size_t i;
    upo_bst_t bst = NULL;
    upo_bst_key_list_t key_list = NULL;

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    /* BST: empty tree */

    ref_lo_key = min_key;
    ref_hi_key = max_key;
    key_list = upo_bst_keys_range(bst, &ref_lo_key, &ref_hi_key);
    assert( key_list == NULL );

    ref_lo_key = min_key;
    ref_hi_key = mid_key;
    key_list = upo_bst_keys_range(bst, &ref_lo_key, &ref_hi_key);
    assert( key_list == NULL );

    ref_lo_key = mid_key;
    ref_hi_key = max_key;
    key_list = upo_bst_keys_range(bst, &ref_lo_key, &ref_hi_key);
    assert( key_list == NULL );

    key_list = upo_bst_keys(bst);
    assert( key_list == NULL );

    /*
     * BST:
     *         8
     *        / \
     *       6  10
     *      /     \
     *     4      12
     *    /         \
     *   2          14
     *  /             \
     * 0              16
     *                  \
     *                  18
     */

    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys[i], &values[i]);
    }

    /* Search */

    ref_lo_key = min_key;
    ref_hi_key = max_key;
    key_list = upo_bst_keys_range(bst, &ref_lo_key, &ref_hi_key);
    // Check the returned list
    assert( check_key_list(key_list, keys, n, ref_lo_key, ref_hi_key) );
    // Free the list
    while (key_list != NULL)
    {
        upo_bst_key_list_t old_list = key_list;
        key_list = key_list->next;
        free(old_list);
    }

    ref_lo_key = min_key;
    ref_hi_key = mid_key;
    key_list = upo_bst_keys_range(bst, &ref_lo_key, &ref_hi_key);
    // Check the returned list
    assert( check_key_list(key_list, keys, n, ref_lo_key, ref_hi_key) );
    // Free the list
    while (key_list != NULL)
    {
        upo_bst_key_list_t old_list = key_list;
        key_list = key_list->next;
        free(old_list);
    }

    ref_lo_key = mid_key;
    ref_hi_key = max_key;
    key_list = upo_bst_keys_range(bst, &ref_lo_key, &ref_hi_key);
    // Check the returned list
    assert( check_key_list(key_list, keys, n, ref_lo_key, ref_hi_key) );
    // Free the list
    while (key_list != NULL)
    {
        upo_bst_key_list_t old_list = key_list;
        key_list = key_list->next;
        free(old_list);
    }

    key_list = upo_bst_keys(bst);
    // Check the returned list
    assert( check_key_list(key_list, keys, n, INT_MIN, INT_MAX) );
    // Free the list
    while (key_list != NULL)
    {
        upo_bst_key_list_t old_list = key_list;
        key_list = key_list->next;
        free(old_list);
    }

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}

void test_bst_property()
{
    int keys1[] = {4,3,2,1,0,5,6,7,8,9};
    int keys2[] = {0,1,2,3,4,5,6,7,8,9};
    int keys3[] = {9,8,7,6,5,4,3,2,1,0};
    int keys4[] = {8,10,9};
    int keys5[] = {8,3,1,6,4,7,10,14,13};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int min_key = INT_MIN;
    int max_key = INT_MAX;
    int tmp_key;
    size_t n = 0;
    size_t i;
    upo_bst_t bst;

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    /* BST: empty tree */

    assert( upo_bst_is_bst(bst, &min_key, &max_key) );

    /*
     * BST:
     *         4
     *        / \
     *       3   5
     *      /     \
     *     2       6
     *    /         \
     *   1           7
     *  /             \
     * 0               8
     *                  \
     *                   9
     */

    n = sizeof keys1/sizeof keys1[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys1[i], &values[i]);
    }

    /* Check */
    assert( upo_bst_is_bst(bst, &min_key, &max_key) );
    /* Invalidate the BST & Check */
    tmp_key = keys1[0];
    keys1[0] = min_key;
    assert( !upo_bst_is_bst(bst, &min_key, &max_key) );
    keys1[0] = tmp_key;

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *   0
     *    \
     *     1
     *      \
     *       2
     *        \
     *         3
     *          \
     *           4
     *            \
     *             5
     *              \
     *               6
     *                \
     *                 7
     *                  \
     *                   8
     *                    \
     *                     9
     */

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys2[i], &values[i]);
    }

    /* Check */
    assert( upo_bst_is_bst(bst, &min_key, &max_key) );
    /* Invalidate the BST & Check */
    tmp_key = keys2[0];
    keys2[0] = max_key,
    assert( !upo_bst_is_bst(bst, &min_key, &max_key) );
    keys2[0] = tmp_key;

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *                     9
     *                    /
     *                   8
     *                  /
     *                 7
     *                /
     *               6
     *              /
     *             5
     *            /
     *           4
     *          /
     *         3
     *        /
     *       2
     *      /
     *     1
     *    /
     *   0
     */

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys3[i], &values[i]);
    }

    /* Check */
    assert( upo_bst_is_bst(bst, &min_key, &max_key) );
    /* Invalidate the BST & Check */
    tmp_key = keys3[0];
    keys3[0] = min_key;
    assert( !upo_bst_is_bst(bst, &min_key, &max_key) );
    keys3[0] = tmp_key;

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *         8
     *          \
     *           10
     *          /
     *         7
     */

    n = sizeof keys4/sizeof keys4[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys4[i], &values[i]);
    }

    /* Check */
    assert( upo_bst_is_bst(bst, &min_key, &max_key) );
    /* Invalidate the BST (9 -> 7) & Check */
    tmp_key = keys4[2];
    keys4[2] = 7;
    assert( !upo_bst_is_bst(bst, &min_key, &max_key) );
    keys4[2] = tmp_key;

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *         8
     *        / \
     *       3   10
     *      / \    \
     *     1   6    14
     *        / \   /
     *       4   7 13
     */

    n = sizeof keys5/sizeof keys5[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys5[i], &values[i]);
    }

    /* Check */
    assert( upo_bst_is_bst(bst, &min_key, &max_key) );
    /* Invalidate the BST (3 -> 9) & Check */
    tmp_key = keys5[1];
    keys5[1] = 9;
    assert( !upo_bst_is_bst(bst, &min_key, &max_key) );
    keys5[1] = tmp_key;
    /* Invalidate the BST (14 -> 12) & Check */
    tmp_key = keys5[7];
    keys5[7] = 12;
    assert( !upo_bst_is_bst(bst, &min_key, &max_key) );
    keys5[7] = tmp_key;

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}


int main()
{
    printf("Test case 'min/max'... ");
    fflush(stdout);
    test_min_max();
    printf("OK\n");

    printf("Test case 'delete min/max'... ");
    fflush(stdout);
    test_delete_min_max();
    printf("OK\n");

    printf("Test case 'floor/ceiling'... ");
    fflush(stdout);
    test_floor_ceiling();
    printf("OK\n");

    printf("Test case 'keys range'... ");
    fflush(stdout);
    test_keys_range();
    printf("OK\n");

    printf("Test case 'BST property'... ");
    fflush(stdout);
    test_bst_property();
    printf("OK\n");

    return 0;
}
