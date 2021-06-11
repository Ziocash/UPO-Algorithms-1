/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file upo/bst.h
 *
 * \brief The Binary Search Tree (BST) abstract data type.
 *
 * Trees are nonlinear containers where data is structured according to
 * hierarchical organization.
 * Trees are made of nodes that are connected to each other according to a
 * parent-child relationship.
 * Binary Search Trees are Binary Trees where:
 * - Each node has a key and an associated value (possibly, the
 *   key itself),
 * - The key in node v is greater than the keys in all nodes in the
 *   left subtree of v, and
 * - The key in node v is less than the keys in all nodes in the right
 *   subtree of v.
 * .
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

#ifndef UPO_BST_H
#define UPO_BST_H


#include <stddef.h>


/** \brief Declares the Binary Search Tree type. */
typedef struct upo_bst_s* upo_bst_t;

/**
 * \brief The type for key comparison functions.
 *
 * Declares the type for key comparison functions that are used to compare keys
 * stored in the binary search tree.
 * A comparison function takes two parameters:
 * - The first parameter is a pointer to the first key to compare.
 * - The second parameter is a pointer to the second key to compare.
 * A comparison function returns a number less than, equal to, or greater than
 * zero if the first key (first argument) is less than, equal to, or greater
 * than the second key (second argument), respectively.
 */
typedef int (*upo_bst_comparator_t)(const void*, const void*);

/**
 * \brief The type for visit functions.
 *
 * Declares the type for visit functions that are used in tree traversal.
 * A visit function takes two parameters:
 * - The first parameter is a pointer to the user-provided key stored in the
 *   node that is being visited.
 * - The second parameter is a pointer to the user-provided value associated to
 *   the key and stored in the node that is being visited.
 * - The third parameter is a pointer to additional information that is used by
 *   the visit function to perform its operation.
 *   For instance, if the purpose of the visit function is to count the number
 *   of nodes in the tree, its second parameter could be a pointer to an
 *   integer variable representing the node counter that it is updated each time
 *   the visit function is called.
 */
typedef void (*upo_bst_visitor_t)(void*, void*, void*);

/** \brief The type for nodes of list of keys. */
struct upo_bst_key_list_node_s
{
    void *key; /**< Pointer to the key. */
    struct upo_bst_key_list_node_s *next; /**< Pointer to the next node in the list. */
};
/** \brief Alias for the type for nodes of list of keys. */
typedef struct upo_bst_key_list_node_s upo_bst_key_list_node_t;

/** \brief The type for list of keys. */
typedef upo_bst_key_list_node_t* upo_bst_key_list_t;


/**
 * \brief Creates a new empty binary search tree.
 *
 * \param key_cmp A pointer to the function used to compare keys.
 * \return An empty binary search tree.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
upo_bst_t upo_bst_create(upo_bst_comparator_t key_cmp);

/**
 * \brief Destroys the given binary search tree together with data stored on it.
 *
 * \param tree The binary search tree to destroy.
 * \param destroy_data Tells whether the previously allocated memory for keys
 *  and values stored in this binary search tree must be freed (value `1`) or
 *  not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_bst_destroy(upo_bst_t tree, int destroy_data);

/**
 * \brief Removes all elements from the given binary search tree and destroys
 *  all data stored on it.
 *
 * \param tree The binary search tree to clear.
 * \param destroy_data Tells whether the previously allocated memory for keys
 *  and values stored in this binary search tree must be freed (value `1`) or
 *  not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_bst_clear(upo_bst_t tree, int destroy_data);

/**
 * \brief Insert the given value identified by the provided key in the given
 *  binary search tree.
 *
 * \param tree The binary search tree.
 * \param key The key.
 * \param value The value.
 * \return The replaced value in case of a duplicate, otherwise `NULL`.
 *
 * If the key is already present in the tree, the associated value is replaced
 * by the one provided as argument to this function.
 * The old value is returned so that its memory can be deallocated
 * (if necessary).
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void* upo_bst_put(upo_bst_t tree, void *key, void *value);

/**
 * \brief Returns the comparison function stored in the binary search tree.
 *
 * \param tree The binary search tree.
 * \return The comparison function.
 */
upo_bst_comparator_t upo_bst_get_comparator(const upo_bst_t tree);

