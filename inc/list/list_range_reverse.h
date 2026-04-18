/**
 * @file list_range_reverse.h
 * @brief Reverse nodes in a range [left, right]
 */

#ifndef LIST_RANGE_REVERSE_H
#define LIST_RANGE_REVERSE_H

#include "list/list_node.h"

#ifdef __cplusplus
extern "C" {
#endif

list_node_t *list_range_reverse(list_node_t *head, int left, int right);

#ifdef __cplusplus
}
#endif

#endif
