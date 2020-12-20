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
#include <stdlib.h>
#include <upo/random.h>
#include <upo/utility.h>


double upo_random_uniform_real(double lo, double hi)
{
    return lo + rand()/(RAND_MAX+1.0)*(hi-lo);
}

int upo_random_uniform_int(int lo, int hi)
{
    return lo + rand()/(RAND_MAX+1.0)*(hi-lo);
}

void upo_random_shuffle(void *base, size_t n, size_t size)
{
    char *ptr = base;
    size_t i;

    assert( base != NULL );

    for (i = 0; i < n; ++i)
    {   
        size_t r = upo_random_uniform_int(i, n-i);
        if (i != r)
        {
            upo_swap(ptr+i*size, ptr+r*size, size);
        }
    }
}

char* upo_random_string(char *s, size_t n)
{
    size_t i = 0;

    for (; i < n; ++i)
    {
        s[i] = upo_random_uniform_int(' ', '~');
    }
    s[n] = '\0';

    return s;
}
