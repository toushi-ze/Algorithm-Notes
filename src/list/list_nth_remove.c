/**
 * @file list_nth_remove.c
 * @brief Remove Nth node from end of list using two pointers
 */

#include "list/list_nth_remove.h"

list_node_t *list_nth_remove(list_node_t *head, int n)
{
    if (head == NULL || n <= 0) {
        return head;
    }

    list_node_t dummy;
    dummy.next = head;
    list_node_t *fast = &dummy;
    list_node_t *slow = &dummy;

    for (int i = 0; i <= n; i++) {
        if (fast == NULL) {
            return head;
        }
        fast = fast->next;
    }

    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    list_node_t *to_remove = slow->next;
    slow->next = to_remove->next;
    free(to_remove);

    return dummy.next;
}
