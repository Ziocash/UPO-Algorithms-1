/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file upo/error.h
 *
 * \brief Error-related utilities
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

#ifndef UPO_ERROR_H
#define UPO_ERROR_H


#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * \brief Prints the given message to the standard error and abort the program.
 *
 * \param msg The error message
 */
/* This is implemented as a macro in order to keep __FILE__ and __LINE__ in
 * context */
#define upo_throw_error(msg) {\
                                assert(msg);\
                                fprintf(stderr, "[file: %s, line: %d] %s\n", __FILE__, __LINE__, msg);\
                                abort();\
                             }

/**
 * \brief Prints the error message obtained from the current value of the errno
 *  variable, together with the additional given message, to the standard error
 *  and abort the program.
 *
 * \param msg The additional error message
 */
/* This is implemented as a macro in order to keep __FILE__ and __LINE__ in
 * context */
#define upo_throw_sys_error(msg) {\
                                    const char *errstr = strerror(errno);\
                                    assert(msg);\
                                    assert(errstr);\
                                    fprintf(stderr, "[file: %s, line: %d] %s (%s)\n", __FILE__, __LINE__, msg, errstr);\
                                    abort();\
                                  }


#endif /* UPO_ERROR_H */
