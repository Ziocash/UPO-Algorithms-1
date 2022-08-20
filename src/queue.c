/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file src/queue.c
 *
 * \brief Implementation file for the Queue type.
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

#include "queue_private.h"
#include <stdio.h>
#include <stdlib.h>

upo_queue_t upo_queue_create()
{
    upo_queue_t q = malloc(sizeof(struct upo_queue_s));
    if (q == NULL)
    {
        perror("Allocation of queue failed");
        exit(EXIT_FAILURE);
    }
    q->first = NULL;
    q->last = NULL;
    q->size = 0;
    return q;
}

void upo_queue_destroy(upo_queue_t queue, int destroy_data)
{
    if (queue == NULL)
        return;

    upo_queue_clear(queue, destroy_data);
    free(queue);
}

void upo_queue_clear(upo_queue_t queue, int destroy_data)
{
    if (queue == NULL)
        return;
    if (upo_queue_is_empty(queue))
        return;

    while (queue->first != queue->last)
    {
        upo_queue_node_t node = queue->last;
        queue->last = node->previous;
        if (destroy_data)
            free(node->data);
        free(node);
        queue->size -= 1;
    }
    free(queue->first);
    queue->size -= 1;
}

void upo_queue_enqueue(upo_queue_t queue, void *data)
{
    if (queue == NULL)
        return;

    upo_queue_node_t node = malloc(sizeof(struct upo_queue_node_s));
    node->data = data;
    node->next = NULL;
    node->previous = NULL;
    if (queue->size > 0)
    {
        node->previous = queue->last;
        queue->last->next = node;
        queue->last = queue->last->next;
    }
    else
    {
        queue->first = node;
        queue->last = node;
    }
    queue->size += 1;
}

void upo_queue_dequeue(upo_queue_t queue, int destroy_data)
{
    if (queue == NULL)
        return;
    if (queue->size == 0)
        return;

    upo_queue_node_t node = queue->first;
    queue->first = node->next;
    if (queue->size == 1)
        queue->first = NULL;
    if (destroy_data)
        free(node->data);
    free(node);
    queue->size -= 1;
}

void *upo_queue_peek(const upo_queue_t queue)
{
    if (queue == NULL)
        return NULL;

    return queue->first->data;
}

size_t upo_queue_size(const upo_queue_t queue)
{
    if (queue == NULL)
        return 0;

    return queue->size;
}

int upo_queue_is_empty(const upo_queue_t queue)
{
    if (queue == NULL)
        return 0;

    if (queue->size > 0)
        return 0;
    return 1;
}