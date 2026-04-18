/**
 * @file list_k_group_reverse.c
 * @brief Reverse nodes in k-group chunks
 */

#include "list/list_k_group_reverse.h"

/**
 * @brief Reverse k nodes and return new head and tail
 */
static list_node_t *reverse_k_nodes(list_node_t *head, int k, list_node_t **new_tail)
{
    list_node_t *prev = NULL;
    list_node_t *current = head;

    for (int i = 0; i < k; i++) {
        list_node_t *next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *new_tail = head;
    return prev;
}

list_node_t *list_k_group_reverse(list_node_t *head, int k)
{
    if (head == NULL || k <= 1) {
        return head;
    }

    list_node_t *check = head;
    for (int i = 0; i < k; i++) {
        if (check == NULL) {
            return head;
        }
        check = check->next;
    }

    list_node_t *new_tail = NULL;
    list_node_t *new_head = reverse_k_nodes(head, k, &new_tail);

    new_tail->next = list_k_group_reverse(check, k);

    return new_head;
}
