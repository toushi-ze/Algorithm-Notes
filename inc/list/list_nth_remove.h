/**
 * @file list_nth_remove.h
 * @brief Remove Nth node from end of list
 */

#ifndef LIST_NTH_REMOVE_H
#define LIST_NTH_REMOVE_H

#include "list/list_node.h"

#ifdef __cplusplus
extern "C" {
#endif

list_node_t *list_nth_remove(list_node_t *head, int n);

#ifdef __cplusplus
}
#endif

#endif
