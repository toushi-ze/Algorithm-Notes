/**
 * @file list_node.h
 * @brief Simple integer linked list node for algorithm implementations
 */

#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Simple singly linked list node for integer values
 */
typedef struct list_node {
    int val;
    struct list_node *next;
} list_node_t;

/**
 * @brief Create a new node with given value
 */
list_node_t *list_node_create(int val);

/**
 * @brief Create a linked list from an array
 */
list_node_t *list_from_array(int *arr, int size);

/**
 * @brief Print linked list as [val1, val2, ...]
 */
void list_print(list_node_t *head);

/**
 * @brief Free entire linked list
 */
void list_free(list_node_t *head);

#ifdef __cplusplus
}
#endif

#endif
