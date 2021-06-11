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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/error.h>
#include <upo/sort.h>


/* Types and global data */

#define N 9

struct item_s
{
    long id;
    char *name;
};
typedef struct item_s item_t;

static double da[] = {3.0,1.3,0.4,7.8,13.2,-1.1,6.0,-3.2,78};
static double expect_da[] = {-3.2,-1.1,0.4,1.3,3.0,6.0,7.8,13.2,78.0};
static const char *sa[] = {"The","quick","brown","fox","jumps","over","the","lazy","dog"};
static const char *expect_sa[] = {"The","brown","dog","fox","jumps","lazy","over","quick","the"};
static item_t ca[] = {{9,"john"},{8,"jane"},{7,"mary"},{6,"anthony"},{5,"stevie"},{4,"bob"},{3,"ann"},{2,"claire"},{1,"alice"}};
static item_t expect_ca[] = {{1,"alice"},{2,"claire"},{3,"ann"},{4,"bob"},{5,"stevie"},{6,"anthony"},{7,"mary"},{8,"jane"},{9,"john"}};

/* Comparators */

static int double_comparator(const void *a, const void *b);
static int string_comparator(const void *a, const void *b);
static int item_comparator(const void *a, const void *b);

/* Test cases */
void test_sort_algorithm(void (*sort)(void*,size_t,size_t,upo_sort_comparator_t));
static void test_insertion_sort();
static void test_merge_sort();
static void test_quick_sort();


int double_comparator(const void *a, const void *b)
{
    const double *aa = a;
    const double *bb = b;

    return (*aa > *bb) - (*aa < *bb);
}

int string_comparator(const void *a, const void *b)
{
    const char **aa = (const char**) a;
    const char **bb = (const char**) b;

    return strcmp(*aa, *bb);
}

int item_comparator(const void *a, const void *b)
{
    const item_t *aa = a;
    const item_t *bb = b;

    return (aa->id > bb->id) - (aa->id < bb->id);
}

void test_sort_algorithm(void (*sort)(void*,size_t,size_t,upo_sort_comparator_t))
{
    int ok = 1;
    size_t i = 0;
    double *da_clone = NULL;
    char **sa_clone = NULL;
    item_t *ca_clone = NULL;

    ok = 1;
    da_clone = malloc(N*sizeof(double));
    assert( da_clone != NULL );
    memcpy(da_clone, da, N*sizeof(double));
    sort(da_clone, N, sizeof(double), double_comparator);
    for (i = 0; i < N; ++i)
    {
        ok &= !double_comparator(&da_clone[i], &expect_da[i]);
    }
    free(da_clone);
    assert( ok );

    ok = 1;
    sa_clone = malloc(N*sizeof(char*));
    assert( sa_clone != NULL );
    memcpy(sa_clone, sa, N*sizeof(char*));
    sort(sa_clone, N, sizeof(char*), string_comparator);
    for (i = 0; i < N; ++i)
    {
        ok &= !string_comparator(&sa_clone[i], &expect_sa[i]);
    }
    free(sa_clone);
    assert( ok );

    ok = 1;
    ca_clone = malloc(N*sizeof(item_t));
    assert( ca_clone != NULL );
    memcpy(ca_clone, ca, N*sizeof(item_t));
    sort(ca_clone, N, sizeof(item_t), item_comparator);
    for (i = 0; i < N; ++i)
    {
        ok &= !item_comparator(&ca_clone[i], &expect_ca[i]);
    }
    free(ca_clone);
    assert( ok );
}

void test_insertion_sort()
{
    test_sort_algorithm(upo_insertion_sort);
}

void test_merge_sort()
{
    test_sort_algorithm(upo_merge_sort);
}

void test_quick_sort()
{
    test_sort_algorithm(upo_quick_sort);
}


int main()
{
    printf("Test case 'insertion sort'... ");
    fflush(stdout);
    test_insertion_sort();
    printf("OK\n");

    printf("Test case 'merge sort'... ");
    fflush(stdout);
    test_merge_sort();
    printf("OK\n");

    printf("Test case 'quick sort'... ");
    fflush(stdout);
    test_quick_sort();
    printf("OK\n");

    return 0;
}
