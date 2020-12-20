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
#include <stdio.h>
#include <stdlib.h>
#include <upo/hires_timer.h>

static void test_create_destroy();
static void test_start();
static void test_stop();
static void test_elapsed();


void test_create_destroy()
{
    upo_hires_timer_t timer = upo_hires_timer_create();

    assert(timer != NULL);

    upo_hires_timer_destroy(timer);
}

void test_start()
{
    upo_hires_timer_t timer = upo_hires_timer_create();

    assert(upo_hires_timer_is_started(timer) == 0);

    upo_hires_timer_start(timer);

    assert(upo_hires_timer_is_started(timer) == 1);

    upo_hires_timer_destroy(timer);
}

void test_stop()
{
    upo_hires_timer_t timer = upo_hires_timer_create();

    assert(upo_hires_timer_is_stopped(timer) == 0);

    upo_hires_timer_start(timer);

    assert(upo_hires_timer_is_stopped(timer) == 0);

    upo_hires_timer_stop(timer);

    assert(upo_hires_timer_is_stopped(timer) == 1);

    upo_hires_timer_destroy(timer);
}

void test_elapsed()
{
    upo_hires_timer_t timer = upo_hires_timer_create();

    assert(upo_hires_timer_elapsed(timer) == -1);

    upo_hires_timer_start(timer);

    assert(upo_hires_timer_elapsed(timer) >= 0);

    upo_hires_timer_stop(timer);

    assert(upo_hires_timer_elapsed(timer) >= 0);

    upo_hires_timer_destroy(timer);
}


int main()
{
    printf("Test case 'create/destroy'... ");
    fflush(stdout);
    test_create_destroy();
    printf("OK\n");

    printf("Test case 'start'... ");
    fflush(stdout);
    test_start();
    printf("OK\n");

    printf("Test case 'stop'... ");
    fflush(stdout);
    test_stop();
    printf("OK\n");

    printf("Test case 'elapsed'... ");
    fflush(stdout);
    test_elapsed();
    printf("OK\n");

    return 0;
}
