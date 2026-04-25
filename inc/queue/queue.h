/**
 * @file queue.h
 * @brief Industrial-grade generic queue (FIFO) library
 *
 * This module provides a generic queue data structure built on top of the
 * generic linked list library. It supports arbitrary data types through
 * void* type erasure and custom free functions for automatic memory
 * management.
 *
 * Enqueue (insert) and dequeue (remove) are both O(1) operations.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "list/list.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque handle to queue structure
 */
typedef struct queue_s queue_t;

/**
 * @brief Create a new queue
 *
 * @param free_func Function to free element data (can be NULL for no
 *                  auto-free). If provided, ownership of data pointers
 *                  is transferred to the queue.
 * @return New queue handle, or NULL on allocation failure
 */
queue_t *queue_create(list_free_func_t free_func);

/**
 * @brief Destroy a queue and free all elements
 *
 * Frees all elements by calling the free_func (if provided) on each
 * element's data, then frees the queue structure itself. The caller's
 * pointer is set to NULL to prevent dangling pointer use.
 *
 * @param queue_ptr Pointer to queue handle (will be set to NULL)
 */
void queue_destroy(queue_t **queue_ptr);

/**
 * @brief Clear all elements from a queue (preserves queue structure)
 *
 * Removes and frees all elements, but the queue can be reused
 * afterwards.
 *
 * @param queue Queue handle
 * @return Error code (LIST_SUCCESS on success)
 */
list_error_t queue_clear(queue_t *queue);

/**
 * @brief Enqueue (add) an element to the back of the queue
 *
 * @param queue Queue handle
 * @param data Data pointer to enqueue (ownership transferred to queue)
 * @return Error code (LIST_SUCCESS on success, LIST_ERROR_NULL_POINTER
 *         if queue is NULL, LIST_ERROR_MEMORY_ALLOC on allocation failure)
 */
list_error_t queue_enqueue(queue_t *queue, void *data);

/**
 * @brief Dequeue (remove) the front element from the queue
 *
 * The free_func (if provided) is called on the removed element's data.
 *
 * @param queue Queue handle
 * @return Error code (LIST_SUCCESS on success, LIST_ERROR_EMPTY_LIST
 *         if the queue is empty)
 */
list_error_t queue_dequeue(queue_t *queue);

/**
 * @brief Get the front element without removing it
 *
 * @param queue Queue handle (can be const)
 * @return Data pointer at the front, or NULL if queue is empty or NULL
 */
void *queue_front(const queue_t *queue);

/**
 * @brief Get the back element without removing it
 *
 * @param queue Queue handle (can be const)
 * @return Data pointer at the back, or NULL if queue is empty or NULL
 */
void *queue_back(const queue_t *queue);

/**
 * @brief Get the number of elements in the queue
 *
 * @param queue Queue handle (can be const)
 * @return Number of elements, or 0 if queue is NULL
 */
size_t queue_get_length(const queue_t *queue);

/**
 * @brief Check if the queue is empty
 *
 * @param queue Queue handle (can be const)
 * @return 1 if empty or NULL, 0 otherwise
 */
int queue_is_empty(const queue_t *queue);

#ifdef __cplusplus
}
#endif

#endif
