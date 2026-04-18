/**
 * @file list_test.c
 * @brief Unit tests for generic linked list library
 *
 * Comprehensive test suite covering all APIs and edge cases.
 */

#include "list/list.h"
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

/* Test helper functions */
static int int_compare(const void *a, const void *b)
{
    int val1 = *(const int *)a;
    int val2 = *(const int *)b;
    return val1 - val2;
}

static void int_free(void *data)
{
    free(data);
}

static int string_compare(const void *a, const void *b)
{
    return strcmp((const char *)a, (const char *)b);
}

static void string_free(void *data)
{
    free(data);
}

/* Custom structure for testing */
typedef struct {
    int id;
    char name[32];
} person_t;

static int person_compare(const void *a, const void *b)
{
    const person_t *p1 = (const person_t *)a;
    const person_t *p2 = (const person_t *)b;
    return p1->id - p2->id;
}

static void person_free(void *data)
{
    free(data);
}

/* ==========================================================================
 * Test Cases
 * ========================================================================== */

static void test_list_create_destroy(void)
{
    printf("\n--- Testing list_create and list_destroy ---\n");

    /* Test create with NULL functions */
    list_t *list1 = list_create(NULL, NULL);
    TEST_ASSERT(list1 != NULL, "Create list with NULL functions");
    list_destroy(&list1);
    TEST_ASSERT(list1 == NULL, "Destroy sets pointer to NULL");

    /* Test create with custom functions */
    list_t *list2 = list_create(int_free, int_compare);
    TEST_ASSERT(list2 != NULL, "Create list with custom functions");
    list_destroy(&list2);

    /* Test destroy with NULL pointer */
    list_destroy(NULL);
    list_destroy(&list1);  /* Double destroy should be safe */
    TEST_ASSERT(1, "Destroy handles NULL gracefully");
}

static void test_list_clear(void)
{
    printf("\n--- Testing list_clear ---\n");

    list_t *list = list_create(int_free, int_compare);
    TEST_ASSERT(list != NULL, "Create list for clear test");

    /* Clear empty list */
    list_error_t err = list_clear(list);
    TEST_ASSERT(err == LIST_SUCCESS, "Clear empty list succeeds");
    TEST_ASSERT(list_get_length(list) == 0, "Empty list has length 0");

    /* Add some items */
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list_tail_insert(list, val);
    }
    TEST_ASSERT(list_get_length(list) == 5, "List has 5 items after insert");

    /* Clear non-empty list */
    err = list_clear(list);
    TEST_ASSERT(err == LIST_SUCCESS, "Clear non-empty list succeeds");
    TEST_ASSERT(list_get_length(list) == 0, "List length is 0 after clear");

    /* Can still use list after clear */
    int *val = malloc(sizeof(int));
    *val = 42;
    err = list_tail_insert(list, val);
    TEST_ASSERT(err == LIST_SUCCESS, "Can insert after clear");
    TEST_ASSERT(list_get_length(list) == 1, "List has 1 item after re-insert");

    list_destroy(&list);
}

static void test_list_head_insert(void)
{
    printf("\n--- Testing list_head_insert ---\n");

    list_t *list = list_create(int_free, int_compare);

    /* Insert into empty list */
    int *val1 = malloc(sizeof(int));
    *val1 = 1;
    list_error_t err = list_head_insert(list, val1);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert into empty list");
    TEST_ASSERT(list_get_length(list) == 1, "Length is 1");
    TEST_ASSERT(*(int *)list_index_get(list, 0) == 1, "Value is correct");

    /* Insert at head */
    int *val2 = malloc(sizeof(int));
    *val2 = 2;
    err = list_head_insert(list, val2);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert at head");
    TEST_ASSERT(list_get_length(list) == 2, "Length is 2");
    TEST_ASSERT(*(int *)list_index_get(list, 0) == 2, "New head value is correct");
    TEST_ASSERT(*(int *)list_index_get(list, 1) == 1, "Old head value is correct");

    /* Test NULL pointer */
    err = list_head_insert(NULL, val2);
    TEST_ASSERT(err == LIST_ERROR_NULL_POINTER, "NULL list returns error");

    list_destroy(&list);
}

