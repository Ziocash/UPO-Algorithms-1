/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file apps/sort_playlist.c
 *
 * \brief An application to sort playlists.
 *
 * \author Simone Gattini, Federico Barbero, Anton Iliev
 *
 * \copyright 2016 University of Piemonte Orientale, Computer Science Institute
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
#include "playlist.h"
#include <stdio.h>
#include <string.h>
#include <upo/error.h>
#include <upo/sort.h>


#define DEFAULT_OPT_ORDER_BY playlist_by_artist_sorting_criterion
#define DEFAULT_OPT_ORDER_BY_STR "artist"
#define DEFAULT_OPT_VERBOSE 0


/** \brief Extracts the sorting criterion from the given string. */
static playlist_sorting_criterion_t parse_sorting_criterion(const char *str);

/** \brief Prints the given sorting criterion to the given stream. */
static void print_sorting_criterion(FILE *fp, playlist_sorting_criterion_t order_by);

/** \brief Displays a help message. */
static void usage(const char *progname);


playlist_sorting_criterion_t parse_sorting_criterion(const char *str)
{
    assert( str != NULL );

    if (!strcmp("artist", str))
    {
        return playlist_by_artist_sorting_criterion;
    }
    if (!strcmp("album", str))
    {
        return playlist_by_album_sorting_criterion;
    }
    if (!strcmp("year", str))
    {
        return playlist_by_year_sorting_criterion;
    }
    if (!strcmp("title", str))
    {
        return playlist_by_track_title_sorting_criterion;
    }
    if (!strcmp("trackno", str))
    {
        return playlist_by_track_number_sorting_criterion;
    }
    return playlist_unknown_sorting_criterion;
}

void print_sorting_criterion(FILE *fp, playlist_sorting_criterion_t order_by)
{
    assert( fp != NULL );

    switch (order_by)
    {
        case playlist_by_artist_sorting_criterion:
            fprintf(fp, "artist");
            break;
        case playlist_by_album_sorting_criterion:
            fprintf(fp, "album");
            break;
        case playlist_by_year_sorting_criterion:
            fprintf(fp, "year");
            break;
        case playlist_by_track_number_sorting_criterion:
            fprintf(fp, "trackno");
            break;
        case playlist_by_track_title_sorting_criterion:
            fprintf(fp, "title");
            break;
        case playlist_unknown_sorting_criterion:
            fprintf(fp, "unknown");
            break;
    }
}

void usage(const char *progname)
{
    fprintf(stderr, "Usage: %s <options>\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "-h: Displays this message.\n");
    fprintf(stderr, "-i <file name>: Specifies the name of the input playlist file.\n");
    fprintf(stderr, "-s <value>: Specifies the sorting critertion to apply.\n"
                    "            Possible values are:\n"
                    "            - artist\n"
                    "            - album\n"
                    "            - title\n"
                    "            - trackno\n"
                    "            - year\n"
                    "            [default: %s]\n", DEFAULT_OPT_ORDER_BY_STR);
    fprintf(stderr, "-v: Enables output verbosity.\n"
                    "    [default: <%s>]\n", (DEFAULT_OPT_VERBOSE ? "enabled" : "disabled"));
}


int main(int argc, char *argv[])
{
    int opt_help = 0;
    char *opt_input_file = NULL;
    playlist_sorting_criterion_t *opt_order_by_ary = NULL;
    size_t opt_order_by_num = 0;
    int opt_verbose = DEFAULT_OPT_VERBOSE;
    int arg;
    playlist_t playlist = NULL;
    size_t i;

    for (arg = 1; arg < argc; ++arg)
    {
        if (!strcmp("-i", argv[arg]))
        {
            ++arg;
            if (arg >= argc)
            {
                fprintf(stderr, "ERROR: expected playlist file name.\n");
                usage(argv[0]);
                return EXIT_FAILURE;
            }

            opt_input_file = argv[arg];
        }
        else if (!strcmp("-h", argv[arg]))
        {
            opt_help = 1;
        }
        else if (!strcmp("-s", argv[arg]))
        {
            char *str = NULL;
            playlist_sorting_criterion_t order_by;
            playlist_sorting_criterion_t *tmp_order_by_ary = NULL;

            ++arg;
            if (arg >= argc)
            {
                fprintf(stderr, "ERROR: expected sorting criterion.\n");
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            str = argv[arg];
            order_by = parse_sorting_criterion(str);
            if (order_by == playlist_unknown_sorting_criterion)
            {
                fprintf(stderr, "ERROR: unknown sorting criterion.\n");
                usage(argv[0]);
                return EXIT_FAILURE;
            }

            ++opt_order_by_num;
            tmp_order_by_ary = realloc(opt_order_by_ary, opt_order_by_num*sizeof(playlist_sorting_criterion_t));
            if (tmp_order_by_ary == NULL)
            {
                fprintf(stderr, "ERROR: unable to allocate memory for sorting criteria (%s).\n", strerror(errno));
                return EXIT_FAILURE;
            }
            opt_order_by_ary = tmp_order_by_ary;
            opt_order_by_ary[opt_order_by_num-1] = order_by;
        }
        else if (!strcmp("-v", argv[arg]))
        {
            opt_verbose = 1;
        }
    }

    if (opt_help)
    {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }
    if (opt_input_file == NULL)
    {
        fprintf(stderr, "ERROR: input playlist file has not been specified.\n");
        usage(argv[0]);
        return EXIT_FAILURE;
    }
    if (opt_order_by_ary == NULL)
    {
        opt_order_by_ary = malloc(sizeof(playlist_sorting_criterion_t));
        opt_order_by_ary[0] = DEFAULT_OPT_ORDER_BY;
        opt_order_by_num = 1;
    }

    if (opt_verbose)
    {
        printf("-- Options:\n");
        printf("* Playlist file name: %s\n", opt_input_file);
        printf("* Sorting criteria: ");
        for (i = 0; i < opt_order_by_num; ++i)
        {
            print_sorting_criterion(stdout, opt_order_by_ary[i]);
        }
        printf("\n");
    }

    if (opt_verbose)
    {
        printf("Reading the playlist from '%s'...\n", opt_input_file);
    }
    playlist = playlist_create_from_file(opt_input_file);
    if (playlist == NULL)
    {
        fprintf(stderr, "ERROR: problems while reading the input playlist.\n");
        return EXIT_FAILURE;
    }

    if (opt_verbose)
    {
        playlist_print(playlist, stdout);
    }

    /*
     * NOTE: if you want to get a playlist ordered by:
     *          criterion #1, criterion #2, ... and criterion #N,
     *       you need to call the sorting algorithm N times in the reverse
     *       order, so that the first time it sorts by criterion #N, then the
     *       second time it sorts by criterion #(N-1), and so on until the last
     *       time when it sorts by criterion #1.
     *       For instance, to get a playlist ordered by:
     *          artist, album, track number
     *       you must sort by track number, then by album and finally by artist.
     */

    for (i = opt_order_by_num; i > 0; --i)
    {
        if (opt_verbose)
        {
            printf("Sorting the playlist with criterion '");
            print_sorting_criterion(stdout, opt_order_by_ary[i-1]);
            printf("'...\n");
        }
        playlist_sort(playlist, opt_order_by_ary[i-1]);
    }

    if (opt_verbose)
    {
        printf("Writing the sorted playlist...\n");
    }
    playlist_print(playlist, stdout);

    playlist_destroy(playlist);

    if (opt_order_by_ary != NULL)
    {
        free(opt_order_by_ary);
        opt_order_by_num = 0;
    }

    return EXIT_SUCCESS;
}
