/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file upo/hashtable.h
 *
 * \brief The Hash Table (HT) abstract data type.
 *
 * Hash Tables are containers composed of unique keys (containing at most one of
 * each key value) that associates values of another type with the keys.
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

#ifndef UPO_HASHTABLE_H
#define UPO_HASHTABLE_H

#include <stddef.h>

/*** BEGIN of COMMON TYPES ***/

/** \brief The type for hash functions.
 *
 * Declares the type for key hash functions that are used to map key
 * space into the index space to use for indexing the hash table.
 * A hash function takes two parameters:
 * - The first parameter is a pointer to the key to hash.
 * - The second parameter is the capacity of the hash table.
 * A hash function returns a nonnegative number which represents a position
 * (index) in the hash table.
 */
typedef size_t (*upo_ht_hasher_t)(const void *, size_t);

/**
 * \brief The type for key comparison functions.
 *
 * Declares the type for key comparison functions that are used to compare keys
 * stored in the hash table.
 * A comparison function takes two parameters:
 * - The first parameter is a pointer to the first key to compare.
 * - The second parameter is a pointer to the second key to compare.
 * A comparison function returns a number less than, equal to, or greater than
 * zero if the first key (first argument) is less than, equal to, or greater
 * than the second key (second argument), respectively.
 */
typedef int (*upo_ht_comparator_t)(const void *, const void *);

/**
 * \brief The type for visit functions.
 *
 * Declares the type for visit functions that are used in hash table traversal.
 * A visit function takes two parameters:
 * - The first parameter is a pointer to the user-provided key that is being
 *   visited.
 * - The second parameter is a pointer to the user-provided value associated to
 *   the key that is being visited.
 * - The third parameter is a pointer to data that is used by the visit
 *   function to perform its operation.
 *   For instance, if the purpose of the visit function is to count the number
 *   of keys in the hash table, its second parameter could be a pointer to an
 *   integer variable representing the key counter that it is updated each time
 *   the visit function is called.
 */
typedef void (*upo_ht_visitor_t)(void *, void *, void *);

/** \brief The type for nodes of list of keys. */
struct upo_ht_key_list_node_s
{
    void *key;                           /**< Pointer to the key. */
    struct upo_ht_key_list_node_s *next; /**< Pointer to the next node in the list. */
};
/** \brief Alias for the type for nodes of list of keys. */
typedef struct upo_ht_key_list_node_s upo_ht_key_list_node_t;

/** \brief The type for list of keys. */
typedef upo_ht_key_list_node_t *upo_ht_key_list_t;

/*** END of COMMON TYPES ***/

/*** BEGIN of HASH TABLE with SEPARATE CHAINING ***/

/** \brief Default capacity of hash tables with separate chaining. */
#define UPO_HT_SEPCHAIN_DEFAULT_CAPACITY 997U

/** \brief Type for hash tables with separate chaining. */
typedef struct upo_ht_sepchain_s *upo_ht_sepchain_t;

/**
 * \brief Creates a new empty hash table.
 *
 * \param m The initial capacity of the hash table.
 * \param key_hash A pointer to the function used to hash keys.
 * \param key_cmp A pointer to the function used to compare keys.
 * \return An empty hash table.
 *
 * Worst-case complexity: linear in the capacity `m` of the hash table, `O(m)`.
 */
upo_ht_sepchain_t upo_ht_sepchain_create(size_t m, upo_ht_hasher_t key_hash, upo_ht_comparator_t key_cmp);

/**
 * \brief Destroys the given hash table.
 *
 * \param ht The hash table to destroy.
 * \param destroy_data Tells whether the previously allocated memory for data
 *  stored in the hash table must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the capacity `m` of the hash table, `O(m)`.
 */
void upo_ht_sepchain_destroy(upo_ht_sepchain_t ht, int destroy_data);

/**
 * \brief Removes all key-value pairs from the given hash table.
 *
 * \param ht The hash table to clear.
 * \param destroy_data Tells whether the previously allocated memory for data
 *  stored in the hash table must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the capacity `m` of the hash table, `O(m)`.
 */
void upo_ht_sepchain_clear(upo_ht_sepchain_t ht, int destroy_data);

