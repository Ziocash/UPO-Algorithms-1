/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file upo/stack.h
 *
 * \brief The Stack abstract data type.
 *
 * A Stack is an abstract data type that represents a container of elements such
 * that:
 * -# Each element is added over the top of the Stack (*push* operation).
 * -# Each element is removed from the top of the Stack (*pop* operation).
 * .
 * A Stack is often called a Last-in First-out (LIFO) container since the last
 * element that is added is the first to be removed.
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

#ifndef UPO_STACK_H
#define UPO_STACK_H


#include <stddef.h>


/** \brief Declares the Stack type. */
typedef struct upo_stack_s* upo_stack_t;


/**
 * \brief Creates a new stack.
 *
 * \return A stack.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
upo_stack_t upo_stack_create();

/**
 * \brief Destroys the given stack.
 *
 * \param stack The stack to destroy.
 * \param destroy_data Tells whether the previously allocated memory for data
 *  stored in this stack must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_stack_destroy(upo_stack_t stack, int destroy_data);

/**
 * \brief Add an element to the top of the given stack.
 *
 * \param stack The stack to which adding a new element.
 * \param data The new element.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
void upo_stack_push(upo_stack_t stack, void *data);

/**
 * \brief Remove an element from the top of the given stack.
 *
 * \param stack The stack from which removing an element.
 * \param destroy_data Tells whether the previously allocated memory for data,
 *  that is to be removed, must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
void upo_stack_pop(upo_stack_t stack, int destroy_data);

/**
 * \brief Returns the element stored on the top of the given stack.
 *
 * \param stack The stack.
 * \return The element stored on the top of the stack, or `NULL` if the stack is
 *  empty.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
void* upo_stack_top(const upo_stack_t stack);

/**
 * \brief Tells if the given stack is empty.
 *
 * \param stack The stack.
 * \return `1` if the stack is empty or `0` otherwise.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
int upo_stack_is_empty(const upo_stack_t stack);

/**
 * \brief Returns the number of elements stored in the given stack.
 *
 * \param stack The stack.
 * \return The number of elements stored in the stack, or `0` otherwise.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
size_t upo_stack_size(const upo_stack_t stack);

/**
 * \brief Removes all elements from the given stack.
 *
 * \param stack The stack.
 * \param destroy_data Tells whether the previously allocated memory for data
 *  stored in this stack must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_stack_clear(upo_stack_t stack, int destroy_data);


#endif /* UPO_STACK_H */
