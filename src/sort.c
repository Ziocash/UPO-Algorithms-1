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

    for (size_t i = 1; i < n; ++i)
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

    upo_merge_sort_rec(base, 0, n - 1, size, cmp);
}

void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    size_t mid;
    if (lo >= hi)
    {
        return;
    }
    // mid = (hi+lo)/2; //WARN: do not use this assignment as it may overflow
    mid = lo + (hi - lo) / 2;
    // Sorts left half
    upo_merge_sort_rec(base, lo, mid, size, cmp);
    // Sorts right half
    upo_merge_sort_rec(base, mid + 1, hi, size, cmp);
    // Merges results
    upo_merge_sort_merge(base, lo, mid, hi, size, cmp);
}

void upo_merge_sort_merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, upo_sort_comparator_t cmp)
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
    upo_quick_sort_rec(base, 0, n - 1, size, cmp);
}

void upo_quick_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    if (lo >= hi)
        return;
    size_t j = upo_quick_sort_partition(base, lo, hi, size, cmp);
    if (j > 0)
        upo_quick_sort_rec(base, lo, j - 1, size, cmp);
    upo_quick_sort_rec(base, j + 1, hi, size, cmp);
}

size_t upo_quick_sort_partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    size_t p = lo, i = lo, j = hi;
    unsigned char *array = base;
    while (i < j)
    {
        while ((i < hi) && (cmp(array + i * size, array + p * size) < 0))
            i++;
        while ((j > lo) && (cmp(array + j * size, array + p * size) > 0))
            j--;
        upo_swap(array + i * size, array + j * size, size);
    }
    upo_swap(array + p * size, array + j * size, size);
    return j;
}

void upo_bubble_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    unsigned char *ptr = base;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < ((n - 1) - i); j++)
        {
            if (cmp(ptr + j * size, ptr + ((j + 1) * size)) > 0)
                upo_swap(ptr + ((j + 1) * size), ptr + j * size, size);
        }
    }
}

void upo_quick_sort_median3_cutoff(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    upo_quick_sort_median3_cutoff_rec(base, 0, n - 1, size, cmp);
}

void upo_quick_sort_median3_cutoff_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    if (lo >= hi)
        return;
    if (lo + (hi - lo) <= 10)
    {
        upo_insertion_sort(base, hi + 1, size, cmp);
        return;
    }

    size_t j = upo_quick_sort_median3_cutoff_partition(base, lo, hi, size, cmp);
    if (j > 0)
        upo_quick_sort_median3_cutoff_rec(base, lo, j, size, cmp);
    upo_quick_sort_median3_cutoff_rec(base, j + 1, hi, size, cmp);
}

size_t upo_quick_sort_median3_cutoff_partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    size_t mid = lo + (hi - lo) / 2;

    unsigned char *array = base;

    if (cmp(array + hi * size, array + lo * size) < 0)
        upo_swap(array + lo * size, array + hi * size, size);
    if (cmp(array + mid * size, array + lo * size) < 0)
        upo_swap(array + lo * size, array + mid * size, size);
    if (cmp(array + mid * size, array + hi * size) < 0)
        upo_swap(array + hi * size, array + mid * size, size);

    return upo_quick_sort_partition(base, lo + 1, hi - 1, size, cmp);
}