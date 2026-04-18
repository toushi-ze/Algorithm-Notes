/**
 * @file list.c
 * @brief Generic linked list library implementation
 *
 * Internal implementation of the linked list data structure.
 * All internal structures and helper functions are static.
 */

#include "list/list.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Internal node structure
 */
typedef struct list_node_s {
    void *data;                     /**< Node data pointer */
    struct list_node_s *next;       /**< Pointer to next node */
} list_node_t;

/**
 * @brief Internal list structure
 */
struct list_s {
    list_node_t *head;              /**< Head node pointer */
    list_node_t *tail;              /**< Tail node pointer (for O(1) append) */
    size_t length;                  /**< Number of nodes in list */
    list_free_func_t free_func;     /**< Data cleanup function */
    list_compare_func_t compare_func; /**< Data comparison function */
    list_node_t *current_iter;      /**< Current iterator position */
};


/**
 * @brief Create a new node
 *
 * @param data Data pointer for the node
 * @return New node or NULL on failure
 */
static list_node_t *node_create(void *data)
{
    list_node_t *node = (list_node_t *)malloc(sizeof(list_node_t));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

/**
 * @brief Free a node and its data
 *
 * @param node Node to free
 * @param free_func Function to free node data (can be NULL)
 */
static void node_destroy(list_node_t *node, list_free_func_t free_func)
{
    if (node == NULL) {
        return;
    }
    if (free_func != NULL && node->data != NULL) {
        free_func(node->data);
    }
    free(node);
}

/**
 * @brief Calculate normalized index (handles negative indices)
 *
 * @param list List handle
 * @param index Index to normalize
 * @return Normalized index or -1 if invalid
 */
static int normalize_index(list_t *list, int index)
{
    if (list == NULL || list->length == 0) {
        return -1;
    }

    size_t len = list->length;

    if (index < 0) {
        index = (int)len + index;
    }

    if (index < 0 || (size_t)index >= len) {
        return -1;
    }

    return index;
}

/**
 * @brief Get node at specific index
 *
 * @param list List handle
 * @param index Normalized index
 * @return Node pointer or NULL
 */
static list_node_t *get_node_at_index(list_t *list, int index)
{
    if (list == NULL || index < 0 || (size_t)index >= list->length) {
        return NULL;
    }

    list_node_t *current = list->head;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    return current;
}

/**
 * @brief Remove node from list
 *
 * @param list List handle
 * @param node Node to remove
 * @param prev_node Previous node (NULL if removing head)
 * @return Error code
 */
static list_error_t remove_node(list_t *list, list_node_t *node, list_node_t *prev_node)
{
    if (list == NULL || node == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    if (prev_node == NULL) {
        list->head = node->next;
    } else {
        prev_node->next = node->next;
    }

    if (node == list->tail) {
        list->tail = prev_node;
    }

    node_destroy(node, list->free_func);
    list->length--;

    return LIST_SUCCESS;
}


list_t *list_create(list_free_func_t free_func, list_compare_func_t compare_func)
{
    list_t *list = (list_t *)malloc(sizeof(list_t));
    if (list == NULL) {
        return NULL;
    }

    memset(list, 0, sizeof(list_t));

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->free_func = free_func;
    list->compare_func = compare_func;
    list->current_iter = NULL;

    return list;
}

void list_destroy(list_t **list_ptr)
{
    if (list_ptr == NULL || *list_ptr == NULL) {
        return;
    }

    list_t *list = *list_ptr;

    list_node_t *current = list->head;
    while (current != NULL) {
        list_node_t *next = current->next;
        node_destroy(current, list->free_func);
        current = next;
    }

    free(list);
    *list_ptr = NULL;
}

list_error_t list_clear(list_t *list)
{
    if (list == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    list_node_t *current = list->head;
    while (current != NULL) {
        list_node_t *next = current->next;
        node_destroy(current, list->free_func);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->current_iter = NULL;

    return LIST_SUCCESS;
}

list_error_t list_head_insert(list_t *list, void *data)
{
    if (list == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    list_node_t *node = node_create(data);
    if (node == NULL) {
        return LIST_ERROR_MEMORY_ALLOC;
    }

    node->next = list->head;
    list->head = node;

    if (list->tail == NULL) {
        list->tail = node;
    }

    list->length++;
    return LIST_SUCCESS;
}

list_error_t list_tail_insert(list_t *list, void *data)
{
    if (list == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    list_node_t *node = node_create(data);
    if (node == NULL) {
        return LIST_ERROR_MEMORY_ALLOC;
    }

    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->length++;
    return LIST_SUCCESS;
}

list_error_t list_index_insert(list_t *list, int index, void *data)
{
    if (list == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    if (list->length == 0) {
        if (index == 0 || index == -1) {
            return list_head_insert(list, data);
        }
        return LIST_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    if (index == -1) {
        return list_tail_insert(list, data);
    }

    int norm_index;
    if (index < 0) {
        norm_index = (int)list->length + index;
    } else {
        norm_index = index;
    }

    if (norm_index < 0 || norm_index > (int)list->length) {
        return LIST_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    if (norm_index == 0) {
        return list_head_insert(list, data);
    }

    if ((size_t)norm_index == list->length) {
        return list_tail_insert(list, data);
    }

    list_node_t *prev = get_node_at_index(list, norm_index - 1);
    if (prev == NULL) {
        return LIST_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    list_node_t *node = node_create(data);
    if (node == NULL) {
        return LIST_ERROR_MEMORY_ALLOC;
    }

    node->next = prev->next;
    prev->next = node;
    list->length++;
    return LIST_SUCCESS;
}

list_error_t list_index_remove(list_t *list, int index)
{
    if (list == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    if (list->length == 0) {
        return LIST_ERROR_EMPTY_LIST;
    }

    int norm_index = normalize_index(list, index);
    if (norm_index < 0) {
        return LIST_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    if (norm_index == 0) {
        list_node_t *old_head = list->head;
        list->head = old_head->next;
        if (list->tail == old_head) {
            list->tail = NULL;
        }
        node_destroy(old_head, list->free_func);
        list->length--;
        return LIST_SUCCESS;
    }

    list_node_t *prev = get_node_at_index(list, norm_index - 1);
    if (prev == NULL || prev->next == NULL) {
        return LIST_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    list_node_t *node_to_remove = prev->next;
    prev->next = node_to_remove->next;

    if (node_to_remove == list->tail) {
        list->tail = prev;
    }

    node_destroy(node_to_remove, list->free_func);
    list->length--;

    return LIST_SUCCESS;
}

list_error_t list_value_remove(list_t *list, const void *data)
{
    if (list == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    if (list->length == 0) {
        return LIST_ERROR_EMPTY_LIST;
    }

    if (list->compare_func == NULL) {
        return LIST_ERROR_INVALID_PARAM;
    }

    list_node_t *current = list->head;
    list_node_t *prev = NULL;

    while (current != NULL) {
        if (list->compare_func(current->data, data) == 0) {
            return remove_node(list, current, prev);
        }
        prev = current;
        current = current->next;
    }

    return LIST_ERROR_NOT_FOUND;
}

list_error_t list_value_remove_all(list_t *list, const void *data)
{
    if (list == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    if (list->length == 0) {
        return LIST_ERROR_EMPTY_LIST;
    }

    if (list->compare_func == NULL) {
        return LIST_ERROR_INVALID_PARAM;
    }

    int removed_count = 0;
    list_node_t *current = list->head;
    list_node_t *prev = NULL;

    while (current != NULL) {
        if (list->compare_func(current->data, data) == 0) {
            list_node_t *to_remove = current;
            current = current->next;

            if (prev == NULL) {
                list->head = current;
            } else {
                prev->next = current;
            }

            if (to_remove == list->tail) {
                list->tail = prev;
            }

            node_destroy(to_remove, list->free_func);
            list->length--;
            removed_count++;
        } else {
            prev = current;
            current = current->next;
        }
    }

    return removed_count > 0 ? LIST_SUCCESS : LIST_ERROR_NOT_FOUND;
}

void *list_index_get(list_t *list, int index)
{
    if (list == NULL) {
        return NULL;
    }

    int norm_index = normalize_index(list, index);
    if (norm_index < 0) {
        return NULL;
    }

    list_node_t *node = get_node_at_index(list, norm_index);
    return (node != NULL) ? node->data : NULL;
}

int list_value_get_index(list_t *list, const void *data)
{
    if (list == NULL || list->compare_func == NULL) {
        return -1;
    }

    list_node_t *current = list->head;
    int index = 0;

    while (current != NULL) {
        if (list->compare_func(current->data, data) == 0) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}

size_t list_get_length(list_t *list)
{
    if (list == NULL) {
        return 0;
    }
    return list->length;
}

list_error_t list_foreach(list_t *list, list_foreach_func_t callback, void *user_data)
{
    if (list == NULL || callback == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    list_node_t *current = list->head;
    while (current != NULL) {
        int result = callback(current->data, user_data);
        if (result != 0) {
            break;
        }
        current = current->next;
    }

    return LIST_SUCCESS;
}

void *list_foreach_start(list_t *list)
{
    if (list == NULL) {
        return NULL;
    }
    list->current_iter = list->head;
    return (list->current_iter != NULL) ? list->current_iter->data : NULL;
}

void *list_foreach_next(list_t *list)
{
    if (list == NULL || list->current_iter == NULL) {
        return NULL;
    }
    list->current_iter = list->current_iter->next;
    return (list->current_iter != NULL) ? list->current_iter->data : NULL;
}
