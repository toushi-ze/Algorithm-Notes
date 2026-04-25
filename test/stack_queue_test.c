/**
 * @file stack_queue_test.c
 * @brief Unit tests for generic stack and queue libraries
 *
 * Comprehensive test suite covering all APIs for both stack and queue,
 * including int, string, and custom struct data types.
 */

#include "queue/queue.h"
#include "stack/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* MSVC compatibility for strdup */
#ifdef _MSC_VER
#define strdup _strdup
#endif

/* Test counters */
static int tests_passed = 0;
static int tests_failed = 0;

/* Test result macro */
#define TEST_ASSERT(condition, message) \
    do { \
        if (condition) { \
            tests_passed++; \
            printf("[PASS] %s\n", message); \
        } else { \
            tests_failed++; \
            printf("[FAIL] %s (line %d)\n", message, __LINE__); \
        } \
    } while (0)

/* Custom structure for testing */
typedef struct {
    int id;
    char name[32];
} person_t;

static void int_free(void *data)
{
    free(data);
}

static void string_free(void *data)
{
    free(data);
}

static void person_free(void *data)
{
    free(data);
}

/* ==========================================================================
 * Stack Test Cases
 * ========================================================================== */

static void test_stack_create_destroy(void)
{
    printf("\n--- Testing stack_create and stack_destroy ---\n");

    /* Test create with NULL free function */
    stack_t *s1 = stack_create(NULL);
    TEST_ASSERT(s1 != NULL, "Create stack with NULL free func");
    stack_destroy(&s1);
    TEST_ASSERT(s1 == NULL, "Destroy sets pointer to NULL");

    /* Test create with custom free function */
    stack_t *s2 = stack_create(int_free);
    TEST_ASSERT(s2 != NULL, "Create stack with int_free");
    stack_destroy(&s2);

    /* Test destroy with NULL pointer */
    stack_destroy(NULL);
    stack_destroy(&s1); /* Double destroy should be safe */
    TEST_ASSERT(1, "Destroy handles NULL gracefully");
}

static void test_stack_clear(void)
{
    printf("\n--- Testing stack_clear ---\n");

    stack_t *stack = stack_create(int_free);
    TEST_ASSERT(stack != NULL, "Create stack for clear test");

    /* Clear empty stack */
    list_error_t err = stack_clear(stack);
    TEST_ASSERT(err == LIST_SUCCESS, "Clear empty stack succeeds");
    TEST_ASSERT(stack_get_length(stack) == 0, "Empty stack has length 0");

    /* Push some items */
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        stack_push(stack, val);
    }
    TEST_ASSERT(stack_get_length(stack) == 5, "Stack has 5 items after push");

    /* Clear non-empty stack */
    err = stack_clear(stack);
    TEST_ASSERT(err == LIST_SUCCESS, "Clear non-empty stack succeeds");
    TEST_ASSERT(stack_get_length(stack) == 0, "Stack length is 0 after clear");
    TEST_ASSERT(stack_is_empty(stack) == 1, "Stack is empty after clear");

    /* Can still use stack after clear */
    int *val = malloc(sizeof(int));
    *val = 42;
    err = stack_push(stack, val);
    TEST_ASSERT(err == LIST_SUCCESS, "Can push after clear");
    TEST_ASSERT(stack_get_length(stack) == 1, "Stack has 1 item after re-push");

    stack_destroy(&stack);
}