static void test_list_tail_insert(void)
{
    printf("\n--- Testing list_tail_insert ---\n");

    list_t *list = list_create(int_free, int_compare);

    /* Insert into empty list */
    int *val1 = malloc(sizeof(int));
    *val1 = 1;
    list_error_t err = list_tail_insert(list, val1);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert into empty list");
    TEST_ASSERT(*(int *)list_index_get(list, 0) == 1, "Value is correct");

    /* Insert at tail */
    int *val2 = malloc(sizeof(int));
    *val2 = 2;
    err = list_tail_insert(list, val2);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert at tail");
    TEST_ASSERT(list_get_length(list) == 2, "Length is 2");
    TEST_ASSERT(*(int *)list_index_get(list, 1) == 2, "New tail value is correct");

    /* Insert more */
    int *val3 = malloc(sizeof(int));
    *val3 = 3;
    err = list_tail_insert(list, val3);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert third item");
    TEST_ASSERT(*(int *)list_index_get(list, 2) == 3, "Third value is correct");

    list_destroy(&list);
}

static void test_list_index_insert(void)
{
    printf("\n--- Testing list_index_insert ---\n");

    list_t *list = list_create(int_free, int_compare);

    /* Insert at index 0 (empty list) */
    int *val0 = malloc(sizeof(int));
    *val0 = 0;
    list_error_t err = list_index_insert(list, 0, val0);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert at index 0 (empty list)");
    TEST_ASSERT(*(int *)list_index_get(list, 0) == 0, "Value at index 0 is correct");

    /* Insert at index 1 (end) */
    int *val2 = malloc(sizeof(int));
    *val2 = 2;
    err = list_index_insert(list, 1, val2);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert at index 1");
    TEST_ASSERT(*(int *)list_index_get(list, 1) == 2, "Value at index 1 is correct");

    /* Insert at index 1 (middle) */
    int *val1 = malloc(sizeof(int));
    *val1 = 1;
    err = list_index_insert(list, 1, val1);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert at index 1 (middle)");
    TEST_ASSERT(*(int *)list_index_get(list, 0) == 0, "Value at index 0 is still 0");
    TEST_ASSERT(*(int *)list_index_get(list, 1) == 1, "Value at index 1 is now 1");
    TEST_ASSERT(*(int *)list_index_get(list, 2) == 2, "Value at index 2 is now 2");

    /* Test negative index */
    int *val_neg = malloc(sizeof(int));
    *val_neg = 99;
    err = list_index_insert(list, -1, val_neg);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert at negative index -1");
    TEST_ASSERT(*(int *)list_index_get(list, -1) == 99, "Value at -1 is correct");

    /* Test out of bounds */
    int *val_oob = malloc(sizeof(int));
    *val_oob = 100;
    err = list_index_insert(list, 100, val_oob);
    TEST_ASSERT(err == LIST_ERROR_INDEX_OUT_OF_BOUNDS, "Out of bounds index returns error");
    free(val_oob);

    list_destroy(&list);
}

static void test_list_index_insert_negative(void)
{
    printf("\n--- Testing list_index_insert with negative indices ---\n");

    list_t *list = list_create(int_free, int_compare);

    /* Setup: 1, 2, 3 */
    for (int i = 1; i <= 3; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list_tail_insert(list, val);
    }

    /* Test negative index mapping to position 0 (head) */
    int *val_neg3 = malloc(sizeof(int));
    *val_neg3 = 99;
    list_error_t err = list_index_insert(list, -3, val_neg3);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert at negative index -3 (maps to head)");
    TEST_ASSERT(list_get_length(list) == 4, "Length is 4 after insert");
    TEST_ASSERT(*(int *)list_index_get(list, 0) == 99, "Value 99 is at position 0");

    /* Test negative index mapping to middle position */
    int *val_neg2 = malloc(sizeof(int));
    *val_neg2 = 88;
    err = list_index_insert(list, -2, val_neg2);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert at negative index -2 (maps to middle)");
    TEST_ASSERT(list_get_length(list) == 5, "Length is 5 after insert");

    /* Test negative index -1 (tail insertion) */
    int *val_neg1 = malloc(sizeof(int));
    *val_neg1 = 77;
    err = list_index_insert(list, -1, val_neg1);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert at negative index -1 (tail)");
    TEST_ASSERT(*(int *)list_index_get(list, -1) == 77, "Value 77 is at tail");

    /* Test negative index out of bounds */
    int *val_oob = malloc(sizeof(int));
    *val_oob = 100;
    err = list_index_insert(list, -10, val_oob);
    TEST_ASSERT(err == LIST_ERROR_INDEX_OUT_OF_BOUNDS, "Negative out of bounds returns error");
    free(val_oob);

    /* Test negative index on empty list */
    list_t *empty_list = list_create(int_free, int_compare);
    int *val_empty = malloc(sizeof(int));
    *val_empty = 42;
    err = list_index_insert(empty_list, -1, val_empty);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert at -1 on empty list succeeds");
    TEST_ASSERT(list_get_length(empty_list) == 1, "Empty list has 1 item after insert");
    list_destroy(&empty_list);

    list_destroy(&list);
}

