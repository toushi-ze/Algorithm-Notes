/**
 * @file list_range_reverse.c
 * @brief Reverse nodes in a range [left, right]
 */

#include "list/list_range_reverse.h"

list_node_t *list_range_reverse(list_node_t *head, int left, int right)
{
    if (head == NULL || left >= right) {
        return head;
    }

    list_node_t dummy;
    dummy.next = head;
    list_node_t *prev = &dummy;

    for (int i = 1; i < left; i++) {
        if (prev->next == NULL) {
            return head;
        }
        prev = prev->next;
    }

    list_node_t *current = prev->next;
    if (current == NULL) {
        return head;
    }

    for (int i = 0; i < right - left; i++) {
        list_node_t *next = current->next;
        if (next == NULL) {
            break;
        }
        current->next = next->next;
        next->next = prev->next;
        prev->next = next;
    }

    return dummy.next;
}
