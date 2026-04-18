/**
 * @file list_cycle_ii.c
 * @brief Find cycle entry point using Floyd's algorithm
 */

#include "list/list_cycle_ii.h"

list_node_t *list_cycle_entry_find(list_node_t *head)
{
    if (head == NULL || head->next == NULL) {
        return NULL;
    }

    list_node_t *slow = head;
    list_node_t *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            list_node_t *entry = head;
            while (entry != slow) {
                entry = entry->next;
                slow = slow->next;
            }
            return entry;
        }
    }

    return NULL; 
}
