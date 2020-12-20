/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file stack_private.h
 *
 * \brief Private header for the Stack abstract data type.
 *
 * In this implementation, the Stack abstract data type is implemented as a
 * singly-linked list.
 * The `push` operation simply adds elements to the front of the list, while the
 * `pop` operation removes elements from the front of the list.
 * The `top` operation returns the element stored in the front of the list.
 *
 * \author Your Name
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

#ifndef UPO_STACK_PRIVATE_H
#define UPO_STACK_PRIVATE_H


#include <stddef.h>
#include <upo/stack.h>


/** \brief Defines the structure of each node of the singly-linked list implementing the stack. */
struct upo_stack_node_s
{
    void *data; /**< User-provided data. */
    struct upo_stack_node_s *next; /**< Pointer to the next node in the list. */
};
/** \brief Defines the type of a list node. */
typedef struct upo_stack_node_s upo_stack_node_t;

/** \brief Defines the structure of the list implementing the stack. */
struct upo_stack_s
{
    upo_stack_node_t *top; /**< The front of the list. */
    size_t size; /**< The size of the list. This field allows to guarantee a constant complexity for the `size` operation. */
};


#endif /* UPO_STACK_PRIVATE_H */
