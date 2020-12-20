/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file upo/random.h
 *
 * \brief Utilities related to pseudo-random number generation.
 *
 * \author Marco Guazzone (marco.guazzone@uniupo.it)
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

#ifndef UPO_RANDOM_H
#define UPO_RANDOM_H


#include <stddef.h>


/**
 * \brief Returns a random real number uniformly distributed in the [lo,hi)
 *  range.
 *
 * \param lo The lower bound of the given real range.
 * \param hi The upper bound of the given real range.
 * \return a random real number uniformly distributed between \a lo (inclusive)
 *  and \a hi (exclusive).
 */
double upo_random_uniform_real(double lo, double hi);
 
/**
 * \brief Returns a random integer uniformly distributed in the [lo,hi) range.
 *
 * \param lo The lower bound of the given integer range.
 * \param hi The upper bound of the given integer range.
 * \return a random integer uniformly distributed between \a lo (inclusive) and
 *  \a hi (exclusive).
 */
int upo_random_uniform_int(int lo, int hi);
 
/**
 * \brief Rearranges the elements of an array in uniformly random order.
 *
 * \param base Pointer to the first entry of the input array.
 * \param n Number of entries of the input array.
 * \param size Size of each element stored in the input array.
 */
void upo_random_shuffle(void *base, size_t n, size_t size);

/**
 * \brief Fills the given string with random characters.
 *
 * \param s The string to be filled.
 * \param n The length of the string.
 *
 * The given string \a s is filled with \a n random characters taken from the
 * printable ASCII character-encoding scheme (i.e., from ' ' to '~').
 * Also, an end-of-string character is added at the end of the string (i.e., at
 * position n).
 */
char* upo_random_string(char *s, size_t n);

#endif /* UPO_RANDOM_H */
