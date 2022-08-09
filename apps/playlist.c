/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file apps/playlist.c
 *
 * \brief Implementation of a type to represent playlists.
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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/error.h>
#include <upo/io.h>
#include <upo/sort.h>

#define PLAYLIST_ENTRY_DELIMITER '|'
#define PLAYLIST_ENTRY_NUM_FIELDS 5

/** \brief Defines the type of an entry of a playlist. */
typedef struct
{
    char *artist;      /**< The name of the artist */
    char *album;       /**< The name of the album */
    int year;          /**< The release year of the album */
    int track_num;     /**< The position of the song in the album */
    char *track_title; /**< The title of the song */
} entry_t;

/** \brief Defines the type of a playlist. */
struct playlist_s
{
    entry_t *entries;
    size_t size;
};

/** \brief Destroys the given playlist entry. */
static void playlist_entry_destroy(entry_t *entry);

/** \brief Comparison function for playlist entries based on artist name */
static int by_artist_comparator(const void *a, const void *b);

/** \brief Comparison function for playlist entries based on album name */
static int by_album_comparator(const void *a, const void *b);

/** \brief Comparison function for playlist entries based on track number */
static int by_track_number_comparator(const void *a, const void *b);

/** \brief Comparison function for playlist entries based on track title */
static int by_track_title_comparator(const void *a, const void *b);

/** \brief Comparison function for playlist entries based on album release year */
static int by_year_comparator(const void *a, const void *b);

/** \brief Extracts a playlist entry from the given string. */
static int parse_entry(const char *str, entry_t *entry);

/**** EXERCISE #2 - BEGIN of SORTING PLAYLISTS ****/

int by_artist_comparator(const void *a, const void *b)
{
    const entry_t aa = *(const entry_t *)a;
    const entry_t bb = *(const entry_t *)b;

    return strcmp(aa.artist, bb.artist);
}

int by_album_comparator(const void *a, const void *b)
{
    const entry_t aa = *(const entry_t *)a;
    const entry_t bb = *(const entry_t *)b;

    return strcmp(aa.album, bb.album);
}

int by_year_comparator(const void *a, const void *b)
{
    const entry_t aa = *(const entry_t *)a;
    const entry_t bb = *(const entry_t *)b;

    return (aa.year > bb.year) - (aa.year < bb.year);
}

int by_track_number_comparator(const void *a, const void *b)
{
    const entry_t aa = *(const entry_t *)a;
    const entry_t bb = *(const entry_t *)b;

    return (aa.track_num > bb.track_num) - (aa.track_num < bb.track_num);
}

int by_track_title_comparator(const void *a, const void *b)
{
    const entry_t aa = *(const entry_t *)a;
    const entry_t bb = *(const entry_t *)b;

    return strcmp(aa.track_title, bb.track_title);
}

void playlist_sort(playlist_t playlist, playlist_sorting_criterion_t order_by)
{
    switch (order_by)
    {
    case playlist_by_artist_sorting_criterion:
        upo_merge_sort(playlist->entries, playlist->size, sizeof(playlist->entries[0]), by_artist_comparator);
        break;
    case playlist_by_album_sorting_criterion:
        upo_merge_sort(playlist->entries, playlist->size, sizeof(playlist->entries[0]), by_album_comparator);
        break;
    case playlist_by_year_sorting_criterion:
        upo_merge_sort(playlist->entries, playlist->size, sizeof(playlist->entries[0]), by_year_comparator);
        break;
    case playlist_by_track_number_sorting_criterion:
        upo_merge_sort(playlist->entries, playlist->size, sizeof(playlist->entries[0]), by_track_number_comparator);
        break;
    case playlist_by_track_title_sorting_criterion:
        upo_merge_sort(playlist->entries, playlist->size, sizeof(playlist->entries[0]), by_track_title_comparator);
        break;
    case playlist_unknown_sorting_criterion:
    default:
        perror("Unknown criterion");
        abort();
        break;
    }
}

/**** EXERCISE #2 - END of SORTING PLAYLISTS ****/

