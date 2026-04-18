/**
 * @file list_reverse.c
 * @brief Reverse a linked list (iterative approach)
 */

#include "list/list_reverse.h"

list_node_t *list_reverse(list_node_t *head)
{
    list_node_t *prev = NULL;
    list_node_t *current = head;

    while (current != NULL) {
        list_node_t *next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}
