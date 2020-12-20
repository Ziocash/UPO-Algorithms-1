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
#include <ctype.h>
#include <upo/error.h>
#include <upo/io.h>


void upo_io_ignore_spaces(FILE *stream)
{
    if (stream != NULL)
    {
        int ch;

        while ((ch = fgetc(stream)) != EOF && isspace(ch))
        {
            ; /* empty */
        }
        if (ch != EOF)
        {
            ungetc(ch, stream);
        }
    }
}

size_t upo_io_read_line(FILE *stream, char **lineptr, size_t *size)
{
    int ch; /* the char read */
    size_t rd = 0; /* number of char read */
    int size_changed = 0;

    /* preconditions */
    assert( lineptr != NULL );
    assert( size != NULL );

    if (stream == NULL || ferror(stream))
    {
        *lineptr = NULL;
        *size = 0;
        return 0;
    }

    if (*lineptr == NULL)
    {
        /* initialize the size to zero so when reading the first char
         * memory is allocated. */
        *size = 0;
    }

    while ((ch = fgetc(stream)) != EOF)
    {
        /* check if the string is capable to contain this char and the '\0' */
        if (*size == 0 || rd >= (*size-1))
        {
            char *tmp = NULL;

            *size += 10;
            tmp = realloc(*lineptr, *size);
            if (tmp == NULL)
            {
                upo_throw_sys_error("Error while re-allocating memory for reading a line");
            }
            *lineptr = tmp;

            size_changed = 1;
        }

        (*lineptr)[rd++] = ch;

        if (ch == '\n')
        {
            break;
        }
    }

    if (rd > 0)
    {
        if (size_changed)
        {
            *size = rd + 1;
            *lineptr = realloc(*lineptr, *size);
            if (*lineptr == NULL)
            {
                upo_throw_sys_error("Error while re-allocating memory for reading a line");
            }
        }

        (*lineptr)[rd] = '\0';
    }

    return rd;
}