/**
 * \brief Insert the given value identified by the provided key in the given
 *  hash table.
 *
 * \param ht The hash table.
 * \param key The key.
 * \param value The value.
 * \return The replaced value in case of a duplicate, otherwise `NULL`.
 *
 * If the key is already present in the hash table, the associated value is
 * replaced by the one provided as argument to this function.
 * The old value is returned so that its memory can be deallocated
 * (if necessary).
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void *upo_ht_sepchain_put(upo_ht_sepchain_t ht, void *key, void *value);

/**
 * \brief Inserts the given value identified by the provided key in the given
 *  hash table but ignores duplicates.
 *
 * \param ht The hash table.
 * \param key The key.
 * \param value The value.
 *
 * If the key is already present in the hash table, no insertion takes place.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_ht_sepchain_insert(upo_ht_sepchain_t ht, void *key, void *value);

/**
 * \brief Returns the value identified by the provided key in the given
 *  hash table.
 *
 * \param ht The hash table.
 * \param key The key.
 * \return The value associated to \a key, or `NULL` if the key is not found.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void *upo_ht_sepchain_get(const upo_ht_sepchain_t ht, const void *key);

/**
 * \brief Tells if the given hash table contains an item identified by
 *  the given key.
 *
 * \param ht The hash table.
 * \param key The key.
 * \return `1` if the hash table contains an item identified by the
 *  given key, or `0` if the key is not found.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
int upo_ht_sepchain_contains(const upo_ht_sepchain_t ht, const void *key);

/**
 * \brief Removes the value identified by the provided key in the given
 *  hash table.
 *
 * \param ht The hash table.
 * \param key The key.
 * \param destroy_data Tells whether the previously allocated memory for data,
 *  that is to be removed, must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_ht_sepchain_delete(upo_ht_sepchain_t ht, const void *key, int destroy_data);

/**
 * \brief Tells if the given hash table is empty.
 *
 * \param ht The hash table.
 * \return `1` if the hash table is empty or `0` otherwise.
 *
 * A hash table is empty if it doesn't contain any node.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
int upo_ht_sepchain_is_empty(const upo_ht_sepchain_t ht);

/**
 * \brief Returns the capacity of the hash table.
 *
 * \param ht The hash table.
 * \return The total number of slots of the hash tables.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
size_t upo_ht_sepchain_capacity(const upo_ht_sepchain_t ht);

/**
 * \brief Returns the size of the hash table.
 *
 * \param ht The hash table.
 * \return The number of keys stored in the hash tables.
 *
 * Worst-case complexity: linear in the capacity `m` of the hash table, `O(m)`.
 */
size_t upo_ht_sepchain_size(const upo_ht_sepchain_t ht);

/**
 * \brief Returns the load factor of the hash table.
 *
 * \param ht The hash table.
 * \return The load factor which is defined as the ratio between the number of
 *  stored keys (i.e., the keys) and the number of slots (i.e., the capacity).
 *
 * Worst-case complexity: constant, `O(1)`.
 */
double upo_ht_sepchain_load_factor(const upo_ht_sepchain_t ht);

/**
 * \brief Returns the keys in the given hash table.
 *
 * \param ht The hash table.
 * \return A singly-linked list of keys, or `NULL` if the hash table is empty.
 *
 * Worst-case complexity: linear in the number `m` of slots, `O(m)`.
 */
upo_ht_key_list_t upo_ht_sepchain_keys(const upo_ht_sepchain_t ht);

/**
 * \brief Performs a traversal of the hash table.
 *
 * \param tree The hash table to traverse.
 * \param visit The visit function.
 * \param visit_context Additional information, passed to the visit function as
 *  third parameter.
 *
 * Worst-case complexity: linear in the number `m` of slots, `O(m)`.
 */
void upo_ht_sepchain_traverse(const upo_ht_sepchain_t ht, upo_ht_visitor_t visit, void *visit_context);

/**
 * \brief Returns the key comparator function.
 *
 * \param ht The hash table.
 * \return The key comparator function.
 */
upo_ht_comparator_t upo_ht_sepchain_get_comparator(const upo_ht_sepchain_t ht);

/**
 * \brief Returns the key hasher function.
 *
 * \param ht The hash table.
 * \return The key hasher function.
 */
upo_ht_hasher_t upo_ht_sepchain_get_hasher(const upo_ht_sepchain_t ht);

/*** END of HASH TABLE with SEPARATE CHAINING ***/

/*** BEGIN of HASH TABLE with OPEN ADDRESSING ***/

/** \brief Initial capacity of hash tables with linear probing. */
#define UPO_HT_LINPROB_DEFAULT_CAPACITY 16U

