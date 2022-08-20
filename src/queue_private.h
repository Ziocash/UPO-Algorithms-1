/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file src/queue_private.h
 *
 * \brief Private header for the Queue type.
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

#ifndef UPO_QUEUE_PRIVATE_H
#define UPO_QUEUE_PRIVATE_H

#include <upo/queue.h>

typedef struct upo_queue_node_s *upo_queue_node_t;

struct upo_queue_s
{
    upo_queue_node_t first;
    upo_queue_node_t last;
    size_t size;
};

struct upo_queue_node_s
{
    void *data;
    upo_queue_node_t previous;
    upo_queue_node_t next;
};

void upo_queue_clear_impl(upo_queue_node_t node, int destroy_data);

void upo_queue_enqueue_impl(upo_queue_node_t node, void *data);

#endif /* UPO_QUEUE_PRIVATE_H */