static void test_list_index_remove(void)
{
    printf("\n--- Testing list_index_remove ---\n");

    list_t *list = list_create(int_free, int_compare);

    /* Setup: 0, 1, 2, 3, 4 */
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list_tail_insert(list, val);
    }

    /* Remove from middle */
    list_error_t err = list_index_remove(list, 2);
    TEST_ASSERT(err == LIST_SUCCESS, "Remove from middle");
    TEST_ASSERT(list_get_length(list) == 4, "Length is 4");
    TEST_ASSERT(*(int *)list_index_get(list, 2) == 3, "Value at index 2 is now 3");

    /* Remove head */
    err = list_index_remove(list, 0);
    TEST_ASSERT(err == LIST_SUCCESS, "Remove head");
    TEST_ASSERT(list_get_length(list) == 3, "Length is 3");
    TEST_ASSERT(*(int *)list_index_get(list, 0) == 1, "New head is 1");

    /* Remove tail */
    err = list_index_remove(list, -1);
    TEST_ASSERT(err == LIST_SUCCESS, "Remove tail");
    TEST_ASSERT(list_get_length(list) == 2, "Length is 2");
    TEST_ASSERT(*(int *)list_index_get(list, -1) == 3, "New tail is 3");

    /* Remove remaining */
    err = list_index_remove(list, 0);
    err = list_index_remove(list, 0);
    TEST_ASSERT(list_get_length(list) == 0, "List is empty");

    /* Test remove from empty list */
    err = list_index_remove(list, 0);
    TEST_ASSERT(err == LIST_ERROR_EMPTY_LIST, "Remove from empty list returns error");

    /* Test invalid index on empty list (should return EMPTY_LIST error) */
    err = list_index_remove(list, 10);
    TEST_ASSERT(err == LIST_ERROR_EMPTY_LIST, "Invalid index on empty list returns EMPTY_LIST error");

    list_destroy(&list);
}

static void test_list_value_remove(void)
{
    printf("\n--- Testing list_value_remove ---\n");

    list_t *list = list_create(int_free, int_compare);

    /* Setup: 1, 2, 3, 2, 4 */
    int *val1 = malloc(sizeof(int));
    *val1 = 1;
    list_tail_insert(list, val1);

    int *val2a = malloc(sizeof(int));
    *val2a = 2;
    list_tail_insert(list, val2a);

    int *val3 = malloc(sizeof(int));
    *val3 = 3;
    list_tail_insert(list, val3);

    int *val2b = malloc(sizeof(int));
    *val2b = 2;
    list_tail_insert(list, val2b);

    int *val4 = malloc(sizeof(int));
    *val4 = 4;
    list_tail_insert(list, val4);

    /* Remove first occurrence of 2 */
    int search_val = 2;
    list_error_t err = list_value_remove(list, &search_val);
    TEST_ASSERT(err == LIST_SUCCESS, "Remove first occurrence of 2");
    TEST_ASSERT(list_get_length(list) == 4, "Length is 4");
    TEST_ASSERT(*(int *)list_index_get(list, 1) == 3, "Value at index 1 is now 3");

    /* Remove non-existent value */
    int not_found = 99;
    err = list_value_remove(list, &not_found);
    TEST_ASSERT(err == LIST_ERROR_NOT_FOUND, "Remove non-existent value returns error");

    list_destroy(&list);
}

