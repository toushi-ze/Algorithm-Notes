/**
 * @file stack.h
 * @brief Industrial-grade generic stack (LIFO) library
 *
 * This module provides a generic stack data structure built on top of the
 * generic linked list library. It supports arbitrary data types through
 * void* type erasure and custom free functions for automatic memory
 * management.
 *
 * All operations are O(1) except clear/destroy which are O(n).
 */

#ifndef STACK_H
#define STACK_H

#include "list/list.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque handle to stack structure
 */
typedef struct stack_s stack_t;

/**
 * @brief Create a new stack
 *
 * @param free_func Function to free element data (can be NULL for no
 *                  auto-free). If provided, ownership of data pointers
 *                  is transferred to the stack.
 * @return New stack handle, or NULL on allocation failure
 */
stack_t *stack_create(list_free_func_t free_func);

/**
 * @brief Destroy a stack and free all elements
 *
 * Frees all elements by calling the free_func (if provided) on each
 * element's data, then frees the stack structure itself. The caller's
 * pointer is set to NULL to prevent dangling pointer use.
 *
 * @param stack_ptr Pointer to stack handle (will be set to NULL)
 */
void stack_destroy(stack_t **stack_ptr);

/**
 * @brief Clear all elements from a stack (preserves stack structure)
 *
 * Removes and frees all elements, but the stack can be reused
 * afterwards.
 *
 * @param stack Stack handle
 * @return Error code (LIST_SUCCESS on success)
 */
list_error_t stack_clear(stack_t *stack);

/**
 * @brief Push an element onto the top of the stack
 *
 * @param stack Stack handle
 * @param data Data pointer to push (ownership transferred to stack)
 * @return Error code (LIST_SUCCESS on success, LIST_ERROR_NULL_POINTER
 *         if stack is NULL, LIST_ERROR_MEMORY_ALLOC on allocation failure)
 */
list_error_t stack_push(stack_t *stack, void *data);

/**
 * @brief Remove the top element from the stack
 *
 * The free_func (if provided) is called on the removed element's data.
 *
 * @param stack Stack handle
 * @return Error code (LIST_SUCCESS on success, LIST_ERROR_EMPTY_LIST
 *         if the stack is empty)
 */
list_error_t stack_pop(stack_t *stack);

/**
 * @brief Get the top element without removing it
 *
 * @param stack Stack handle (can be const)
 * @return Data pointer at the top, or NULL if stack is empty or NULL
 */
void *stack_top(const stack_t *stack);

/**
 * @brief Get the number of elements in the stack
 *
 * @param stack Stack handle (can be const)
 * @return Number of elements, or 0 if stack is NULL
 */
size_t stack_get_length(const stack_t *stack);

/**
 * @brief Check if the stack is empty
 *
 * @param stack Stack handle (can be const)
 * @return 1 if empty or NULL, 0 otherwise
 */
int stack_is_empty(const stack_t *stack);

#ifdef __cplusplus
}
#endif

#endif
