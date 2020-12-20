/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include "hires_timer_private.h"
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <upo/error.h>


#define UPO_HIRES_TIMER_MICROSECONDS_PER_SECOND 1e+6


upo_hires_timer_t upo_hires_timer_create()
{
    upo_hires_timer_t timer;
    timer = malloc(sizeof(struct upo_hires_timer_s));
    if (timer == NULL)
    {
        upo_throw_sys_error("Unable to allocate memory for the high-resolution timer");
    }

    /* Invalidates the timer */
    timer->start.tv_sec = timer->start.tv_usec
                        = timer->stop.tv_sec
                        = timer->stop.tv_usec
                        = -1;

    return timer;
}

void upo_hires_timer_destroy(upo_hires_timer_t timer)
{
    if (timer != NULL)
    {
        free(timer);
    }
}

void upo_hires_timer_start(upo_hires_timer_t timer)
{
    int ret;

    assert( timer != NULL );

    ret = gettimeofday(&timer->start, NULL);
    if (ret == -1)
    {
        upo_throw_sys_error("Unable to start the high-resolution timer");
    }

    timer->stop.tv_sec = timer->stop.tv_usec
                       = -1; 
}

void upo_hires_timer_stop(upo_hires_timer_t timer)
{
    assert( timer != NULL );

    if (!upo_hires_timer_is_stopped(timer))
    {
        int ret;
        ret = gettimeofday(&timer->stop, NULL);
        if (ret == -1)
        {
            upo_throw_sys_error("Unable to stop the high-resolution timer");
        }
    }
} 

int upo_hires_timer_is_started(const upo_hires_timer_t timer) 
{
    assert( timer != NULL );

    return (timer->start.tv_sec != -1 && timer->start.tv_usec != -1) ? 1 : 0;
}

int upo_hires_timer_is_stopped(const upo_hires_timer_t timer) 
{
    assert( timer != NULL );

    return (timer->stop.tv_sec != -1 && timer->stop.tv_usec != -1) ? 1 : 0;
}

double upo_hires_timer_elapsed(const upo_hires_timer_t timer)
{
    assert( timer != NULL );

    if (upo_hires_timer_is_stopped(timer))
    {
        /* The timer is stopped: returns the length of the [start,stop) interval */
        return difftime(timer->stop.tv_sec, timer->start.tv_sec)
               + difftime(timer->stop.tv_usec, timer->start.tv_usec)/UPO_HIRES_TIMER_MICROSECONDS_PER_SECOND;
    }

    if (upo_hires_timer_is_started(timer))
    {
        /* The timer isn't stopped: returns the time elapsed so far */

        struct timeval now;
        int ret;

        ret = gettimeofday(&now, NULL);
        if (ret == -1)
        {
            upo_throw_sys_error("Unable to get elapsed time for the high-resolution timer");
        }

        return difftime(now.tv_sec, timer->start.tv_sec)
               + difftime(now.tv_usec, timer->start.tv_usec)/UPO_HIRES_TIMER_MICROSECONDS_PER_SECOND;
    }

    return -1;
}
