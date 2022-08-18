/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file src/hashtable_private.h
 *
 * \brief Private header for the Hash Tbale abstract data type.
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

#ifndef UPO_HASHTABLE_PRIVATE_H
#define UPO_HASHTABLE_PRIVATE_H


#include <upo/hashtable.h>


/*** BEGIN of HASH TABLE with SEPARATE CHAINING ***/


/** \brief Type for nodes of the list of collisions. */
struct upo_ht_sepchain_list_node_s
{
    void *key; /**< Pointer to the user-provided key. */
    void *value; /**< Pointer to the value associated to the key. */
    struct upo_ht_sepchain_list_node_s *next; /**< Pointer to the next node in the list. */
};
/** \brief Alias for the type for nodes of the list of collisions. */
typedef struct upo_ht_sepchain_list_node_s upo_ht_sepchain_list_node_t;

/** \brief Type for slots of hash tables with separate chaining. */
struct upo_ht_sepchain_slot_s
{
    upo_ht_sepchain_list_node_t *head; /**< Pointer to the head of the list of collisions. */
};
/** \brief Alias for the type for slots of hash tables with separate chaining. */
typedef struct upo_ht_sepchain_slot_s upo_ht_sepchain_slot_t;

/** \brief Type for hash tables with separate chaining. */
struct upo_ht_sepchain_s
{
    upo_ht_sepchain_slot_t *slots; /**< The hash table as array of slots. */
    size_t capacity; /**< The capacity of the hash table. */
    size_t size; /**< The number of elements stored in the hash table. */
    upo_ht_hasher_t key_hash; /**< The key hash function. */
    upo_ht_comparator_t key_cmp; /**< The key comparison function. */
};


/*** END of HASH TABLE with SEPARATE CHAINING ***/


/*** BEGIN of HASH TABLE with LINEAR PROBING ***/


/** \brief Type for slots of hash tables with linear probing. */
struct upo_ht_linprob_slot_s
{
    void *key; /**< Pointer to the user-provided key. */
    void *value; /**< Pointer to the value associated to the key. */
    int tombstone; /**< Flag used to mark this slot as deleted. */
};

/** \brief Alias for type for slots of hash tables with linear probing. */
typedef struct upo_ht_linprob_slot_s upo_ht_linprob_slot_t;

/** \brief Type for hash tables with linear probing. */
struct upo_ht_linprob_s
{
    upo_ht_linprob_slot_t *slots; /**< The hash table as array of slots. */
    size_t capacity; /**< The capacity of the hash table. */
    size_t size; /**< The number of stored key-value pairs. */
    upo_ht_hasher_t key_hash; /**< The key hash function. */
    upo_ht_comparator_t key_cmp; /**< The key comparison function. */
};


/**
 * \brief Resize the given hash table to the given capacity.
 *
 * \param ht The hash table to resize.
 * \param n The new capacity.
 */
static void upo_ht_linprob_resize(upo_ht_linprob_t ht, size_t n);


/*** END of HASH TABLE with LINEAR PROBING ***/

void upo_ht_build_key_list(const void *key, upo_ht_key_list_t *list);

#endif /* UPO_HASHTABLE_PRIVATE_H */
