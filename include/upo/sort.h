/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file upo/sort.h
 *
 * \brief Sorting algorithms.
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

#ifndef UPO_SORT_H
#define UPO_SORT_H


#include <stddef.h>


/** \brief Type definition for comparison functions used to compare two elements */
typedef int (*upo_sort_comparator_t)(const void*, const void*);


/**
 * \brief Sorts the given array according to the insertion sort algorithm.
 *
 * \param base Pointer to the start of the input array.
 * \param n Number of elements in the input array.
 * \param size The size (in bytes) of each element of the array.
 * \param cmp Pointer to the comparison function used to sort the array in
 *  ascending order.
 *  The comparison function is called with two arguments that point to the
 *  objects being compared and must return an interger less than, equal to, or
 *  greater than zero if the first argument is considered to be respectively
 *  less than, equal to, or greater than the second.
 *
 * Insertion sort uses \f$\sim n^2/4\f$ compares and \f$\sim n^2/4\f$ exchanges
 * to sort a randomly ordered array with distinct keys, on the average.
 * The worst case is \f$\sim n^2/2\f$ compares and \f$\sim n^2/2\f$ exchanges,
 * and the best case is \f$n-1\f$ compares and \f$0\f$ exchanges.
 * The time complexity of insertion sort is \f$\Theta(n^2)\f$ in the worst case.
 */
void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp);

/**
 * \brief Sorts the given array according to the merge sort algorithm.
 *
 * \param base Pointer to the start of the input array.
 * \param n Number of elements in the input array.
 * \param size The size (in bytes) of each element of the array.
 * \param cmp Pointer to the comparison function used to sort the array in
 *  ascending order.
 *  The comparison function is called with two arguments that point to the
 *  objects being compared and must return an interger less than, equal to, or
 *  greater than zero if the first argument is considered to be respectively
 *  less than, equal to, or greater than the second.
 *
 * Merge sort performs between $\frac{1}{2} n \log n$ and $n \log n$ compares
 * and at most $6n \log n$ array accesses.
 *
 */
void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp);

/**
 * \brief Sorts the given array according to the quick sort algorithm.
 *
 * \param base Pointer to the start of the input array.
 * \param n Number of elements in the input array.
 * \param size The size (in bytes) of each element of the array.
 * \param cmp Pointer to the comparison function used to sort the array in
 *  ascending order.
 *  The comparison function is called with two arguments that point to the
 *  objects being compared and must return an interger less than, equal to, or
 *  greater than zero if the first argument is considered to be respectively
 *  less than, equal to, or greater than the second.
 */
void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp);


#endif /* UPO_SORT_H */
