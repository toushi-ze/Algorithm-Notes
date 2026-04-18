/**
 * @file list_cycle.c
 * @brief Floyd's cycle detection algorithm
 */

#include "list/list_cycle.h"
#include <stdbool.h>

bool list_cycle_check(list_node_t *head)
{
    if (head == NULL || head->next == NULL) {
        return false;
    }

    list_node_t *slow = head;
    list_node_t *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}