/** \brief Type for hash tables with linear probing. */
typedef struct upo_ht_linprob_s *upo_ht_linprob_t;

/**
 * \brief Creates a new empty hash table.
 *
 * \param m The initial capacity of the hash table.
 * \param key_hash A pointer to the function used to hash keys.
 * \param key_cmp A pointer to the function used to compare keys.
 * \return An empty hash table.
 *
 * Worst-case complexity: linear in the capacity `m` of the hash table, `O(m)`.
 */
upo_ht_linprob_t upo_ht_linprob_create(size_t m, upo_ht_hasher_t hasher, upo_ht_comparator_t key_cmp);

/**
 * \brief Destroys the given hash table.
 *
 * \param ht The hash table to destroy.
 * \param destroy_data Tells whether the previously allocated memory for data
 *  stored in the hash table must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the capacity `m` of the hash table, `O(m)`.
 */
void upo_ht_linprob_destroy(upo_ht_linprob_t ht, int destroy_data);

/**
 * \brief Removes all key-value pairs from the given hash table.
 *
 * \param ht The hash table to clear.
 * \param destroy_data Tells whether the previously allocated memory for data
 *  stored in the hash table must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the capacity `m` of the hash table, `O(m)`.
 */
void upo_ht_linprob_clear(upo_ht_linprob_t ht, int destroy_data);

/**
 * \brief Insert the given value identified by the provided key in the given
 *  hash table.
 *
 * \param ht The hash table.
 * \param key The key.
 * \param value The value.
 * \return The replaced value in case of a duplicate, otherwise `NULL`.
 *
 * If the key is already present in the hash table, the associated value is
 * replaced by the one provided as argument to this function.
 * The old value is returned so that its memory can be deallocated
 * (if necessary).
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void *upo_ht_linprob_put(upo_ht_linprob_t ht, void *key, void *value);

/**
 * \brief Inserts the given value identified by the provided key in the given
 *  hash table but ignores duplicates.
 *
 * \param ht The hash table.
 * \param key The key.
 * \param value The value.
 *
 * If the key is already present in the hash table, no insertion takes place.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_ht_linprob_insert(upo_ht_linprob_t ht, void *key, void *value);

/**
 * \brief Returns the value identified by the provided key in the given
 *  hash table.
 *
 * \param ht The hash table.
 * \param key The key.
 * \return The value associated to \a key, or `NULL` if the key is not found.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void *upo_ht_linprob_get(const upo_ht_linprob_t ht, const void *key);

/**
 * \brief Tells if the given hash table contains an item identified by
 *  the given key.
 *
 * \param ht The hash table.
 * \param key The key.
 * \return `1` if the hash table contains an item identified by the
 *  given key, or `0` if the key is not found.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
int upo_ht_linprob_contains(const upo_ht_linprob_t ht, const void *key);

/**
 * \brief Removes the value identified by the provided key in the given
 *  hash table.
 *
 * \param ht The hash table.
 * \param key The key.
 * \param destroy_data Tells whether the previously allocated memory for data,
 *  that is to be removed, must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_ht_linprob_delete(upo_ht_linprob_t ht, const void *key, int destroy_data);

/**
 * \brief Tells if the given hash table is empty.
 *
 * \param ht The hash table.
 * \return `1` if the hash table is empty or `0` otherwise.
 *
 * A hash table is empty if it doesn't contain any node.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
int upo_ht_linprob_is_empty(const upo_ht_linprob_t ht);

/**
 * \brief Returns the capacity of the hash table.
 *
 * \param ht The hash table.
 * \return The total number of slots of the hash tables.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
size_t upo_ht_linprob_capacity(const upo_ht_linprob_t ht);

/**
 * \brief Returns the size of the hash table.
 *
 * \param ht The hash table.
 * \return The number of keys stored in the hash tables.
 *
 * Worst-case complexity: linear in the capacity `m` of the hash table, `O(m)`.
 */
size_t upo_ht_linprob_size(const upo_ht_linprob_t ht);

/**
 * \brief Returns the load factor of the hash table.
 *
 * \param ht The hash table.
 * \return The load factor which is defined as the ratio between the number of
 *  stored keys (i.e., the keys) and the number of slots (i.e., the capacity).
 *
 * Worst-case complexity: constant, `O(1)`.
 */
double upo_ht_linprob_load_factor(const upo_ht_linprob_t ht);

