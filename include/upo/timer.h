/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file upo/timer.h
 *
 * \brief Timer abstract data type.
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

#ifndef UPO_TIMER_H
#define UPO_TIMER_H

/** \brief Definition of \c upo_timer_t type */
typedef struct upo_timer_s* upo_timer_t; /* Pointer to an incomplete structure type). */


/**
 * \brief Creates a new timer.
 *
 * \return The new timer.
 */
upo_timer_t upo_timer_create();

/**
 * \brief Destroy a given timer.
 *
 * \param The timer to destroy
 */
void upo_timer_destroy(upo_timer_t timer);

/**
 * \brief Starts or restarts the given timer.
 *
 * \param timer A timer.
 */
void upo_timer_start(upo_timer_t timer); 

/**
 * \brief Stops the given timer.
 *
 * \param timer A timer.
 */
void upo_timer_stop(upo_timer_t timer); 

/**
 * \brief Tells if the given timer is started.
 *
 * \param timer A timer.
 * \return \c 1 if the input timer is started; \c 0, otherwise.
 */
int upo_timer_is_started(const upo_timer_t timer); 

/**
 * \brief Tells if the given timer is stopped.
 *
 * \param timer A timer.
 * \return \c 1 if the input timer is stopped; \c 0, otherwise.
 */
int upo_timer_is_stopped(const upo_timer_t timer); 

/**
 * \brief Returns the number of seconds elapsed since when the timer has been
 *  started until the stopping time (or so far, if not stopped yet).
 *
 * \param p_timer A pointer to a timer.
 * \return the number of seconds elapsed, on success; \c a negative number, on
 *  error.
 */
double upo_timer_elapsed(const upo_timer_t timer); 


#endif /* UPO_TIMER_H */
