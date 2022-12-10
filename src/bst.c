/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
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

#include "bst_private.h"
#include <stdio.h>
#include <stdlib.h>

/**** EXERCISE #1 - BEGIN of FUNDAMENTAL OPERATIONS ****/

upo_bst_t upo_bst_create(upo_bst_comparator_t key_cmp)
{
    upo_bst_t tree = malloc(sizeof(struct upo_bst_s));
    if (tree == NULL)
    {
        perror("Unable to create a binary search tree");
        abort();
    }

    tree->root = NULL;
    tree->key_cmp = key_cmp;

    return tree;
}

void upo_bst_destroy(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear(tree, destroy_data);
        free(tree);
    }
}

void upo_bst_clear_impl(upo_bst_node_t *node, int destroy_data)
{
    if (node != NULL)
    {
        upo_bst_clear_impl(node->left, destroy_data);
        upo_bst_clear_impl(node->right, destroy_data);

        if (destroy_data)
        {
            free(node->key);
            free(node->value);
        }

        free(node);
    }
}

void upo_bst_clear(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear_impl(tree->root, destroy_data);
        tree->root = NULL;
    }
}

void *upo_bst_node_create(void *key, void *value)
{
    upo_bst_node_t *node = NULL;
    node = malloc(sizeof(struct upo_bst_node_s));
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void *upo_bst_put_impl(upo_bst_node_t *node, void *key, void *value, void *oldvalue, upo_bst_comparator_t cmp)
{
    oldvalue = NULL;
    if (node == NULL)
        return upo_bst_node_create(key, value);
    else if (cmp(key, node->key) < 0)
        node->left = upo_bst_put_impl(node->left, key, value, oldvalue, cmp);
    else if (cmp(key, node->key) > 0)
        node->right = upo_bst_put_impl(node->right, key, value, oldvalue, cmp);
    else
    {
        oldvalue = node->value;
        node->value = value;
    }
    return node;
}

void *upo_bst_put(upo_bst_t tree, void *key, void *value)
{
    void *oldvalue = NULL;
    tree->root = upo_bst_put_impl(tree->root, key, value, oldvalue, tree->key_cmp);
    return oldvalue;
}

void *upo_bst_insert_impl(upo_bst_node_t *node, void *key, void *value, upo_bst_comparator_t cmp)
{
    if (node == NULL)
        return upo_bst_node_create(key, value);
    else if (cmp(key, node->key) < 0)
        node->left = upo_bst_insert_impl(node->left, key, value, cmp);
    else if (cmp(key, node->key) > 0)
        node->right = upo_bst_insert_impl(node->right, key, value, cmp);

    return node;
}

void upo_bst_insert(upo_bst_t tree, void *key, void *value)
{
    tree->root = upo_bst_insert_impl(tree->root, key, value, tree->key_cmp);
}

void *upo_bst_get(const upo_bst_t tree, const void *key)
{
    upo_bst_node_t *node = upo_bst_get_impl(tree->root, key, tree->key_cmp);

    if (node != NULL)
        return node->value;
    return NULL;
}

void *upo_bst_get_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp)
{
    if (node == NULL)
        return NULL;

    if (cmp(key, node->key) < 0)
        return upo_bst_get_impl(node->left, key, cmp);
    else if (cmp(key, node->key) > 0)
        return upo_bst_get_impl(node->right, key, cmp);
    else
        return node;
}

int upo_bst_contains(const upo_bst_t tree, const void *key)
{
    if (tree == NULL)
        return 0;

    if (upo_bst_get_impl(tree->root, key, tree->key_cmp) != NULL)
        return 1;
    return 0;
}

void upo_bst_destroy_node(upo_bst_node_t *node, int destroy_data)
{
    if (node == NULL)
        return;

    if (destroy_data)
    {
        free(node->key);
        free(node->value);
    }
    free(node);
}

void *upo_bst_delete_2c_impl(upo_bst_node_t *node, int destroy_data, upo_bst_comparator_t cmp)
{
    upo_bst_node_t *temp = upo_bst_max_impl(node->left);
    node->key = temp->key;
    node->value = temp->value;
    node->left = upo_bst_delete_impl(node->left, temp->key, destroy_data, cmp);
    return node;
}

