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
#include <upo/error.h>
#include <upo/stack.h>


static void test_create_destroy();
static void test_push_pop();
static void test_top();
static void test_empty();
static void test_size();
static void test_clear();
static void test_null();

void test_create_destroy()
{
    upo_stack_t stack;

    stack = upo_stack_create();

    assert( stack != NULL );

    upo_stack_destroy(stack, 0);
}

void test_push_pop()
{
    int value = 1;
    upo_stack_t stack;

    stack = upo_stack_create();

    upo_stack_push(stack, &value);

    assert( upo_stack_size(stack) == 1 );

    upo_stack_pop(stack, 0);

    assert( upo_stack_size(stack) == 0 );

    upo_stack_destroy(stack, 0);
}

void test_top()
{
    int value1 = 1;
    int value2 = 2;
    upo_stack_t stack;

    stack = upo_stack_create();

    upo_stack_push(stack, &value1);
    upo_stack_push(stack, &value2);

    assert( upo_stack_top(stack) != NULL );
    assert( *((int*) upo_stack_top(stack)) == value2 );

    upo_stack_pop(stack, 0);

    assert( upo_stack_top(stack) != NULL );
    assert( *((int*) upo_stack_top(stack)) == value1 );

    upo_stack_pop(stack, 0);

    assert( upo_stack_top(stack) == NULL );

    upo_stack_destroy(stack, 0);
}

void test_empty()
{
    int value = 1;
    upo_stack_t stack;

    stack = upo_stack_create();

    assert( upo_stack_is_empty(stack) );

    upo_stack_push(stack, &value);

    assert( !upo_stack_is_empty(stack) );

    upo_stack_pop(stack, 0);

    assert( upo_stack_is_empty(stack) );

    upo_stack_destroy(stack, 0);
}

void test_size()
{
    upo_stack_t stack;
    size_t n = 10;
    size_t i;

    stack = upo_stack_create();

    /* Allocates n double's vectors of size 1,2,...,n, respectively */
    for (i = 1; i <= n; ++i)
    {
        size_t sz = (i+1)*sizeof(double);
        double *dv = malloc(sz);
        if (dv == NULL)
        {
            upo_throw_sys_error("Unable to allocate memory for a vector of double");
        }
        memset(dv, 0, sz);

        upo_stack_push(stack, dv);
    }

    assert( upo_stack_size(stack) == n );

    upo_stack_pop(stack, 1);

    assert( upo_stack_size(stack) == (n-1) );

    upo_stack_destroy(stack, 1);
}

void test_clear()
{
    upo_stack_t stack;
    size_t n = 10;
    size_t i;

    stack = upo_stack_create();

    /* Allocates n double's vectors of size 1,2,...,n, respectively */
    for (i = 1; i <= n; ++i)
    {
        size_t sz = (i+1)*sizeof(double);
        double *dv = malloc(sz);
        if (dv == NULL)
        {
            upo_throw_sys_error("Unable to allocate memory for a vector of double");
        }
        memset(dv, 0, sz);

        upo_stack_push(stack, dv);
    }

    assert( upo_stack_size(stack) == n );

    upo_stack_clear(stack, 1);

    assert( upo_stack_size(stack) == 0 );

    upo_stack_destroy(stack, 1);
}

void test_null()
{
    upo_stack_t stack = NULL;

    assert( upo_stack_size(stack) == 0 );

    assert( upo_stack_is_empty(stack) );

    upo_stack_push(stack, NULL);

    upo_stack_clear(stack, 0);

    assert( upo_stack_size(stack) == 0 );

    upo_stack_destroy(stack, 0);
}


int main()
{
    printf("Test case 'create/destroy'... ");
    fflush(stdout);
    test_create_destroy();
    printf("OK\n");

    printf("Test case 'push/pop'... ");
    fflush(stdout);
    test_push_pop();
    printf("OK\n");

    printf("Test case 'top'... ");
    fflush(stdout);
    test_top();
    printf("OK\n");

    printf("Test case 'empty'... ");
    fflush(stdout);
    test_empty();
    printf("OK\n");

    printf("Test case 'size'... ");
    fflush(stdout);
    test_size();
    printf("OK\n");

    printf("Test case 'clear'... ");
    fflush(stdout);
    test_clear();
    printf("OK\n");

    printf("Test case 'null'... ");
    fflush(stdout);
    test_null();
    printf("OK\n");

    return 0;
}