static void test_list_value_remove_all(void)
{
    printf("\n--- Testing list_value_remove_all ---\n");

    list_t *list = list_create(int_free, int_compare);

    /* Setup: 1, 2, 3, 2, 4, 2 */
    for (int i = 0; i < 6; i++) {
        int *val = malloc(sizeof(int));
        *val = (i == 1 || i == 3 || i == 5) ? 2 : (i < 3 ? i + 1 : i);
        list_tail_insert(list, val);
    }

    /* Remove all occurrences of 2 */
    int search_val = 2;
    list_error_t err = list_value_remove_all(list, &search_val);
    TEST_ASSERT(err == LIST_SUCCESS, "Remove all occurrences of 2");
    TEST_ASSERT(list_get_length(list) == 3, "Length is 3");

    /* Verify remaining values */
    TEST_ASSERT(*(int *)list_index_get(list, 0) == 1, "First value is 1");
    TEST_ASSERT(*(int *)list_index_get(list, 1) == 3, "Second value is 3");
    TEST_ASSERT(*(int *)list_index_get(list, 2) == 4, "Third value is 4");

    list_destroy(&list);
}

static void test_list_index_get(void)
{
    printf("\n--- Testing list_index_get ---\n");

    list_t *list = list_create(int_free, int_compare);

    /* Setup: 10, 20, 30 */
    for (int i = 1; i <= 3; i++) {
        int *val = malloc(sizeof(int));
        *val = i * 10;
        list_tail_insert(list, val);
    }

    /* Test positive indices */
    TEST_ASSERT(*(int *)list_index_get(list, 0) == 10, "Index 0 is 10");
    TEST_ASSERT(*(int *)list_index_get(list, 1) == 20, "Index 1 is 20");
    TEST_ASSERT(*(int *)list_index_get(list, 2) == 30, "Index 2 is 30");

    /* Test negative indices */
    TEST_ASSERT(*(int *)list_index_get(list, -1) == 30, "Index -1 is 30");
    TEST_ASSERT(*(int *)list_index_get(list, -2) == 20, "Index -2 is 20");
    TEST_ASSERT(*(int *)list_index_get(list, -3) == 10, "Index -3 is 10");

    /* Test out of bounds */
    TEST_ASSERT(list_index_get(list, 10) == NULL, "Out of bounds returns NULL");
    TEST_ASSERT(list_index_get(list, -10) == NULL, "Negative out of bounds returns NULL");
    TEST_ASSERT(list_index_get(list, 3) == NULL, "Index equal to length returns NULL");

    /* Test NULL list */
    TEST_ASSERT(list_index_get(NULL, 0) == NULL, "NULL list returns NULL");

    list_destroy(&list);
}

static void test_list_value_get_index(void)
{
    printf("\n--- Testing list_value_get_index ---\n");

    list_t *list = list_create(int_free, int_compare);

    /* Setup: 10, 20, 30, 20 */
    for (int i = 1; i <= 4; i++) {
        int *val = malloc(sizeof(int));
        *val = (i == 4) ? 20 : i * 10;
        list_tail_insert(list, val);
    }

    /* Test find existing values */
    int search_val = 20;
    TEST_ASSERT(list_value_get_index(list, &search_val) == 1, "First 20 at index 1");

    search_val = 30;
    TEST_ASSERT(list_value_get_index(list, &search_val) == 2, "30 at index 2");

    search_val = 10;
    TEST_ASSERT(list_value_get_index(list, &search_val) == 0, "10 at index 0");

    /* Test non-existent value */
    search_val = 99;
    TEST_ASSERT(list_value_get_index(list, &search_val) == -1, "Non-existent returns -1");

    /* Test NULL list */
    TEST_ASSERT(list_value_get_index(NULL, &search_val) == -1, "NULL list returns -1");

    list_destroy(&list);
}

