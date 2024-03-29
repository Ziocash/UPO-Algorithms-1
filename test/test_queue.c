/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file test/test_queue.c
 *
 * \brief Implementation for queue testing.
 *
 * \author Simone Gattini, Federico Barbero, Anton Iliev
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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/error.h>
#include <upo/queue.h>

static void test_create_destroy();

static void test_enqueue_dequeue();

static void test_peek();

static void test_clear();

static void test_size();

static void test_null();

int main(void)
{
    fprintf(stdout, "Test create/destroy...");
    test_create_destroy();
    fflush(stdout);
    printf("OK\n");

    fprintf(stdout, "Test queue/dequeue...");
    test_enqueue_dequeue();
    fflush(stdout);
    printf("OK\n");

    fprintf(stdout, "Test peek...");
    test_peek();
    fflush(stdout);
    printf("OK\n");

    fprintf(stdout, "Test clear...");
    test_clear();
    fflush(stdout);
    printf("OK\n");

    fprintf(stdout, "Test size...");
    test_size();
    fflush(stdout);
    printf("OK\n");

    fprintf(stdout, "Test null...");
    test_null();
    fflush(stdout);
    printf("OK\n");

    return 0;
}

void test_create_destroy()
{
    upo_queue_t queue = upo_queue_create();
    assert(queue != NULL);
    upo_queue_destroy(queue, 0);
}

void test_enqueue_dequeue()
{
    upo_queue_t queue = upo_queue_create();
    assert(queue != NULL);
    char *str = "Hello from queue";
    upo_queue_enqueue(queue, str);
    assert(upo_queue_size(queue) == 1);
    upo_queue_dequeue(queue, 0);
    upo_queue_destroy(queue, 0);
}

void test_peek()
{
    upo_queue_t queue = upo_queue_create();
    int iary[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < sizeof(iary) / sizeof(int); i++)
    {
        upo_queue_enqueue(queue, &iary[i]);
    }
    int actual[10];
    for (size_t i = 0; i < sizeof(iary) / sizeof(int); i++)
    {
        actual[i] = *((int *)upo_queue_peek(queue));
        upo_queue_dequeue(queue, 0);
    }
    for (size_t i = 0; i < sizeof(iary) / sizeof(int); i++)
        assert(actual[i] == iary[i]);

    upo_queue_destroy(queue, 0);
}

void test_clear()
{
    upo_queue_t queue = upo_queue_create();
    int iary[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < sizeof(iary) / sizeof(int); i++)
    {
        upo_queue_enqueue(queue, &iary[i]);
    }
    assert(upo_queue_size(queue) == 10);
    upo_queue_clear(queue, 0);
    assert(upo_queue_is_empty(queue));
    upo_queue_destroy(queue, 0);
}

void test_size()
{
    upo_queue_t queue = upo_queue_create();
    int iary[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < sizeof(iary) / sizeof(int); i++)
    {
        upo_queue_enqueue(queue, &iary[i]);
    }
    assert(upo_queue_size(queue) == 10);
    upo_queue_clear(queue, 0);
    assert(upo_queue_is_empty(queue));
    upo_queue_destroy(queue, 0);
}

void test_null()
{
    upo_queue_t queue = NULL;
    upo_queue_clear(queue, 0);
    assert(upo_queue_is_empty(queue) == 0);
    int num = 15;
    upo_queue_enqueue(queue, &num);
    assert(upo_queue_peek(queue) == NULL);
}