static void test_stack_push_pop(void)
{
    printf("\n--- Testing stack_push and stack_pop ---\n");

    stack_t *stack = stack_create(int_free);

    /* Push to empty stack */
    int *val1 = malloc(sizeof(int));
    *val1 = 10;
    list_error_t err = stack_push(stack, val1);
    TEST_ASSERT(err == LIST_SUCCESS, "Push to empty stack");
    TEST_ASSERT(stack_get_length(stack) == 1, "Length is 1 after push");

    /* Push more items */
    int *val2 = malloc(sizeof(int));
    *val2 = 20;
    stack_push(stack, val2);
    int *val3 = malloc(sizeof(int));
    *val3 = 30;
    stack_push(stack, val3);
    TEST_ASSERT(stack_get_length(stack) == 3, "Length is 3 after 3 pushes");

    /* Pop items (LIFO order: 30, 20, 10) */
    err = stack_pop(stack);
    TEST_ASSERT(err == LIST_SUCCESS, "Pop succeeds");
    TEST_ASSERT(stack_get_length(stack) == 2, "Length is 2 after pop");

    err = stack_pop(stack);
    TEST_ASSERT(err == LIST_SUCCESS, "Second pop succeeds");
    TEST_ASSERT(stack_get_length(stack) == 1, "Length is 1 after second pop");

    err = stack_pop(stack);
    TEST_ASSERT(err == LIST_SUCCESS, "Third pop succeeds");
    TEST_ASSERT(stack_get_length(stack) == 0, "Length is 0 after third pop");

    /* Pop from empty stack */
    err = stack_pop(stack);
    TEST_ASSERT(err == LIST_ERROR_EMPTY_LIST, "Pop from empty stack returns error");

    /* Test NULL stack */
    err = stack_push(NULL, val1);
    TEST_ASSERT(err == LIST_ERROR_NULL_POINTER, "Push to NULL stack returns error");
    err = stack_pop(NULL);
    TEST_ASSERT(err == LIST_ERROR_NULL_POINTER, "Pop from NULL stack returns error");

    stack_destroy(&stack);
}

static void test_stack_lifo_order(void)
{
    printf("\n--- Testing stack LIFO order ---\n");

    stack_t *stack = stack_create(int_free);

    /* Push 1, 2, 3 */
    for (int i = 1; i <= 3; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        stack_push(stack, val);
    }

    /* Verify LIFO order by checking top then popping */
    TEST_ASSERT(*(int *)stack_top(stack) == 3, "Top is 3 (last pushed)");
    stack_pop(stack);
    TEST_ASSERT(*(int *)stack_top(stack) == 2, "Top is 2 after pop");
    stack_pop(stack);
    TEST_ASSERT(*(int *)stack_top(stack) == 1, "Top is 1 after second pop");
    stack_pop(stack);

    TEST_ASSERT(stack_is_empty(stack) == 1, "Stack is empty after all pops");

    stack_destroy(&stack);
}

static void test_stack_top(void)
{
    printf("\n--- Testing stack_top ---\n");

    stack_t *stack = stack_create(NULL);

    /* Top of empty stack */
    void *data = stack_top(stack);
    TEST_ASSERT(data == NULL, "Top of empty stack returns NULL");

    /* Top of NULL stack */
    data = stack_top(NULL);
    TEST_ASSERT(data == NULL, "Top of NULL stack returns NULL");

    /* Push and check top */
    int *val = malloc(sizeof(int));
    *val = 42;
    stack_push(stack, val);
    data = stack_top(stack);
    TEST_ASSERT(data == val, "Top returns correct pointer");
    TEST_ASSERT(*(int *)data == 42, "Top value is 42");

    /* Top does not remove element */
    TEST_ASSERT(stack_get_length(stack) == 1, "Top does not change length");

    free(val);
    stack_destroy(&stack);
}

static void test_stack_is_empty(void)
{
    printf("\n--- Testing stack_is_empty ---\n");

    /* NULL stack */
    TEST_ASSERT(stack_is_empty(NULL) == 1, "NULL stack is empty");

    stack_t *stack = stack_create(NULL);
    TEST_ASSERT(stack_is_empty(stack) == 1, "New stack is empty");

    int val = 10;
    stack_push(stack, &val);
    TEST_ASSERT(stack_is_empty(stack) == 1 ? 0 : 1, "Stack with item is not empty");
    TEST_ASSERT(stack_get_length(stack) > 0, "Stack length > 0 when not empty");

    stack_pop(stack);
    TEST_ASSERT(stack_is_empty(stack) == 1, "Stack is empty after pop");

    stack_destroy(&stack);
}

