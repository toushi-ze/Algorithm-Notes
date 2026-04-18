/**
 * @file list_k_group_reverse.h
 * @brief Reverse nodes in k-group chunks
 */

#ifndef LIST_K_GROUP_REVERSE_H
#define LIST_K_GROUP_REVERSE_H

#include "list/list_node.h"

#ifdef __cplusplus
extern "C" {
#endif

list_node_t *list_k_group_reverse(list_node_t *head, int k);

#ifdef __cplusplus
}
#endif

#endif
