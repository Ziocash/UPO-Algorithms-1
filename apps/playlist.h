/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file apps/playlist.h
 *
 * \brief Header file for the playlist type.
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

#ifndef PLAYLIST_H
#define PLAYLIST_H


#include <stdio.h>


/** \brief Type playlist type. */
typedef struct playlist_s* playlist_t;

/** \brief Criteria to sort a playlist. */
typedef enum {
            playlist_unknown_sorting_criterion, /**< Unknown sorting criterion. */
            playlist_by_artist_sorting_criterion, /**< Sort by artist name. */
            playlist_by_album_sorting_criterion, /**< Sort by album name. */
            playlist_by_year_sorting_criterion, /**< Sort by year of release. */
            playlist_by_track_number_sorting_criterion, /**< Sort by track number. */
            playlist_by_track_title_sorting_criterion /**< Sort by track title. */
        } playlist_sorting_criterion_t; /**< Sort by artist name. */


/**
 * \brief Creates a playlist from the given file.
 *
 * \param file_name The name of the file from which reading the playlist.
 * \return A new playlist built from the given file name.
 */
playlist_t playlist_create_from_file(const char* file_name);

/**
 * \brief Destroys the given playlist.
 *
 * \param playlist The playlist to destroy.
 */
void playlist_destroy(playlist_t playlist);

/**
 * \brief Prints the given playlist to the given output stream.
 *
 * \param playlist The playlist to print.
 * \param fp The stream to which print the playlist.
 */
void playlist_print(const playlist_t playlist, FILE* fp);

/**
 * \brief Sorts the given playlist with the given criterion.
 *
 * \param playlist The playlist to sort.
 * \param order_by The sorting criterion.
 */
void playlist_sort(playlist_t playlist, playlist_sorting_criterion_t order_by);


#endif /* PLAYLIST_H */