static void test_stack_string_data(void)
{
    printf("\n--- Testing stack with string data ---\n");

    stack_t *stack = stack_create(string_free);

    /* Push strings */
    stack_push(stack, strdup("hello"));
    stack_push(stack, strdup("world"));
    stack_push(stack, strdup("test"));

    TEST_ASSERT(stack_get_length(stack) == 3, "String stack has 3 items");

    /* Verify LIFO order */
    TEST_ASSERT(strcmp((char *)stack_top(stack), "test") == 0,
                "Top is 'test' (last pushed)");
    stack_pop(stack);
    TEST_ASSERT(strcmp((char *)stack_top(stack), "world") == 0,
                "Top is 'world' after pop");
    stack_pop(stack);
    TEST_ASSERT(strcmp((char *)stack_top(stack), "hello") == 0,
                "Top is 'hello' after second pop");

    stack_destroy(&stack);
}

static void test_stack_custom_struct(void)
{
    printf("\n--- Testing stack with custom struct ---\n");

    stack_t *stack = stack_create(person_free);

    person_t *p1 = malloc(sizeof(person_t));
    p1->id = 1;
    strcpy(p1->name, "Alice");
    stack_push(stack, p1);

    person_t *p2 = malloc(sizeof(person_t));
    p2->id = 2;
    strcpy(p2->name, "Bob");
    stack_push(stack, p2);

    person_t *p3 = malloc(sizeof(person_t));
    p3->id = 3;
    strcpy(p3->name, "Charlie");
    stack_push(stack, p3);

    TEST_ASSERT(stack_get_length(stack) == 3, "Person stack has 3 items");

    /* Verify LIFO: Charlie is on top */
    person_t *top = (person_t *)stack_top(stack);
    TEST_ASSERT(top->id == 3, "Top person has ID 3");
    TEST_ASSERT(strcmp(top->name, "Charlie") == 0, "Top person is Charlie");

    stack_pop(stack);
    top = (person_t *)stack_top(stack);
    TEST_ASSERT(top->id == 2, "Next person has ID 2");
    TEST_ASSERT(strcmp(top->name, "Bob") == 0, "Next person is Bob");

    stack_destroy(&stack);
}

static void test_stack_reuse_after_clear(void)
{
    printf("\n--- Testing stack reuse after clear ---\n");

    stack_t *stack = stack_create(int_free);

    /* First use */
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        stack_push(stack, val);
    }
    TEST_ASSERT(stack_get_length(stack) == 5, "Stack has 5 items after first use");

    stack_clear(stack);
    TEST_ASSERT(stack_get_length(stack) == 0, "Stack is empty after clear");

    /* Second use */
    for (int i = 10; i < 15; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        stack_push(stack, val);
    }
    TEST_ASSERT(stack_get_length(stack) == 5, "Stack has 5 items after second use");
    TEST_ASSERT(*(int *)stack_top(stack) == 14, "Top is 14 (last pushed)");

    stack_destroy(&stack);
}

/* ==========================================================================
 * Queue Test Cases
 * ========================================================================== */

static void test_queue_create_destroy(void)
{
    printf("\n--- Testing queue_create and queue_destroy ---\n");

    /* Test create with NULL free function */
    queue_t *q1 = queue_create(NULL);
    TEST_ASSERT(q1 != NULL, "Create queue with NULL free func");
    queue_destroy(&q1);
    TEST_ASSERT(q1 == NULL, "Destroy sets pointer to NULL");

    /* Test create with custom free function */
    queue_t *q2 = queue_create(int_free);
    TEST_ASSERT(q2 != NULL, "Create queue with int_free");
    queue_destroy(&q2);

    /* Test destroy with NULL pointer */
    queue_destroy(NULL);
    queue_destroy(&q1); /* Double destroy should be safe */
    TEST_ASSERT(1, "Destroy handles NULL gracefully");
}

