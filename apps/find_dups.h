/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file apps/find_dups.h
 *
 * \brief Header file for the find duplicates in string arrays application.
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
#ifndef FIND_DUPS_H
#define FIND_DUPS_H

#include <stdio.h>

struct upo_strings_list_node_s
{
    void *value;
    struct upo_strings_list_node_s *next;
};

typedef struct upo_strings_list_node_s upo_strings_list_node_t;

typedef upo_strings_list_node_t *upo_strings_list_t;

upo_strings_list_t upo_find_dups(const char **strs, size_t n);

upo_strings_list_t upo_find_idups(const char **strs, size_t n, int ignore_case);

static void upo_dups_create_list(upo_strings_list_t *list, void *value);

static void *upo_to_lower_case(const char *src);

static void upo_destroy_dup_list(upo_strings_list_t *list);

static void upo_check_list(upo_strings_list_t list, const char **strs);

#endif /* FIND_DUPS_H */