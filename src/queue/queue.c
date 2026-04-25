/**
 * @file queue.c
 * @brief Industrial-grade generic queue (FIFO) library implementation
 *
 * Implementation of the generic queue data structure, built on top of
 * the generic linked list library. Internal structure is opaque to
 * the caller.
 */

#include "queue/queue.h"
#include <stdlib.h>

/**
 * @brief Internal queue structure
 */
struct queue_s {
    list_t *list; /**< Underlying linked list */
};


queue_t *queue_create(list_free_func_t free_func)
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    if (queue == NULL) {
        return NULL;
    }

    queue->list = list_create(free_func, NULL);
    if (queue->list == NULL) {
        free(queue);
        return NULL;
    }

    return queue;
}

void queue_destroy(queue_t **queue_ptr)
{
    if (queue_ptr == NULL || *queue_ptr == NULL) {
        return;
    }

    queue_t *queue = *queue_ptr;
    list_destroy(&queue->list);
    free(queue);
    *queue_ptr = NULL;
}

list_error_t queue_clear(queue_t *queue)
{
    if (queue == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    return list_clear(queue->list);
}

list_error_t queue_enqueue(queue_t *queue, void *data)
{
    if (queue == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    return list_tail_insert(queue->list, data);
}

list_error_t queue_dequeue(queue_t *queue)
{
    if (queue == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    if (list_get_length(queue->list) == 0) {
        return LIST_ERROR_EMPTY_LIST;
    }

    return list_index_remove(queue->list, 0);
}

void *queue_front(const queue_t *queue)
{
    if (queue == NULL) {
        return NULL;
    }

    return list_index_get((list_t *)queue->list, 0);
}

void *queue_back(const queue_t *queue)
{
    if (queue == NULL) {
        return NULL;
    }

    return list_index_get((list_t *)queue->list, -1);
}

size_t queue_get_length(const queue_t *queue)
{
    if (queue == NULL) {
        return 0;
    }

    return list_get_length((list_t *)queue->list);
}

int queue_is_empty(const queue_t *queue)
{
    if (queue == NULL) {
        return 1;
    }

    return (list_get_length((list_t *)queue->list) == 0) ? 1 : 0;
}
