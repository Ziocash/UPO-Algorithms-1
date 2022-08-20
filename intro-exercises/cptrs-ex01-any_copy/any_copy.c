/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file intro-exercises/cptrs-ex01-any_copy/any_copy.c
 *
 * \brief Implementation for generic Any Copy function.
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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void any_copy(void *dest, const void *src, size_t n);

void any_copy(void *dest, const void *src, size_t n)
{
    assert(dest != NULL);
    assert(src != NULL);

    unsigned char *temp_dest = dest;
    const unsigned char *temp_src = src;

    for (size_t i = 0; i < n; i++)
        temp_dest[i] = temp_src[i];
}

int main()
{
    char cary[] = "Hello, World";
    int iary[] = {1, 2, 3, 4, 5, -4, -3, -2, -1};
    float fary[] = {1.1, 2.2, 3.3, 4.4, 5.5, -4.6, -3.7, -2.8, -1.9};
    char cary_cpy[13]; /* strlen("...") + 1 (for the '\0' character) */
    int iary_cpy[9];
    float fary_cpy[9];
    size_t cary_size = sizeof cary / sizeof cary[0];
    size_t iary_size = sizeof iary / sizeof iary[0];
    size_t fary_size = sizeof fary / sizeof fary[0];
    size_t i;

    any_copy(cary_cpy, cary, cary_size);
    printf("[");
    for (i = 0; i < cary_size; ++i)
    {
        assert(cary_cpy[i] == cary[i]);

        printf("'%c' ", cary_cpy[i]);
    }
    printf("]\n");

    printf("[");
    any_copy(iary_cpy, iary, iary_size * sizeof(int));
    for (i = 0; i < iary_size; ++i)
    {
        assert(iary_cpy[i] == iary[i]);

        printf("%d ", iary_cpy[i]);
    }
    printf("]\n");

    printf("[");
    any_copy(fary_cpy, fary, fary_size * sizeof(float));
    for (i = 0; i < fary_size; ++i)
    {
        assert(fary_cpy[i] == fary[i]);

        printf("%f ", fary_cpy[i]);
    }
    printf("]\n");

    return 0;
}
