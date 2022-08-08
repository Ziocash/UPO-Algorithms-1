/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file apps/sort_playlist.c
 *
 * \brief An application to sort playlists.
 *
 * \author Simone Gattini, Federico Barbero, Anton Iliev
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

#include <assert.h>
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
    playlist_sorting_criterion_t opt_order_by = DEFAULT_OPT_ORDER_BY;
    int opt_verbose = DEFAULT_OPT_VERBOSE;
    int arg;
    playlist_t playlist = NULL;

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

            ++arg;
            if (arg >= argc)
            {
                fprintf(stderr, "ERROR: expected sorting criterion.\n");
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            str = argv[arg];
            opt_order_by = parse_sorting_criterion(str);
            if (opt_order_by == playlist_unknown_sorting_criterion)
            {
                fprintf(stderr, "ERROR: unknown sorting criterion.\n");
                usage(argv[0]);
                return EXIT_FAILURE;
            }
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

    if (opt_verbose)
    {
        printf("-- Options:\n");
        printf("* Playlist file name: %s\n", opt_input_file);
        printf("* Sorting criterion: ");
        print_sorting_criterion(stdout, opt_order_by);
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

    if (opt_verbose)
    {
        printf("Sorting the playlist with criterion '");
        print_sorting_criterion(stdout, opt_order_by);
        printf("'...\n");
    }
    playlist_sort(playlist, opt_order_by);

    playlist_print(playlist, stdout);

    playlist_destroy(playlist);

    return EXIT_SUCCESS;
}
