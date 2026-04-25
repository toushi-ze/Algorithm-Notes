/**
 * @file stack.c
 * @brief Industrial-grade generic stack (LIFO) library implementation
 *
 * Implementation of the generic stack data structure, built on top of
 * the generic linked list library. Internal structure is opaque to
 * the caller.
 */

#include "stack/stack.h"
#include <stdlib.h>

/**
 * @brief Internal stack structure
 */
struct stack_s {
    list_t *list; /**< Underlying linked list */
};


stack_t *stack_create(list_free_func_t free_func)
{
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    if (stack == NULL) {
        return NULL;
    }

    stack->list = list_create(free_func, NULL);
    if (stack->list == NULL) {
        free(stack);
        return NULL;
    }

    return stack;
}

void stack_destroy(stack_t **stack_ptr)
{
    if (stack_ptr == NULL || *stack_ptr == NULL) {
        return;
    }

    stack_t *stack = *stack_ptr;
    list_destroy(&stack->list);
    free(stack);
    *stack_ptr = NULL;
}

list_error_t stack_clear(stack_t *stack)
{
    if (stack == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    return list_clear(stack->list);
}

list_error_t stack_push(stack_t *stack, void *data)
{
    if (stack == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    return list_head_insert(stack->list, data);
}

list_error_t stack_pop(stack_t *stack)
{
    if (stack == NULL) {
        return LIST_ERROR_NULL_POINTER;
    }

    if (list_get_length(stack->list) == 0) {
        return LIST_ERROR_EMPTY_LIST;
    }

    return list_index_remove(stack->list, 0);
}

void *stack_top(const stack_t *stack)
{
    if (stack == NULL) {
        return NULL;
    }

    return list_index_get((list_t *)stack->list, 0);
}

size_t stack_get_length(const stack_t *stack)
{
    if (stack == NULL) {
        return 0;
    }

    return list_get_length((list_t *)stack->list);
}

int stack_is_empty(const stack_t *stack)
{
    if (stack == NULL) {
        return 1;
    }

    return (list_get_length((list_t *)stack->list) == 0) ? 1 : 0;
}
