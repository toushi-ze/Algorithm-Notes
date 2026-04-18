/**
 * @file list_merge.c
 * @brief Merge two sorted linked lists
 */

#include "list/list_merge.h"

list_node_t *list_merge(list_node_t *l1, list_node_t *l2)
{
    list_node_t dummy;
    list_node_t *tail = &dummy;
    dummy.next = NULL;

    while (l1 != NULL && l2 != NULL) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    /* Attach remaining nodes */
    tail->next = (l1 != NULL) ? l1 : l2;

    return dummy.next;
}