int parse_entry(const char *str, entry_t *entry)
{
    char delim[] = {PLAYLIST_ENTRY_DELIMITER, '\0'};
    char *aux_str = NULL;
    char *loop_str = NULL;
    char *token = NULL;
    int ok = 0;
    size_t num_fields = PLAYLIST_ENTRY_NUM_FIELDS;
    size_t field_len = 0;
    size_t field;

    assert(str != NULL);
    assert(entry != NULL);

    /* We need to copy the original string since strtok modifies its first argument */
    aux_str = malloc(strlen(str) + 1);
    if (aux_str == NULL)
    {
        upo_throw_sys_error("Unable to allocate memory for auxiliary string");
    }
    strcpy(aux_str, str);

    /* Blanks the entry */
    entry->artist = entry->album = entry->track_title = NULL;
    entry->year = entry->track_num = 0;

    loop_str = aux_str;
    ok = 1;
    for (field = 0; field < num_fields && ok; ++field)
    {
        if (field > 0)
        {
            loop_str = NULL;
        }

        token = strtok(loop_str, delim);
        if (token == NULL)
        {
            ok = 0;
        }
        else
        {
            switch (field)
            {
            case 0: /* artist */
                field_len = strlen(token);
                entry->artist = malloc(field_len + 1);
                if (entry->artist == NULL)
                {
                    upo_throw_sys_error("Unable to allocate memory for artist name");
                }
                strcpy(entry->artist, token);
                break;
            case 1: /* album */
                field_len = strlen(token);
                entry->album = malloc(field_len + 1);
                if (entry->album == NULL)
                {
                    upo_throw_sys_error("Unable to allocate memory for album name");
                }
                strcpy(entry->album, token);
                break;
            case 2: /* year */
                entry->year = atoi(token);
                break;
            case 3: /* track number */
                entry->track_num = atoi(token);
                break;
            case 4: /* track title */
                field_len = strlen(token);
                entry->track_title = malloc(field_len + 1);
                if (entry->track_title == NULL)
                {
                    upo_throw_sys_error("Unable to allocate memory for track title");
                }
                strcpy(entry->track_title, token);
                break;
            case PLAYLIST_ENTRY_NUM_FIELDS: /* end-of-entry sentinel */
                break;
            }
        }
    }

    /* Check data stored in the entry */
    if (ok)
    {
        if (strlen(entry->artist) == 0 || strlen(entry->album) == 0 || entry->year <= 0 || entry->track_num <= 0 || strlen(entry->track_title) == 0)
        {
            ok = 0;
        }
    }

    /* If something has gone wrong, cleans-up memory and blanks the entry */
    if (!ok)
    {
        playlist_entry_destroy(entry);
    }

    free(aux_str);

    return ok;
}

void playlist_entry_destroy(entry_t *entry)
{
    assert(entry != NULL);

    if (entry->artist != NULL)
    {
        free(entry->artist);
        entry->artist = NULL;
    }
    if (entry->album != NULL)
    {
        free(entry->album);
        entry->album = NULL;
    }
    entry->year = 0;
    entry->track_num = 0;
    if (entry->track_title != NULL)
    {
        free(entry->track_title);
        entry->track_title = NULL;
    }
}

playlist_t playlist_create_from_file(const char *file_name)
{
    FILE *fp = NULL;
    char *line = NULL;
    size_t line_len = 0;
    int ok = 0;
    playlist_t playlist = NULL;

    assert(file_name);

    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        upo_throw_sys_error("Unable to open playlist file");
    }

    playlist = malloc(sizeof(struct playlist_s));
    if (playlist == NULL)
    {
        return NULL;
    }
    playlist->entries = NULL;
    playlist->size = 0;

    ok = 1;
    while (upo_io_read_line(fp, &line, &line_len) > 0)
    {
        entry_t entry;
        entry_t *tmp_entries = NULL;

        if (line_len > 1 && line[line_len - 2] == '\n')
        {
            line_len -= 2;
            line[line_len] = '\0';
        }

        tmp_entries = realloc(playlist->entries, (playlist->size + 1) * sizeof(entry_t));
        if (tmp_entries == NULL)
        {
            ok = 0;
            break;
        }
        playlist->entries = tmp_entries;
        playlist->size += 1;

        ok = parse_entry(line, &entry);
        if (ok == 0)
        {
            break;
        }
        playlist->entries[playlist->size - 1] = entry;
    }
    if (line != NULL)
    {
        free(line);
    }

    fclose(fp);

    if (ok == 0)
    {
        playlist_destroy(playlist);
        playlist = NULL;
    }

    return playlist;
}

void playlist_print(const playlist_t playlist, FILE *fp)
{
    size_t i;

    assert(playlist != NULL);

    for (i = 0; i < playlist->size; ++i)
    {
        fprintf(fp, "%c%s%c%s%c%d%c%d%c%s%c\n", PLAYLIST_ENTRY_DELIMITER,
                playlist->entries[i].artist,
                PLAYLIST_ENTRY_DELIMITER,
                playlist->entries[i].album,
                PLAYLIST_ENTRY_DELIMITER,
                playlist->entries[i].year,
                PLAYLIST_ENTRY_DELIMITER,
                playlist->entries[i].track_num,
                PLAYLIST_ENTRY_DELIMITER,
                playlist->entries[i].track_title,
                PLAYLIST_ENTRY_DELIMITER);
    }
}

void playlist_destroy(playlist_t playlist)
{
    if (playlist != NULL)
    {
        if (playlist->entries != NULL)
        {
            size_t i;

            for (i = 0; i < playlist->size; ++i)
            {
                playlist_entry_destroy(&(playlist->entries[i]));
            }

            free(playlist->entries);
        }
        free(playlist);
    }
}