void *upo_bst_delete_1c_impl(upo_bst_node_t *node, int destroy_data)
{
    upo_bst_node_t *temp = node;
    if (node->left != NULL)
        node = node->left;
    else
        node = node->right;
    upo_bst_destroy_node(temp, destroy_data);
    return node;
}

void *upo_bst_delete_impl(upo_bst_node_t *node, const void *key, int destroy_data, upo_bst_comparator_t cmp)
{
    if (node == NULL)
        return NULL;

    if (cmp(key, node->key) < 0)
        node->left = upo_bst_delete_impl(node->left, key, destroy_data, cmp);
    else if (cmp(key, node->key) > 0)
        node->right = upo_bst_delete_impl(node->right, key, destroy_data, cmp);
    else if (node->left != NULL && node->right != NULL)
        node = upo_bst_delete_2c_impl(node, destroy_data, cmp);
    else
        node = upo_bst_delete_1c_impl(node, destroy_data);
    return node;
}

void upo_bst_delete(upo_bst_t tree, const void *key, int destroy_data)
{
    if(tree == NULL || tree->root == NULL)
        return;

    tree->root = upo_bst_delete_impl(tree->root, key, destroy_data, tree->key_cmp);
}

size_t upo_bst_size_impl(upo_bst_node_t *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return 1 + upo_bst_size_impl(node->left) + upo_bst_size_impl(node->right);
}

size_t upo_bst_size(const upo_bst_t tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    return upo_bst_size_impl(tree->root);
}

int upo_bst_is_leaf_impl(upo_bst_node_t *node)
{
    if (node->left == NULL && node->right == NULL)
        return 1;
    return 0;
}

size_t upo_bst_height_impl(upo_bst_node_t *node)
{
    // Checking if node is null or leaf
    if (node == NULL || upo_bst_is_leaf_impl(node))
        return 0;
    // Calculating height
    size_t left = upo_bst_height_impl(node->left);
    size_t right = upo_bst_height_impl(node->right);
    return 1 + (left > right ? left : right);
}

size_t upo_bst_height(const upo_bst_t tree)
{
    return upo_bst_height_impl(tree->root);
}

void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void *visit_context)
{
    upo_bst_traverse_in_order_impl(tree->root, visit, visit_context);
}

void upo_bst_traverse_in_order_impl(upo_bst_node_t *node, upo_bst_visitor_t visit, void *visit_context)
{
    if (node != NULL)
    {
        upo_bst_traverse_in_order_impl(node->left, visit, visit_context);
        visit(node->key, node->value, visit_context);
        upo_bst_traverse_in_order_impl(node->right, visit, visit_context);
    }
}

int upo_bst_is_empty(const upo_bst_t tree)
{
    if (tree == NULL)
        return 1;
    if (tree->root == NULL)
        return 1;
    return 0;
}

/**** EXERCISE #1 - END of FUNDAMENTAL OPERATIONS ****/

/**** EXERCISE #2 - BEGIN of EXTRA OPERATIONS ****/

void *upo_bst_min(const upo_bst_t tree)
{
    if (tree == NULL)
        return NULL;
    if (tree->root == NULL)
        return NULL;

    upo_bst_node_t *node = upo_bst_min_impl(tree->root);
    return node != NULL ? node->key : NULL;
}

void *upo_bst_min_impl(upo_bst_node_t *node)
{
    if (node == NULL)
        return NULL;
    else if (node->left != NULL)
        return upo_bst_min_impl(node->left);
    else
        return node;
}

void *upo_bst_max(const upo_bst_t tree)
{
    if (tree == NULL)
        return NULL;
    if (tree->root == NULL)
        return NULL;

    upo_bst_node_t *node = upo_bst_max_impl(tree->root);
    return node != NULL ? node->key : NULL;
}