static void test_list_get_length(void)
{
    printf("\n--- Testing list_get_length ---\n");

    list_t *list = list_create(int_free, int_compare);

    TEST_ASSERT(list_get_length(list) == 0, "Empty list has length 0");
    TEST_ASSERT(list_get_length(NULL) == 0, "NULL list returns 0");

    for (int i = 0; i < 10; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list_tail_insert(list, val);
    }
    TEST_ASSERT(list_get_length(list) == 10, "Length is 10 after 10 inserts");

    list_clear(list);
    TEST_ASSERT(list_get_length(list) == 0, "Length is 0 after clear");

    list_destroy(&list);
}

static int foreach_counter = 0;

static int count_callback(void *data, void *user_data)
{
    (void)data;
    (void)user_data;
    foreach_counter++;
    return 0;
}

static int stop_callback(void *data, void *user_data)
{
    (void)data;
    int *count = (int *)user_data;
    (*count)++;
    if (*count >= 3) {
        return 1;  /* Stop after 3 items */
    }
    return 0;
}

static void test_list_foreach(void)
{
    printf("\n--- Testing list_foreach ---\n");

    list_t *list = list_create(int_free, int_compare);

    /* Setup: 0, 1, 2, 3, 4 */
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list_tail_insert(list, val);
    }

    /* Test full traversal */
    foreach_counter = 0;
    list_error_t err = list_foreach(list, count_callback, NULL);
    TEST_ASSERT(err == LIST_SUCCESS, "Foreach succeeds");
    TEST_ASSERT(foreach_counter == 5, "Foreach visited all 5 items");

    /* Test early termination */
    int count = 0;
    err = list_foreach(list, stop_callback, &count);
    TEST_ASSERT(err == LIST_SUCCESS, "Foreach with stop succeeds");
    TEST_ASSERT(count == 3, "Foreach stopped after 3 items");

    /* Test NULL callback */
    err = list_foreach(list, NULL, NULL);
    TEST_ASSERT(err == LIST_ERROR_NULL_POINTER, "NULL callback returns error");

    list_destroy(&list);
}

static void test_list_iterator_macro(void)
{
    printf("\n--- Testing LIST_FOR_EACH macro ---\n");

    list_t *list = list_create(int_free, int_compare);

    /* Setup: 1, 2, 3 */
    for (int i = 1; i <= 3; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list_tail_insert(list, val);
    }

    /* Test iterator macro */
    int sum = 0;
    int count = 0;
    LIST_FOR_EACH(list, data) {
        sum += *(int *)data;
        count++;
    }
    TEST_ASSERT(count == 3, "Iterator visited 3 items");
    TEST_ASSERT(sum == 6, "Sum is 6 (1+2+3)");

    list_destroy(&list);
}

static void test_string_data(void)
{
    printf("\n--- Testing with string data ---\n");

    list_t *list = list_create(string_free, string_compare);

    /* Insert strings */
    char *str1 = strdup("hello");
    char *str2 = strdup("world");
    char *str3 = strdup("test");

    list_tail_insert(list, str1);
    list_tail_insert(list, str2);
    list_tail_insert(list, str3);

    TEST_ASSERT(list_get_length(list) == 3, "String list has 3 items");

    /* Find string */
    char *search = "world";
    int index = list_value_get_index(list, search);
    TEST_ASSERT(index == 1, "Found 'world' at index 1");

    /* Remove string */
    list_error_t err = list_value_remove(list, search);
    TEST_ASSERT(err == LIST_SUCCESS, "Removed 'world'");
    TEST_ASSERT(list_get_length(list) == 2, "Length is 2 after removal");

    list_destroy(&list);
}

static void test_custom_struct_data(void)
{
    printf("\n--- Testing with custom struct data ---\n");

    list_t *list = list_create(person_free, person_compare);

    /* Insert persons */
    person_t *p1 = malloc(sizeof(person_t));
    p1->id = 1;
    strcpy(p1->name, "Alice");
    list_tail_insert(list, p1);

    person_t *p2 = malloc(sizeof(person_t));
    p2->id = 2;
    strcpy(p2->name, "Bob");
    list_tail_insert(list, p2);

    person_t *p3 = malloc(sizeof(person_t));
    p3->id = 3;
    strcpy(p3->name, "Charlie");
    list_tail_insert(list, p3);

    TEST_ASSERT(list_get_length(list) == 3, "Person list has 3 items");

    /* Find person by ID */
    person_t search_person = { .id = 2 };
    int index = list_value_get_index(list, &search_person);
    TEST_ASSERT(index == 1, "Found person with ID 2 at index 1");

    /* Get person data */
    person_t *found = list_index_get(list, index);
    TEST_ASSERT(found != NULL, "Found person is not NULL");
    TEST_ASSERT(found->id == 2, "Found person has correct ID");
    TEST_ASSERT(strcmp(found->name, "Bob") == 0, "Found person has correct name");

    list_destroy(&list);
}