static void test_queue_clear(void)
{
    printf("\n--- Testing queue_clear ---\n");

    queue_t *queue = queue_create(int_free);
    TEST_ASSERT(queue != NULL, "Create queue for clear test");

    /* Clear empty queue */
    list_error_t err = queue_clear(queue);
    TEST_ASSERT(err == LIST_SUCCESS, "Clear empty queue succeeds");
    TEST_ASSERT(queue_get_length(queue) == 0, "Empty queue has length 0");

    /* Enqueue some items */
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        queue_enqueue(queue, val);
    }
    TEST_ASSERT(queue_get_length(queue) == 5, "Queue has 5 items after enqueue");

    /* Clear non-empty queue */
    err = queue_clear(queue);
    TEST_ASSERT(err == LIST_SUCCESS, "Clear non-empty queue succeeds");
    TEST_ASSERT(queue_get_length(queue) == 0, "Queue length is 0 after clear");
    TEST_ASSERT(queue_is_empty(queue) == 1, "Queue is empty after clear");

    /* Can still use queue after clear */
    int *val = malloc(sizeof(int));
    *val = 42;
    err = queue_enqueue(queue, val);
    TEST_ASSERT(err == LIST_SUCCESS, "Can enqueue after clear");
    TEST_ASSERT(queue_get_length(queue) == 1, "Queue has 1 item after re-enqueue");

    queue_destroy(&queue);
}

static void test_queue_enqueue_dequeue(void)
{
    printf("\n--- Testing queue_enqueue and queue_dequeue ---\n");

    queue_t *queue = queue_create(int_free);

    /* Enqueue to empty queue */
    int *val1 = malloc(sizeof(int));
    *val1 = 10;
    list_error_t err = queue_enqueue(queue, val1);
    TEST_ASSERT(err == LIST_SUCCESS, "Enqueue to empty queue");
    TEST_ASSERT(queue_get_length(queue) == 1, "Length is 1 after enqueue");

    /* Enqueue more items */
    int *val2 = malloc(sizeof(int));
    *val2 = 20;
    queue_enqueue(queue, val2);
    int *val3 = malloc(sizeof(int));
    *val3 = 30;
    queue_enqueue(queue, val3);
    TEST_ASSERT(queue_get_length(queue) == 3, "Length is 3 after 3 enqueues");

    /* Dequeue items (FIFO order: 10, 20, 30) */
    err = queue_dequeue(queue);
    TEST_ASSERT(err == LIST_SUCCESS, "Dequeue succeeds");
    TEST_ASSERT(queue_get_length(queue) == 2, "Length is 2 after dequeue");

    err = queue_dequeue(queue);
    TEST_ASSERT(err == LIST_SUCCESS, "Second dequeue succeeds");
    TEST_ASSERT(queue_get_length(queue) == 1, "Length is 1 after second dequeue");

    err = queue_dequeue(queue);
    TEST_ASSERT(err == LIST_SUCCESS, "Third dequeue succeeds");
    TEST_ASSERT(queue_get_length(queue) == 0, "Length is 0 after third dequeue");

    /* Dequeue from empty queue */
    err = queue_dequeue(queue);
    TEST_ASSERT(err == LIST_ERROR_EMPTY_LIST,
                "Dequeue from empty queue returns error");

    /* Test NULL queue */
    err = queue_enqueue(NULL, val1);
    TEST_ASSERT(err == LIST_ERROR_NULL_POINTER,
                "Enqueue to NULL queue returns error");
    err = queue_dequeue(NULL);
    TEST_ASSERT(err == LIST_ERROR_NULL_POINTER,
                "Dequeue from NULL queue returns error");

    queue_destroy(&queue);
}

static void test_queue_fifo_order(void)
{
    printf("\n--- Testing queue FIFO order ---\n");

    queue_t *queue = queue_create(int_free);

    /* Enqueue 1, 2, 3 */
    for (int i = 1; i <= 3; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        queue_enqueue(queue, val);
    }

    /* Verify FIFO order by checking front then dequeuing */
    TEST_ASSERT(*(int *)queue_front(queue) == 1, "Front is 1 (first enqueued)");
    queue_dequeue(queue);
    TEST_ASSERT(*(int *)queue_front(queue) == 2, "Front is 2 after dequeue");
    queue_dequeue(queue);
    TEST_ASSERT(*(int *)queue_front(queue) == 3, "Front is 3 after second dequeue");

    queue_destroy(&queue);
}

