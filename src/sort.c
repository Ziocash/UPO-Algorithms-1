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
#include "sort_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/utility.h>

void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    assert(base != NULL);
    assert(n > 0);
    assert(size > 0);
    assert(cmp != NULL);

    unsigned char *ptr = base, *current = NULL, *previous = NULL;

    for (int i = 1; i < n; ++i)
    {
        int j = i;
        while (j > 0 && cmp(ptr + j * size, ptr + (j - 1) * size) < 0)
        {
            current = ptr + j * size;
            previous = ptr + (j * size) - (1 * size);

            upo_swap(current, previous, size);
            j--;
        }
    }
}

void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    assert(base != NULL);
    assert(n > 0);
    assert(size > 0);
    assert(cmp != NULL);
    
    upo_merge_sort_driver_topdown(base, 0, n - 1, size, cmp);
}

void upo_merge_sort_driver_topdown(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    size_t mid;
    if (lo >= hi)
    {
        return;
    }
    // mid = (hi+lo)/2; //WARN: do not use this assignment as it may overflow
    mid = lo + (hi - lo) / 2;
    // Sorts left half
    upo_merge_sort_driver_topdown(base, lo, mid, size, cmp);
    // Sorts right half
    upo_merge_sort_driver_topdown(base, mid + 1, hi, size, cmp);
    // Merges results
    upo_merge(base, lo, mid, hi, size, cmp);
}

void upo_merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    unsigned char *ptr = base;
    unsigned char *aux = NULL;
    size_t n = hi - lo + 1;
    size_t i = 0;
    size_t j = mid + 1 - lo;
    size_t k;
    aux = malloc(n * size);
    if (aux == NULL)
    {
        perror("Unable to allocate memory for auxiliary vector");
        abort();
    }
    // Copy base[lo],...,base[hi] into the auxiliary array
    memcpy(aux, ptr + lo * size, n * size);
    // Merge base[lo],...,base[mid] with base[mid+1],...,base[hi].
    // Elements are read from the aux vector and written to the base vector.
    for (k = lo; k <= hi; ++k)
    {
        if (i > (mid - lo))
        {
            memcpy(ptr + k * size, aux + j * size, size);
            ++j;
        }
        else if (j > (hi - lo))
        {
            memcpy(ptr + k * size, aux + i * size, size);
            ++i;
        }
        else if (cmp(aux + j * size, aux + i * size) < 0)
        {
            memcpy(ptr + k * size, aux + j * size, size);
            ++j;
        }
        else
        {
            memcpy(ptr + k * size, aux + i * size, size);
            ++i;
        }
    }
    free(aux);
}

void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    // abort();
}