static void test_edge_cases(void)
{
    printf("\n--- Testing edge cases ---\n");

    /* Single node operations */
    list_t *list = list_create(int_free, int_compare);
    int *val = malloc(sizeof(int));
    *val = 42;
    list_tail_insert(list, val);

    TEST_ASSERT(list_get_length(list) == 1, "Single node list has length 1");
    TEST_ASSERT(*(int *)list_index_get(list, 0) == 42, "Single node value is correct");

    /* Remove single node */
    list_error_t err = list_index_remove(list, 0);
    TEST_ASSERT(err == LIST_SUCCESS, "Remove single node succeeds");
    TEST_ASSERT(list_get_length(list) == 0, "List is empty after removing single node");

    /* Operations on empty list */
    err = list_index_remove(list, 0);
    TEST_ASSERT(err == LIST_ERROR_EMPTY_LIST, "Remove from empty list returns error");

    TEST_ASSERT(list_index_get(list, 0) == NULL, "Get from empty list returns NULL");

    list_destroy(&list);
}

static void test_list_reuse_after_clear(void)
{
    printf("\n--- Testing list reuse after clear ---\n");

    list_t *list = list_create(int_free, int_compare);

    /* First use */
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list_tail_insert(list, val);
    }
    TEST_ASSERT(list_get_length(list) == 5, "List has 5 items after first use");

    list_clear(list);
    TEST_ASSERT(list_get_length(list) == 0, "List is empty after clear");

    /* Second use */
    for (int i = 10; i < 15; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list_head_insert(list, val);
    }
    TEST_ASSERT(list_get_length(list) == 5, "List has 5 items after second use");
    TEST_ASSERT(*(int *)list_index_get(list, 0) == 14, "Head is 14 (last inserted)");

    /* Third use after another clear */
    list_clear(list);
    int *val = malloc(sizeof(int));
    *val = 100;
    list_error_t err = list_index_insert(list, 0, val);
    TEST_ASSERT(err == LIST_SUCCESS, "Insert after second clear succeeds");
    TEST_ASSERT(list_get_length(list) == 1, "List has 1 item");

    list_destroy(&list);
}

static void test_value_remove_no_compare(void)
{
    printf("\n--- Testing value_remove without compare function ---\n");

    list_t *list = list_create(int_free, NULL);

    int *val = malloc(sizeof(int));
    *val = 1;
    list_tail_insert(list, val);

    int search = 1;
    list_error_t err = list_value_remove(list, &search);
    TEST_ASSERT(err == LIST_ERROR_INVALID_PARAM, "Value remove without compare func returns error");

    err = list_value_remove_all(list, &search);
    TEST_ASSERT(err == LIST_ERROR_INVALID_PARAM, "Value remove all without compare func returns error");

    list_destroy(&list);
}

/* ==========================================================================
 * Main Test Runner
 * ========================================================================== */

int main(void)
{
    printf("========================================\n");
    printf("Generic Linked List Library Test Suite\n");
    printf("========================================\n");

    /* Run all tests */
    test_list_create_destroy();
    test_list_clear();
    test_list_head_insert();
    test_list_tail_insert();
    test_list_index_insert();
    test_list_index_insert_negative();
    test_list_index_remove();
    test_list_value_remove();
    test_list_value_remove_all();
    test_list_index_get();
    test_list_value_get_index();
    test_list_get_length();
    test_list_foreach();
    test_list_iterator_macro();
    test_string_data();
    test_custom_struct_data();
    test_edge_cases();
    test_list_reuse_after_clear();
    test_value_remove_no_compare();

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