static void test_queue_front_back(void)
{
    printf("\n--- Testing queue_front and queue_back ---\n");

    queue_t *queue = queue_create(NULL);

    /* Front/back of empty queue */
    TEST_ASSERT(queue_front(queue) == NULL, "Front of empty queue is NULL");
    TEST_ASSERT(queue_back(queue) == NULL, "Back of empty queue is NULL");

    /* Front/back of NULL queue */
    TEST_ASSERT(queue_front(NULL) == NULL, "Front of NULL queue is NULL");
    TEST_ASSERT(queue_back(NULL) == NULL, "Back of NULL queue is NULL");

    /* Enqueue items */
    int vals[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
        queue_enqueue(queue, &vals[i]);
    }

    /* Check front and back */
    int *front = (int *)queue_front(queue);
    int *back = (int *)queue_back(queue);
    TEST_ASSERT(*front == 10, "Front is 10");
    TEST_ASSERT(*back == 30, "Back is 30");

    /* Front/back do not modify queue */
    TEST_ASSERT(queue_get_length(queue) == 3, "Length unchanged after front/back");

    /* Dequeue and check new front */
    queue_dequeue(queue);
    front = (int *)queue_front(queue);
    TEST_ASSERT(*front == 20, "Front is 20 after dequeue");

    /* Back remains the same */
    back = (int *)queue_back(queue);
    TEST_ASSERT(*back == 30, "Back is still 30");

    queue_destroy(&queue);
}

static void test_queue_is_empty(void)
{
    printf("\n--- Testing queue_is_empty ---\n");

    /* NULL queue */
    TEST_ASSERT(queue_is_empty(NULL) == 1, "NULL queue is empty");

    queue_t *queue = queue_create(NULL);
    TEST_ASSERT(queue_is_empty(queue) == 1, "New queue is empty");

    int val = 10;
    queue_enqueue(queue, &val);
    TEST_ASSERT(queue_is_empty(queue) == 0, "Queue with item is not empty");
    TEST_ASSERT(queue_get_length(queue) > 0, "Queue length > 0 when not empty");

    queue_dequeue(queue);
    TEST_ASSERT(queue_is_empty(queue) == 1, "Queue is empty after dequeue");

    queue_destroy(&queue);
}

static void test_queue_string_data(void)
{
    printf("\n--- Testing queue with string data ---\n");

    queue_t *queue = queue_create(string_free);

    /* Enqueue strings */
    queue_enqueue(queue, strdup("hello"));
    queue_enqueue(queue, strdup("world"));
    queue_enqueue(queue, strdup("test"));

    TEST_ASSERT(queue_get_length(queue) == 3, "String queue has 3 items");

    /* Verify FIFO order */
    TEST_ASSERT(strcmp((char *)queue_front(queue), "hello") == 0,
                "Front is 'hello' (first enqueued)");
    queue_dequeue(queue);
    TEST_ASSERT(strcmp((char *)queue_front(queue), "world") == 0,
                "Front is 'world' after dequeue");
    queue_dequeue(queue);
    TEST_ASSERT(strcmp((char *)queue_front(queue), "test") == 0,
                "Front is 'test' after second dequeue");

    queue_destroy(&queue);
}