/**
 * \brief Returns the value identified by the provided key in the given
 *  binary search tree.
 *
 * \param tree The binary search tree.
 * \param key The key.
 * \return The value associated to \a key, or `NULL` if the key is not found.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void* upo_bst_get(const upo_bst_t tree, const void *key);

/**
 * \brief Remove the value identified by the provided key in the given
 *  binary search tree.
 *
 * \param tree The binary search tree.
 * \param key The key.
 * \param destroy_data Tells whether the previously allocated memory for keys
 *  and values stored in this binary search tree must be freed (value `1`) or
 *  not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_bst_delete(upo_bst_t tree, const void *key, int destroy_data);

/**
 * \brief Tells if the given binary search tree contains an item identified by
 *  the given key.
 *
 * \param tree The binary search tree.
 * \param key The key.
 * \return `1` if the binary search tree contains an item identified by the
 *  given key, or `0` if the key is not found.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
int upo_bst_contains(const upo_bst_t tree, const void *key);

/**
 * \brief Inserts the given value identified by the provided key in the given
 *  binary search tree but ignores duplicates.
 *
 * \param tree The binary search tree.
 * \param key The key.
 * \param value The value.
 *
 * If the key is already present in the tree, no insertion takes place.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_bst_insert(upo_bst_t tree, void *key, void *value);

/**
 * \brief Returns the number of nodes stored on the given binary search tree.
 *
 * \param tree The binary search tree.
 * \return The number of nodes of the given binary search tree.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
size_t upo_bst_size(const upo_bst_t tree);

/**
 * \brief Tells if the given binary search tree is empty.
 *
 * \param tree The binary search tree.
 * \return `1` if the binary search tree is empty or `0` otherwise.
 *
 * A binary search tree is empty if it doesn't contain any node.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
int upo_bst_is_empty(const upo_bst_t tree);

/**
 * \brief Returns the height of the given binary search tree.
 *
 * \param tree The binary search tree.
 * \return The height of the given binary search tree.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
size_t upo_bst_height(const upo_bst_t tree);

/**
 * \brief Performs a depth-first in-order traversal of the tree.
 *
 * \param tree The binary search tree to traverse.
 * \param visit The visit function.
 * \param visit_context Additional information, passed to the visit function as
 *  third parameter.
 *
 * The depth-first in-order traversal consists in traversing the tree according
 * to the following recursive policy:
 * 1. Traverse the left subtree
 * 2. Visit the root of the current subtree
 * 3. Traverse the right subtree
 * .
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void *visit_context);

/**
 * \brief Returns the smallest key in the given binary search tree.
 *
 * \param tree The binary search tree.
 * \return The smallest key, or `NULL` if the tree is empty.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void* upo_bst_min(const upo_bst_t tree);

/**
 * \brief Returns the largest key in the given binary search tree.
 *
 * \param tree The binary search tree.
 * \return The largest key, or `NULL` if the tree is empty.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void* upo_bst_max(upo_bst_t tree);

/**
 * \brief Removes the key-value pair with the smallest key in the given
 *  binary search tree.
 *
 * \param tree The binary search tree.
 * \param destroy_data Tells whether the previously allocated memory for keys
 *  and values stored in this binary search tree must be freed (value `1`) or
 *  not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_bst_delete_min(upo_bst_t tree, int destroy_data);

/**
 * \brief Removes the key-value pair with the largest key in the given
 *  binary search tree.
 *
 * \param tree The binary search tree.
 * \param destroy_data Tells whether the previously allocated memory for keys
 *  and values stored in this binary search tree must be freed (value `1`) or
 *  not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_bst_delete_max(upo_bst_t tree, int destroy_data);

/**
 * \brief Returns the largest key in the binary search tree which is less than
 *  or equal to the given key.
 *
 * \param tree The binary search tree.
 * \param key The key.
 * \return The largest key which is less than or equal to the given key.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void* upo_bst_floor(const upo_bst_t tree, const void *key);

/**
 * \brief Returns the smallest key in the binary search tree which is greater
 *  than or equal to the given key.
 *
 * \param tree The binary search tree.
 * \param key The key.
 * \return The smallest key which is greater than or equal to the given key.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void* upo_bst_ceiling(const upo_bst_t tree, const void *key);

/**
 * \brief Returns the keys in the given binary search tree that are inside the
 *  provided range of keys.
 *
 * \param tree The binary search tree.
 * \param low_key The lower bound of the range of keys.
 * \param high_key The upper bound of the range of keys.
 * \return A singly-linked list of keys inside the provided range, or `NULL` if
 *  no key falls inside the range.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void *low_key, const void *high_key);

/**
 * \brief Returns the keys in the given binary search tree.
 *
 * \param tree The binary search tree.
 * \return A singly-linked list of keys, or `NULL` if the tree is empty.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree);

/**
 * \brief Checks if the given tree satisfies the binary search tree property.
 *
 * \param tree The binary search tree to check.
 * \param min_key The minimum value that a key can possibly take.
 * \param max_key The maximum value that a key can possibly take.
 * \return `1` is the given tree satisfies the binary search tree property, or
 *  `0` otherwise.
 *
 * The binary search tree property states that at every node of the tree:
 * - every key in the left child subtree of the node is less than the key stored in that node, and
 * - every key in the right child subtree of the node is greater than the key stored in that node.
 * .
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
int upo_bst_is_bst(const upo_bst_t tree, const void *min_key, const void *max_key);


#endif /* UPO_BST_H */
