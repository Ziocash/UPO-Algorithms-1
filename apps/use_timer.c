/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file apps/use_timer.c
 *
 * \brief An application to show how the Timer ADT can be used.
 *
 * \author Marco Guazzone (marco.guazzone@uniupo.it)
 *
 * \copyright 2015 University of Piemonte Orientale, Computer Science Institute
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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <upo/timer.h>


static void do_something(long n);


int main(int argc, char *argv[])
{
    long n = 200000000L;
    upo_timer_t timer = NULL;

    if (argc > 1)
    {
        n = atol(argv[1]);
    }

    timer = upo_timer_create();

    upo_timer_start(timer);

    do_something(n);

    upo_timer_stop(timer);

    printf("Elapsed: %.f seconds.\n", upo_timer_elapsed(timer));

    upo_timer_destroy(timer);

    return 0;
}


// Does a very interesting task...
void do_something(long n)
{
    while (n > 0)
    {
        exp(sqrt(n));
        --n;
    }
}