static void test_queue_custom_struct(void)
{
    printf("\n--- Testing queue with custom struct ---\n");

    queue_t *queue = queue_create(person_free);

    person_t *p1 = malloc(sizeof(person_t));
    p1->id = 1;
    strcpy(p1->name, "Alice");
    queue_enqueue(queue, p1);

    person_t *p2 = malloc(sizeof(person_t));
    p2->id = 2;
    strcpy(p2->name, "Bob");
    queue_enqueue(queue, p2);

    person_t *p3 = malloc(sizeof(person_t));
    p3->id = 3;
    strcpy(p3->name, "Charlie");
    queue_enqueue(queue, p3);

    TEST_ASSERT(queue_get_length(queue) == 3, "Person queue has 3 items");

    /* Verify FIFO: Alice is at front */
    person_t *front = (person_t *)queue_front(queue);
    TEST_ASSERT(front->id == 1, "Front person has ID 1");
    TEST_ASSERT(strcmp(front->name, "Alice") == 0, "Front person is Alice");

    /* Charlie is at back */
    person_t *back = (person_t *)queue_back(queue);
    TEST_ASSERT(back->id == 3, "Back person has ID 3");
    TEST_ASSERT(strcmp(back->name, "Charlie") == 0, "Back person is Charlie");

    queue_dequeue(queue);
    front = (person_t *)queue_front(queue);
    TEST_ASSERT(front->id == 2, "Next front person has ID 2");
    TEST_ASSERT(strcmp(front->name, "Bob") == 0, "Next front person is Bob");

    queue_destroy(&queue);
}

static void test_queue_reuse_after_clear(void)
{
    printf("\n--- Testing queue reuse after clear ---\n");

    queue_t *queue = queue_create(int_free);

    /* First use */
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        queue_enqueue(queue, val);
    }
    TEST_ASSERT(queue_get_length(queue) == 5, "Queue has 5 items after first use");

    queue_clear(queue);
    TEST_ASSERT(queue_get_length(queue) == 0, "Queue is empty after clear");

    /* Second use */
    for (int i = 10; i < 15; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        queue_enqueue(queue, val);
    }
    TEST_ASSERT(queue_get_length(queue) == 5, "Queue has 5 items after second use");
    TEST_ASSERT(*(int *)queue_front(queue) == 10, "Front is 10 (first enqueued)");
    TEST_ASSERT(*(int *)queue_back(queue) == 14, "Back is 14 (last enqueued)");

    queue_destroy(&queue);
}

/* ==========================================================================
 * Additional Edge Case Tests
 * ========================================================================== */

static void test_stack_single_element(void)
{
    printf("\n--- Testing stack with single element ---\n");

    stack_t *stack = stack_create(int_free);

    int *val = malloc(sizeof(int));
    *val = 42;
    stack_push(stack, val);

    TEST_ASSERT(stack_get_length(stack) == 1, "Single element stack has length 1");
    TEST_ASSERT(*(int *)stack_top(stack) == 42, "Single element value is 42");

    stack_pop(stack);
    TEST_ASSERT(stack_get_length(stack) == 0, "Stack is empty after single pop");
    TEST_ASSERT(stack_is_empty(stack) == 1, "Stack reports empty");

    stack_destroy(&stack);
}

static void test_queue_single_element(void)
{
    printf("\n--- Testing queue with single element ---\n");

    queue_t *queue = queue_create(int_free);

    int *val = malloc(sizeof(int));
    *val = 42;
    queue_enqueue(queue, val);

    TEST_ASSERT(queue_get_length(queue) == 1, "Single element queue has length 1");
    TEST_ASSERT(*(int *)queue_front(queue) == 42, "Front is 42");
    TEST_ASSERT(*(int *)queue_back(queue) == 42, "Back is 42 (same element)");

    queue_dequeue(queue);
    TEST_ASSERT(queue_get_length(queue) == 0, "Queue is empty after single dequeue");
    TEST_ASSERT(queue_is_empty(queue) == 1, "Queue reports empty");

    queue_destroy(&queue);
}

