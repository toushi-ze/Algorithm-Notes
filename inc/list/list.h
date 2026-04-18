#ifndef LIST_H
#define LIST_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque handle to linked list structure
 */
typedef struct list_s list_t;

/**
 * @brief Function pointer type for data comparison
 * @param data1 First data pointer
 * @param data2 Second data pointer
 * @return 0 if equal, negative if data1 < data2, positive if data1 > data2
 */
typedef int (*list_compare_func_t)(const void *data1, const void *data2);

/**
 * @brief Function pointer type for data cleanup
 * @param data Data pointer to be freed
 */
typedef void (*list_free_func_t)(void *data);

/**
 * @brief Function pointer type for traversal callback
 * @param data Data pointer at current node
 * @param user_data User-provided context data
 * @return 0 to continue traversal, non-zero to stop traversal
 */
typedef int (*list_foreach_func_t)(void *data, void *user_data);


/**
 * @brief Unified error code enumeration
 */
typedef enum {
    LIST_SUCCESS = 0,           /**< Operation completed successfully */
    LIST_ERROR_NULL_POINTER,    /**< Null pointer passed to function */
    LIST_ERROR_INDEX_OUT_OF_BOUNDS, /**< Index is out of valid range */
    LIST_ERROR_MEMORY_ALLOC,    /**< Memory allocation failed */
    LIST_ERROR_NOT_FOUND,       /**< Data not found in list */
    LIST_ERROR_EMPTY_LIST,      /**< List is empty */
    LIST_ERROR_INVALID_PARAM,   /**< Invalid parameter */
    LIST_ERROR_ALREADY_EXISTS,  /**< Data already exists (for unique lists) */
    LIST_ERROR_UNKNOWN          /**< Unknown error */
} list_error_t;


/**
 * @brief Iterator macro for traversing linked list
 *
 * Usage example:
 * @code
 * list_t *list = list_create(free, compare_func);
 * // ... populate list ...
 * LIST_FOR_EACH(list, data) {
 *     // Process data
 * }
 * @endcode
 */
#define LIST_FOR_EACH(list, data_var) \
    for (void *data_var = list_foreach_start(list); \
         data_var != NULL; \
         data_var = list_foreach_next(list))

/**
 * @brief Create a new linked list
 *
 * @param free_func Function to free node data (can be NULL for no auto-free)
 * @param compare_func Function to compare node data (can be NULL for no comparison)
 * @return New list handle, or NULL on failure
 */
list_t *list_create(list_free_func_t free_func, list_compare_func_t compare_func);

/**
 * @brief Destroy a linked list and all its nodes
 *
 * @param list_ptr Pointer to list handle (will be set to NULL after destruction)
 */
void list_destroy(list_t **list_ptr);

/**
 * @brief Clear all nodes from a list (preserves list structure)
 *
 * @param list List handle
 * @return Error code
 */
list_error_t list_clear(list_t *list);

/**
 * @brief Insert data at the head of the list
 *
 * @param list List handle
 * @param data Data pointer to insert (ownership transferred to list)
 * @return Error code
 */
list_error_t list_head_insert(list_t *list, void *data);

/**
 * @brief Insert data at the tail of the list (O(1) operation)
 *
 * @param list List handle
 * @param data Data pointer to insert (ownership transferred to list)
 * @return Error code
 */
list_error_t list_tail_insert(list_t *list, void *data);

/**
 * @brief Insert data at a specific index
 *
 * Supports positive indices (0 = head) and negative indices (-1 = tail).
 *
 * @param list List handle
 * @param index Index position (positive or negative)
 * @param data Data pointer to insert (ownership transferred to list)
 * @return Error code
 */
list_error_t list_index_insert(list_t *list, int index, void *data);

/**
 * @brief Remove node at specific index
 *
 * @param list List handle
 * @param index Index of node to remove
 * @return Error code
 */
list_error_t list_index_remove(list_t *list, int index);

/**
 * @brief Remove first node matching the specified value
 *
 * @param list List handle
 * @param data Data value to find and remove
 * @return Error code
 */
list_error_t list_value_remove(list_t *list, const void *data);

/**
 * @brief Remove all nodes matching the specified value
 *
 * @param list List handle
 * @param data Data value to find and remove
 * @return Error code
 */
list_error_t list_value_remove_all(list_t *list, const void *data);

/**
 * @brief Get data pointer at specific index
 *
 * @param list List handle
 * @param index Index of node
 * @return Data pointer, or NULL on error
 */
void *list_index_get(list_t *list, int index);

/**
 * @brief Get index of first node matching the specified value
 *
 * @param list List handle
 * @param data Data value to find
 * @return Index of first match, or -1 if not found
 */
int list_value_get_index(list_t *list, const void *data);

/**
 * @brief Get the length of the list (O(1) operation)
 *
 * @param list List handle
 * @return Number of nodes in list, or 0 on error
 */
size_t list_get_length(list_t *list);

/**
 * @brief Traverse list with callback function
 *
 * @param list List handle
 * @param callback Function to call for each node
 * @param user_data User-provided context data
 * @return Error code
 */
list_error_t list_foreach(list_t *list, list_foreach_func_t callback, void *user_data);

/**
 * @brief Start iteration (for iterator macro)
 *
 * @param list List handle
 * @return First data pointer, or NULL
 */
void *list_foreach_start(list_t *list);

/**
 * @brief Get next data in iteration (for iterator macro)
 *
 * @param list List handle
 * @return Next data pointer, or NULL
 */
void *list_foreach_next(list_t *list);

#ifdef __cplusplus
}
#endif

#endif
