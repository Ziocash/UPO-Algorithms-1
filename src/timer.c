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
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "timer_private.h"


upo_timer_t upo_timer_create()
{
    upo_timer_t timer = NULL;

    timer = malloc(sizeof(struct upo_timer_s));
    if (timer == NULL)
    {
        upo_timer_throw_error(strerror(errno));
    }

    /* Invalidates the timer */
    timer->start = timer->stop = -1;

    return timer;
}

void upo_timer_destroy(upo_timer_t timer)
{
    if (timer != NULL)
    {
        free(timer);
    }
}

void upo_timer_start(upo_timer_t timer)
{
    if (timer == NULL)
    {
        upo_timer_throw_error("Invalid timer argument");
    }

    time(&timer->start);
    timer->stop = -1; 
}

void upo_timer_stop(upo_timer_t timer)
{
    if (timer == NULL)
    {
        upo_timer_throw_error("Invalid timer argument");
    }

    if (!upo_timer_is_stopped(timer))
    {
        time(&timer->stop);
    }
} 

int upo_timer_is_started(const upo_timer_t timer) 
{
    if (timer == NULL)
    {
        upo_timer_throw_error("Invalid timer argument");
    }

    return (timer->start != -1) ? 1 : 0;
}

int upo_timer_is_stopped(const upo_timer_t timer) 
{
    if (timer == NULL)
    {
        upo_timer_throw_error("Invalid timer argument");
    }

    return timer->stop != -1 ? 1 : 0;
}

double upo_timer_elapsed(const upo_timer_t timer)
{
    if (timer == NULL)
    {
        upo_timer_throw_error("Invalid timer argument");
    }

    if (upo_timer_is_stopped(timer))
    {
        /* The timer is stopped: returns the length of the [start,stop) interval */
        return difftime(timer->stop, timer->start);
    }

    if (upo_timer_is_started(timer))
    {
        /* The timer isn't stopped: returns the time elapsed so far */
        return difftime(time(NULL), timer->start);
    }

    return -1;
}

void upo_timer_throw_error(const char *msg)
{
    assert(msg);

    fprintf(stderr, "[file: %s, line: %d] %s\n", __FILE__, __LINE__, msg);
    abort();
}
