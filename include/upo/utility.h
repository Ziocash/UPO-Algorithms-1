/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file upo/utility.h
 *
 * \brief General-purpose utilities.
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

#ifndef UPO_UTILITY_H
#define UPO_UTILITY_H


#include <stddef.h>
#include <stdio.h>


/**
 * \brief Exchanges the content pointed by \a a with the one pointed by \a b.
 *
 * \param a A generic pointer.
 * \param b A generic pointer.
 * \param size The size of the data (in byte) pointed by the input pointers.
 */
void upo_swap(void *a, void *b, size_t size);


#endif /* UPO_UTILITY_H */
