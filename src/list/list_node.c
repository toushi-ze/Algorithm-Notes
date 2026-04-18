/**
 * @file list_node.c
 * @brief Simple integer linked list node utilities
 */

#include "list/list_node.h"
#include <stdio.h>
#include <stdlib.h>

list_node_t *list_node_create(int val)
{
    list_node_t *node = (list_node_t *)malloc(sizeof(list_node_t));
    if (node == NULL) {
        return NULL;
    }
    node->val = val;
    node->next = NULL;
    return node;
}

list_node_t *list_from_array(int *arr, int size)
{
    if (arr == NULL || size <= 0) {
        return NULL;
    }

    list_node_t *head = list_node_create(arr[0]);
    if (head == NULL) {
        return NULL;
    }

    list_node_t *current = head;
    for (int i = 1; i < size; i++) {
        current->next = list_node_create(arr[i]);
        if (current->next == NULL) {
            list_free(head);
            return NULL;
        }
        current = current->next;
    }

    return head;
}

void list_print(list_node_t *head)
{
    printf("[");
    list_node_t *current = head;
    while (current != NULL) {
        printf("%d", current->val);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]");
}

void list_free(list_node_t *head)
{
    list_node_t *current = head;
    while (current != NULL) {
        list_node_t *next = current->next;
        free(current);
        current = next;
    }
}