void *upo_bst_max_impl(upo_bst_node_t *node)
{
    if (node == NULL)
        return NULL;
    else if (node->right != NULL)
        return upo_bst_max_impl(node->right);
    else
        return node;
}

void upo_bst_delete_min(upo_bst_t tree, int destroy_data)
{
    if (tree == NULL)
        return;
    if (tree->root == NULL)
        return;
    void *min = upo_bst_min(tree);
    tree->root = upo_bst_delete_impl(tree->root, min, destroy_data, tree->key_cmp);
}

void upo_bst_delete_max(upo_bst_t tree, int destroy_data)
{
    if (tree == NULL)
        return;
    if (tree->root == NULL)
        return;
    void *max = upo_bst_max(tree);
    tree->root = upo_bst_delete_impl(tree->root, max, destroy_data, tree->key_cmp);
}

void *upo_bst_floor(const upo_bst_t tree, const void *key)
{
    if (tree == NULL)
        return NULL;

    if (tree->root == NULL)
        return NULL;

    upo_bst_node_t *node = upo_bst_floor_impl(tree->root, tree->key_cmp, key);
    return (node != NULL) ? node->key : NULL;
}

void *upo_bst_floor_impl(upo_bst_node_t *node, upo_bst_comparator_t cmp, const void *key)
{
    if (node == NULL)
        return NULL;
    if (cmp(node->key, key) > 0)
        return upo_bst_floor_impl(node->left, cmp, key);
    else if (cmp(node->key, key) < 0)
    {
        upo_bst_node_t *fl = upo_bst_floor_impl(node->right, cmp, key);
        return fl != NULL ? fl : node;
    }
    else
        return node;
}

void *upo_bst_ceiling(const upo_bst_t tree, const void *key)
{
    if (tree == NULL)
        return NULL;

    if (tree->root == NULL)
        return NULL;

    upo_bst_node_t *node = upo_bst_ceiling_impl(tree->root, tree->key_cmp, key);
    return (node != NULL) ? node->key : NULL;
}

void *upo_bst_ceiling_impl(upo_bst_node_t *node, upo_bst_comparator_t cmp, const void *key)
{
    if (node == NULL)
        return NULL;
    if (cmp(node->key, key) < 0)
        return upo_bst_ceiling_impl(node->right, cmp, key);
    else if (cmp(node->key, key) > 0)
    {
        upo_bst_node_t *cl = upo_bst_ceiling_impl(node->left, cmp, key);
        return cl != NULL ? cl : node;
    }
    else
        return node;
}

upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void *low_key, const void *high_key)
{
    if (tree == NULL)
        return NULL;

    upo_bst_key_list_t list = NULL;
    upo_bst_keys_range_impl(tree->root, &list, tree->key_cmp, low_key, high_key);
    return list;
}

void upo_bst_keys_range_impl(const upo_bst_node_t *node, upo_bst_key_list_t *list, upo_bst_comparator_t cmp, const void *low_key, const void *high_key)
{
    if (node == NULL)
        return;
    upo_bst_keys_range_impl(node->left, list, cmp, low_key, high_key);
    if ((cmp(node->key, low_key) >= 0) && (cmp(node->key, high_key) <= 0))
    {
        upo_bst_key_list_node_t *list_node = malloc(sizeof(upo_bst_key_list_node_t));
        list_node->key = node->key;
        list_node->next = *list;
        *list = list_node;
    }
    upo_bst_keys_range_impl(node->right, list, cmp, low_key, high_key);
}

upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree)
{
    if (tree == NULL)
        return NULL;
    if (tree->root == NULL)
        return NULL;
    upo_bst_key_list_t list = NULL;
    upo_bst_keys_impl(tree->root, &list);
    return list;
}

void upo_bst_keys_impl(const upo_bst_node_t *node, upo_bst_key_list_t *list)
{
    if (node == NULL)
        return;
    upo_bst_keys_impl(node->left, list);
    upo_bst_key_list_node_t *list_node = malloc(sizeof(upo_bst_key_list_node_t));
    list_node->key = node->key;
    list_node->next = *list;
    *list = list_node;
    upo_bst_keys_impl(node->right, list);
}

