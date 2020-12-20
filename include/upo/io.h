/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file upo/io.h
 *
 * \brief Input/Output utilities.
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

#ifndef UPO_IO_H
#define UPO_IO_H

#include <stddef.h>
#include <stdio.h>


/**
 * \brief Ignores spaces from the given input stream.
 *
 * \param stream The input stream from which ignoring spaces.
 */
void upo_io_ignore_spaces(FILE *stream);

/**
 * \brief Reads an entire line, storing it in string pointed by \c lineptr.
 *
 * \param stream The stream from which the line has to be read.
 * \param lineptr Pointer to the string where the line will be stored. If it is
 *  \c NULL, the function will allocate a buffer for containing the line, which
 *  must be freed by the client; otherwise, this parameter must point to a
 *  malloc-allocated string that will be eventually enlarged if its size does
 *  not fit the line.\n[output]
 * \param size Pointer to the size of the line; it will be updated by the
 *  function in the case \c lineptr is \c NULL or more memory has been allocated
 *  for storing the line.\n[output]
 * \return The number of read characters on success, or -1 on error.
 *
 * The resulting buffer \a *lineptr is null-terminated and includes the newline
 * char, if a newline delimiter was found.
 *
 * \pre \c stream != \c NULL
 * \pre \c lineptr != \c NULL
 * \pre \c size != \c NULL
 */
size_t upo_io_read_line(FILE *stream, char **lineptr, size_t *size);


#endif /* UPO_IO_H */
