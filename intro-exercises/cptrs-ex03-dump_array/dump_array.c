/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file intro-exercises/cptrs-ex03-dump_array/dump_array.c
 *
 * \brief Implementation for dump_array generic function.
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
#include <string.h>

static void dump_array(const void *base, size_t num_elem, size_t elem_size, void (*dump_element)(const void *, FILE *), FILE *fp);
static void dump_int(const void *p, FILE *fp);
static void dump_string(const void *p, FILE *fp);

void dump_array(const void *base, size_t num_elem, size_t elem_size, void (*dump_element)(const void *, FILE *), FILE *fp)
{
    assert(base != NULL);
    assert(fp != NULL);

    const unsigned char *array = base;

    fprintf(fp, "[");
    for (int i = 0; i < num_elem; i++)
    {
        dump_element(&(array[i * elem_size]), fp);
        if(i < num_elem - 1)
            fprintf(fp, ", ");
    }
    fprintf(fp, "]");
}

void dump_int(const void *p, FILE *fp)
{
    assert(p != NULL);
    assert(fp != NULL);
    const int *value = p;
    fprintf(fp, "%d", *value);
}

void dump_string(const void *p, FILE *fp)
{
    assert(p != NULL);
    assert(fp != NULL);
    const char * temp = *((char **)p);
    fprintf(fp, "%s", temp);
}

int main()
{
    int iary[] = {1, 20, 25, 32, 76, 123};
    const char *sary[] = {"e01", "e02", "e03", "e04", "e05", "e06"};
    FILE *fp = stdout;

    dump_array(iary, sizeof iary / sizeof iary[0], sizeof iary[0], dump_int, fp);
    fputc('\n', fp);
    dump_array(sary, sizeof sary / sizeof sary[0], sizeof sary[0], dump_string, fp);
    fputc('\n', fp);

    return 0;
}