int upo_bst_is_bst(const upo_bst_t tree, const void *min_key, const void *max_key)
{
    if (tree == NULL)
        return 1;
    return upo_bst_is_bst_impl(tree->root, min_key, max_key, tree->key_cmp);
}

int upo_bst_is_bst_impl(upo_bst_node_t *node, const void *min_key, const void *max_key, upo_bst_comparator_t cmp)
{
    if (node == NULL)
        return 1;

    int value = 1;
    if (cmp(node->key, min_key) > 0 && cmp(node->key, max_key) < 0)
    {
        value &= upo_bst_is_bst_impl(node->left, min_key, node->key, cmp);
        if (value)
            value &= upo_bst_is_bst_impl(node->right, node->key, max_key, cmp);
        return value;
    }
    return 0;
}

size_t upo_bst_rank(const upo_bst_t tree, const void *key)
{
    return upo_bst_rank_impl(tree->root, key, tree->key_cmp);
}

size_t upo_bst_rank_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp)
{
    if (node == NULL)
        return 0;

    if (cmp(node->key, key) < 0)
        return 1 + upo_bst_rank_impl(node->left, key, cmp) + upo_bst_rank_impl(node->right, key, cmp);

    return upo_bst_rank_impl(node->left, key, cmp);
}

void *upo_bst_predecessor(const upo_bst_t tree, const void *key)
{
    if (tree == NULL)
        return NULL;
    return upo_bst_predecessor_impl(tree->root, key, tree->key_cmp);
}

void *upo_bst_predecessor_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp)
{
    if (node == NULL)
        return NULL;
    if (cmp(node->key, key) == 0)
    {
        upo_bst_node_t *max = upo_bst_max_impl(node->left);
        return max != NULL ? max->key : NULL;
    }

    else if (cmp(node->key, key) > 0)
        return upo_bst_predecessor_impl(node->left, key, cmp);
    else
    {
        void *previuos = node->key;
        void *result = upo_bst_predecessor_impl(node->right, key, cmp);
        return result != NULL ? result : previuos;
    }
    return node->key;
}

void *upo_bst_get_value_depth(const upo_bst_t tree, const void *key, long *depth)
{
    if (tree == NULL)
    {
        *depth = -1;
        return NULL;
    }

    *depth = 0;
    return upo_bst_get_value_depth_impl(tree->root, key, depth, tree->key_cmp);
}

void *upo_bst_get_value_depth_impl(upo_bst_node_t *node, const void *key, long *depth, upo_bst_comparator_t cmp)
{
    if (node == NULL)
    {
        (*depth) = -1;
        return NULL;
    }

    if (cmp(node->key, key) > 0)
    {
        (*depth)++;
        return upo_bst_get_value_depth_impl(node->left, key, depth, cmp);
    }
    else if (cmp(node->key, key) < 0)
    {
        (*depth)++;
        return upo_bst_get_value_depth_impl(node->right, key, depth, cmp);
    }
    else
        return node->key;
}

upo_bst_key_list_t upo_bst_keys_le(const upo_bst_t tree, const void *key)
{
    upo_bst_key_list_t list = NULL;
    upo_bst_keys_le_impl(tree->root, key, &list, tree->key_cmp);
    return list;
}

void upo_bst_keys_le_impl(upo_bst_node_t *node, const void *key, upo_bst_key_list_t *list, upo_bst_comparator_t cmp)
{
    if (node != NULL)
    {        
        if (cmp(node->key, key) <= 0)
        {
            upo_bst_key_list_node_t *list_node = malloc(sizeof(upo_bst_key_list_node_t));
            list_node->key = node->key;
            list_node->next = *list;
            *list = list_node;
            upo_bst_keys_le_impl(node->right, key, list, cmp);
        }
        upo_bst_keys_le_impl(node->left, key, list, cmp);
    }
}

/**** EXERCISE #2 - END of EXTRA OPERATIONS ****/

upo_bst_comparator_t upo_bst_get_comparator(const upo_bst_t tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    return tree->key_cmp;
}
