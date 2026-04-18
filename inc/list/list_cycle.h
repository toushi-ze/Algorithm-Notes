/**
 * @file list_cycle.h
 * @brief Linked list cycle detection
 */

#ifndef LIST_CYCLE_H
#define LIST_CYCLE_H

#include "list/list_node.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool list_cycle_check(list_node_t *head);

#ifdef __cplusplus
}
#endif

#endif