/**
 * \brief Returns the keys in the given hash table.
 *
 * \param ht The hash table.
 * \return A singly-linked list of keys, or `NULL` if the hash table is empty.
 *
 * Worst-case complexity: linear in the number `m` of slots, `O(m)`.
 */
upo_ht_key_list_t upo_ht_linprob_keys(const upo_ht_linprob_t ht);

/**
 * \brief Performs a traversal of the hash table.
 *
 * \param tree The hash table to traverse.
 * \param visit The visit function.
 * \param visit_context Additional information, passed to the visit function as
 *  third parameter.
 *
 * Worst-case complexity: linear in the number `m` of slots, `O(m)`.
 */
void upo_ht_linprob_traverse(const upo_ht_linprob_t ht, upo_ht_visitor_t visit, void *visit_context);

/**
 * \brief Returns the key comparator function.
 *
 * \param ht The hash table.
 * \return The key comparator function.
 */
upo_ht_comparator_t upo_ht_linprob_get_comparator(const upo_ht_linprob_t ht);

/**
 * \brief Returns the key hasher function.
 *
 * \param ht The hash table.
 * \return The key hasher function.
 */
upo_ht_hasher_t upo_ht_linprob_get_hasher(const upo_ht_linprob_t ht);

/*** END of HASH TABLE with OPEN ADDRESSING ***/

/*** BEGIN of HASH FUNCTIONS ***/

/**
 * \brief Hash function for integers that uses the division method.
 *
 * \param x The integer to be hashed.
 * \param m The number of possible hash values.
 * \return The hash value which is an integer number in \f$\{0,\ldots,m-1\}\f$.
 *
 * The division method is defined as:
 * \f[
 *   h(x) = x \bmod m
 * \f]
 * where:
 * - \f$y \bmod z\f$ means the remainder of the division \f$y / z\f$.
 * .
 */
size_t upo_ht_hash_int_div(const void *x, size_t m);

/**
 * \brief Hash function for integers that uses the multiplication method.
 *
 * \param x The integer to be hashed.
 * \param a A multiplicative constant in the range of (0,1).
 * \param m The number of possible hash values.
 * \return The hash value which is an integer number in \f$\{0,\ldots,m-1\}\f$.
 *
 * The multiplication method is defined as:
 * \f[
 *   h(x) = m \lfloor a x \bmod 1 \rfloor
 * \f]
 * where:
 * - \f$\lfloor y \rfloor\f$ means the floor of \f$y\f$, that is the greatest
 *   integer less than or equal to \f$y\f$.
 * - \f$y \bmod z\f$ means the remainder of the division \f$y / z\f$.
 * - \f$y \bmod 1\f$ is the fractional part of \f$y\f$, that is
 *   the result of \f$y - \lfloor y \rfloor\f$.
 * .
 */
size_t upo_ht_hash_int_mult(const void *x, double a, size_t m);

/**
 * \brief Hash function for integers that uses the multiplication method and
 *  the value of the multiplicative constant as proposed by Knuth.
 *
 * \param x The integer to be hashed.
 * \param m The number of possible hash values.
 * \return The hash value which is an integer number in \f$\{0,\ldots,m-1\}\f$.
 */
size_t upo_ht_hash_int_mult_knuth(const void *x, size_t m);

/**
 * \brief Hash function for strings.
 *
 * \param s The string to be hashed.
 * \param h0 The initial value for the hash value that is usually chosen
 *  randomly from a universal family mapping integer domain
 *  \f$\{0,\ldots,p-1\} \mapsto \{0,\ldots,m-1\}\f$.
 * \param a A multiplicative factor such that \f$a \in \{0,\ldots,p-1\}\f$ which
 *  is usually uniformly random.
 * \param m The number of possible hash values.
 * \return The hash value which is an integer number in \f$\{0,\ldots,m-1\}\f$.
 *
 * The implemented hash function is the following:
 * \f[
 *     h(k) = h_0 \left( \big(\sum_{i=0}^{\ell-1} k_i\cdot a^i \big) \bmod m \right),
 * \f]
 * where:
 * - \f$k=(k_0,\ldots,k_{\ell-1})\f$ is an array of characters of size \$\ell\$
 */
size_t upo_ht_hash_str(const void *s, size_t h0, size_t a, size_t m);

/**
 * \brief The Bernstein's hash function `djb2`.
 *
 * This hash function was first reported by Daniel J. Bernstein in comp.lang.c on 1991.
 *
 * See:
 * - https://groups.google.com/forum/#!msg/comp.lang.c/lSKWXiuNOAk/zstZ3SRhCjgJ
 * - http://www.cse.yorku.ca/~oz/hash.html
 * .
 */
