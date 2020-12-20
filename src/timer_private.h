/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file timer_private.h
 *
 * \brief Private header for the Timer abstract data type.
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

#ifndef UPO_TIMER_PRIVATE_H
#define UPO_TIMER_PRIVATE_H

#include <time.h>
#include <upo/timer.h>


/**
 * \brief Implementation of the \c upo_timer_t type.
 */
struct upo_timer_s
{
    time_t start; /**< The starting time. */
    time_t stop; /**< The stopping time. */
};

/**
 * \brief Prints the given message to the standard error and abort the program.
 *
 * \param msg The message to be displayed.
 */
static void upo_timer_throw_error(const char *msg);


#endif /* UPO_TIMER_PRIVATE_H */