static void test_stack_no_free_func(void)
{
    printf("\n--- Testing stack without free function ---\n");

    stack_t *stack = stack_create(NULL);

    int val1 = 10, val2 = 20, val3 = 30;
    stack_push(stack, &val1);
    stack_push(stack, &val2);
    stack_push(stack, &val3);

    TEST_ASSERT(*(int *)stack_top(stack) == 30, "Top is 30");

    /* Pop without free function - data is not freed */
    stack_pop(stack);
    TEST_ASSERT(*(int *)stack_top(stack) == 20, "Top is 20 after pop");

    /* Clear without free function */
    stack_clear(stack);
    TEST_ASSERT(stack_is_empty(stack) == 1, "Stack is empty after clear");

    stack_destroy(&stack);
}

static void test_queue_no_free_func(void)
{
    printf("\n--- Testing queue without free function ---\n");

    queue_t *queue = queue_create(NULL);

    int val1 = 10, val2 = 20, val3 = 30;
    queue_enqueue(queue, &val1);
    queue_enqueue(queue, &val2);
    queue_enqueue(queue, &val3);

    TEST_ASSERT(*(int *)queue_front(queue) == 10, "Front is 10");

    /* Dequeue without free function - data is not freed */
    queue_dequeue(queue);
    TEST_ASSERT(*(int *)queue_front(queue) == 20, "Front is 20 after dequeue");

    /* Clear without free function */
    queue_clear(queue);
    TEST_ASSERT(queue_is_empty(queue) == 1, "Queue is empty after clear");

    queue_destroy(&queue);
}

static void test_stack_multiple_clear(void)
{
    printf("\n--- Testing stack multiple clear ---\n");

    stack_t *stack = stack_create(int_free);

    for (int round = 0; round < 3; round++) {
        for (int i = 0; i < 10; i++) {
            int *val = malloc(sizeof(int));
            *val = round * 100 + i;
            stack_push(stack, val);
        }
        TEST_ASSERT(stack_get_length(stack) == 10, "Stack has 10 items");
        stack_clear(stack);
        TEST_ASSERT(stack_is_empty(stack) == 1, "Stack is empty after clear");
    }

    stack_destroy(&stack);
}

static void test_queue_multiple_clear(void)
{
    printf("\n--- Testing queue multiple clear ---\n");

    queue_t *queue = queue_create(int_free);

    for (int round = 0; round < 3; round++) {
        for (int i = 0; i < 10; i++) {
            int *val = malloc(sizeof(int));
            *val = round * 100 + i;
            queue_enqueue(queue, val);
        }
        TEST_ASSERT(queue_get_length(queue) == 10, "Queue has 10 items");
        queue_clear(queue);
        TEST_ASSERT(queue_is_empty(queue) == 1, "Queue is empty after clear");
    }

    queue_destroy(&queue);
}

/* ==========================================================================
 * Main Test Runner
 * ========================================================================== */

int main(void)
{
    printf("========================================\n");
    printf("Stack & Queue Library Test Suite\n");
    printf("========================================\n");

    /* Stack tests */
    printf("\n========== STACK TESTS ==========\n");
    test_stack_create_destroy();
    test_stack_clear();
    test_stack_push_pop();
    test_stack_lifo_order();
    test_stack_top();
    test_stack_is_empty();
    test_stack_string_data();
    test_stack_custom_struct();
    test_stack_reuse_after_clear();
    test_stack_single_element();
    test_stack_no_free_func();
    test_stack_multiple_clear();

    /* Queue tests */
    printf("\n========== QUEUE TESTS ==========\n");
    test_queue_create_destroy();
    test_queue_clear();
    test_queue_enqueue_dequeue();
    test_queue_fifo_order();
    test_queue_front_back();
    test_queue_is_empty();
    test_queue_string_data();
    test_queue_custom_struct();
    test_queue_reuse_after_clear();
    test_queue_single_element();
    test_queue_no_free_func();
    test_queue_multiple_clear();

    /* Print summary */
    printf("\n========================================\n");
    printf("Test Summary\n");
    printf("========================================\n");
    printf("Passed: %d\n", tests_passed);
    printf("Failed: %d\n", tests_failed);
    printf("Total:  %d\n", tests_passed + tests_failed);
    printf("========================================\n");

    return (tests_failed == 0) ? 0 : 1;
}
