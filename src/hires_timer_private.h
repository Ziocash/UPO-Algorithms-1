/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file hires_timer_private.h
 *
 * \brief Private header for the High-resolution Timer abstract data type.
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

#ifndef UPO_HIRES_TIMER_PRIVATE_H
#define UPO_HIRES_TIMER_PRIVATE_H

#include <sys/time.h>
#include <time.h>
#include <upo/hires_timer.h>

/** \brief Implementation of the \c upo_hires_timer_t type. */
struct upo_hires_timer_s
{
    struct timeval start; /**< The starting time. */
    struct timeval stop; /**< The stopping time. */
};

#endif /* UPO_HIRES_TIMER_PRIVATE_H */
