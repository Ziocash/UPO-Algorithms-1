/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file src/sort_private.h
 *
 * \brief Private header for sorting algorithms.
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

#ifndef UPO_SORT_PRIVATE_H
#define UPO_SORT_PRIVATE_H

#include <upo/sort.h>

/* TO STUDENTS:
 *
 *  This file is currently "empty".
 *  Here you can put the prototypes of auxiliary "private" functions that are
 *  internally used by "public" functions.
 *  For instance, you can declare the prototype of the function that performs
 *  the "merge" operation in the merge-sort algorithm:
 *    static void upo_merge_sort_merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, upo_sort_comparator_t cmp);
 *  Also, you can declare the prototype of the function that performs the
 *  the recursion in the merge-sort algorithm:
 *    static void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp);
 *  Further, you can declare the prototype of the function that performs the
 *  "partition" operation in the quick-sort algorithm:
 *    static size_t upo_quick_sort_partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp);
 *  And so on.
 *
 */

static void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp);

static void upo_merge_sort_merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, upo_sort_comparator_t cmp);

static void upo_quick_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp);

static size_t upo_quick_sort_partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp);

static void upo_quick_sort_median3_cutoff_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp);

static size_t upo_quick_sort_median3_cutoff_partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp);

#endif /* UPO_SORT_PRIVATE_H */
