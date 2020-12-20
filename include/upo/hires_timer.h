/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file upo/hires_timer.h
 *
 * \brief High-resolution timer abstract data type.
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

#ifndef UPO_HIRES_TIMER_H
#define UPO_HIRES_TIMER_H

/** \brief Definition of \c upo_hires_timer_t type */
typedef struct upo_hires_timer_s* upo_hires_timer_t; /* Pointer to an incomplete structure type. */


/**
 * \brief Creates a new high-resolution timer.
 *
 * \return The new timer.
 */
upo_hires_timer_t upo_hires_timer_create();

/**
 * \brief Destroy a given high-resolution timer.
 *
 * \param The timer to destroy
 */
void upo_hires_timer_destroy(upo_hires_timer_t timer);

/**
 * \brief Starts or restarts the given high-resolution timer.
 *
 * \param timer A timer.
 */
void upo_hires_timer_start(upo_hires_timer_t timer); 

/**
 * \brief Stops the given high-resolution timer.
 *
 * \param timer A timer.
 */
void upo_hires_timer_stop(upo_hires_timer_t timer); 

/**
 * \brief Tells if the given high-resolution timer is started.
 *
 * \param timer A timer.
 * \return \c 1 if the input timer is started; \c 0, otherwise.
 */
int upo_hires_timer_is_started(const upo_hires_timer_t timer); 

/**
 * \brief Tells if the given high-resolution timer is stopped.
 *
 * \param timer A timer.
 * \return \c 1 if the input timer is stopped; \c 0, otherwise.
 */
int upo_hires_timer_is_stopped(const upo_hires_timer_t timer); 

/**
 * \brief Returns the number of seconds elapsed since when the high-resolution
 *  timer has been started until the stopping time (or so far, if not stopped
 *  yet).
 *
 * \param p_timer A pointer to a timer.
 * \return the number of seconds elapsed, on success; \c a negative number, on
 *  error.
 */
double upo_hires_timer_elapsed(const upo_hires_timer_t timer); 


#endif /* UPO_HIRES_TIMER_H */