size_t upo_ht_hash_str_djb2(const void *s, size_t m);

/**
 * \brief The Bernstein's hash function `djb2a`.
 *
 * This hash function is an alternative to the 'djb2' hash function that was
 * first reported by Daniel J. Bernstein in comp.lang.c on 1991.
 * Instead of using the sum operator it uses the XOR operator.
 *
 * See:
 * - https://groups.google.com/forum/#!msg/comp.lang.c/lSKWXiuNOAk/zstZ3SRhCjgJ
 * - http://www.cse.yorku.ca/~oz/hash.html
 * .
 */
size_t upo_ht_hash_str_djb2a(const void *s, size_t m);

/**
 * \brief The Java's hash function `hashCode`.
 *
 * See:
 * - https://docs.oracle.com/javase/8/docs/api/java/lang/String.html#hashCode--
 * .
 */
size_t upo_ht_hash_str_java(const void *s, size_t m);

/**
 * \brief The Kernighan and Ritchie's hash function proposed in the second
 *  edition of their C book.
 */
size_t upo_ht_hash_str_kr2e(const void *s, size_t m);

/**
 * \brief The SGI STL's hash function `hash_fun`.
 *
 */
size_t upo_ht_hash_str_sgistl(const void *s, size_t m);

/*** END of HASH FUNCTIONS ***/

/** \brief The hash table with separate chaining (based on ordered linked lists)
abstract data type. */
typedef struct upo_ht_sepchain_olist_s *upo_ht_sepchain_olist_t;

/** \brief Creates a new hash table with separate chaining (based on ordered linked
lists). */
upo_ht_sepchain_olist_t upo_ht_sepchain_olist_create(size_t m, upo_ht_hasher_t key_hash, upo_ht_comparator_t key_cmp);

/** \brief Destroys the given hash table with separate chaining (based on ordered
linked lists). */
void upo_ht_sepchain_olist_destroy(upo_ht_sepchain_olist_t ht, int destroy_data);

/** \brief Removes all elements from the given hash table with separate chaining (based
on ordered linked lists). */
void upo_ht_sepchain_olist_clear(upo_ht_sepchain_olist_t ht, int destroy_data);

/** \brief Returns value associated to the given key in the given hash table with
separate chaining (based on ordered linked lists). */
void *upo_ht_sepchain_olist_get(const upo_ht_sepchain_olist_t ht, const void *key);

/** \brief Tells whether the given key is present in the given hash table with separate
chaining (based on ordered linked lists). */
int upo_ht_sepchain_olist_contains(const upo_ht_sepchain_olist_t ht, const void *key);

/** \brief Inserts/updates the given key-value pair into the given hash table with
separate chaining (based on ordered linked lists). */
void *upo_ht_sepchain_olist_put(upo_ht_sepchain_olist_t ht, void *key, void *value);

/** \brief Inserts the given key-value pair into the given hash table with separate
chaining (based on ordered linked lists); updates are ignored. */
void upo_ht_sepchain_olist_insert(upo_ht_sepchain_olist_t ht, void *key, void *value);

/** \brief Removes the key-value pair associated to the given key from the given hash
table with separate chaining (based on ordered linked lists). */
void upo_ht_sepchain_olist_delete(upo_ht_sepchain_olist_t ht, const void *key, int destroy_data);

/** \brief Returns the capacity of the given hash table with separate chaining (based
on ordered linked lists). */
size_t upo_ht_sepchain_olist_capacity(const upo_ht_sepchain_olist_t ht);

/** \brief Returns the number of stored keys in the given hash table with separate
chaining (based on ordered linked lists). */

size_t upo_ht_sepchain_olist_size(const upo_ht_sepchain_olist_t ht);

/** \brief Returns the load factor of the given hash table with separate chaining
(based on ordered linked lists). */
double upo_ht_sepchain_olist_load_factor(const upo_ht_sepchain_olist_t ht);

/** \brief Tells whether the given hash table with separate chaining (based on ordered
linked lists) is empty. */
int upo_ht_sepchain_olist_is_empty(const upo_ht_sepchain_olist_t ht);

void upo_ht_linprob_merge(upo_ht_linprob_t dest_ht, const upo_ht_linprob_t src_ht);

#endif /* UPO_HASHTABLE_H */
