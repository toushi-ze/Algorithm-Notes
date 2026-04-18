/**
 * @file algorithms_test.c
 * @brief Demonstration of linked list algorithm implementations
 */

#include "list/list_node.h"
#include "list/list_reverse.h"
#include "list/list_merge.h"
#include "list/list_nth_remove.h"
#include "list/list_range_reverse.h"
#include "list/list_k_group_reverse.h"
#include "list/list_cycle.h"
#include "list/list_cycle_ii.h"
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    /* === Test listReverse === */
    printf("=== Test listReverse ===\n");
    int arr1[] = {1, 2, 3, 4, 5};
    list_node_t *list1 = list_from_array(arr1, 5);
    printf("Input:  ");
    list_print(list1);
    list1 = list_reverse(list1);
    printf("\nOutput: ");
    list_print(list1);
    printf("\n\n");
    list_free(list1);

    /* === Test listMerge === */
    printf("=== Test listMerge ===\n");
    int arr2a[] = {1, 2, 4};
    int arr2b[] = {1, 3, 4};
    list_node_t *list2a = list_from_array(arr2a, 3);
    list_node_t *list2b = list_from_array(arr2b, 3);
    printf("List1:  ");
    list_print(list2a);
    printf("\nList2:  ");
    list_print(list2b);
    list_node_t *merged = list_merge(list2a, list2b);
    printf("\nOutput: ");
    list_print(merged);
    printf("\n\n");
    list_free(merged);

    /* === Test listNthRemove === */
    printf("=== Test listNthRemove ===\n");
    int arr3[] = {1, 2, 3, 4, 5};
    list_node_t *list3 = list_from_array(arr3, 5);
    printf("Input:  ");
    list_print(list3);
    list3 = list_nth_remove(list3, 2); /* Remove 2nd from end (value 4) */
    printf("\nOutput: ");
    list_print(list3);
    printf("\n\n");
    list_free(list3);

    /* === Test listRangeReverse === */
    printf("=== Test listRangeReverse ===\n");
    int arr4[] = {1, 2, 3, 4, 5};
    list_node_t *list4 = list_from_array(arr4, 5);
    printf("Input:  ");
    list_print(list4);
    list4 = list_range_reverse(list4, 2, 4); /* Reverse [2,4] */
    printf("\nOutput: ");
    list_print(list4);
    printf("\n\n");
    list_free(list4);

    /* === Test listKGroupReverse === */
    printf("=== Test listKGroupReverse ===\n");
    int arr5[] = {1, 2, 3, 4, 5};
    list_node_t *list5 = list_from_array(arr5, 5);
    printf("Input:  ");
    list_print(list5);
    list5 = list_k_group_reverse(list5, 2); /* Reverse in groups of 2 */
    printf("\nOutput: ");
    list_print(list5);
    printf("\n\n");
    list_free(list5);

    /* === Test list_cycle_check & list_cycle_entry_find === */
    printf("=== Test list_cycle_check & list_cycle_entry_find ===\n");

    /* Test 1: No cycle */
    int arr6[] = {1, 2, 3, 4, 5};
    list_node_t *list6 = list_from_array(arr6, 5);
    bool has_cycle = list_cycle_check(list6);
    printf("Has Cycle: %s\n", has_cycle ? "True" : "False");
    list_free(list6);

    /* Test 2: With cycle */
    list_node_t *node1 = list_node_create(1);
    list_node_t *node2 = list_node_create(2);
    list_node_t *node3 = list_node_create(3);
    list_node_t *node4 = list_node_create(4);
    list_node_t *node5 = list_node_create(5);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node2; /* Create cycle: 5 -> 2 */

    has_cycle = list_cycle_check(node1);
    printf("Has Cycle: %s\n", has_cycle ? "True" : "False");

    list_node_t *entry = list_cycle_entry_find(node1);
    if (entry != NULL) {
        printf("Cycle Entry Val: %d (expect 2)\n", entry->val);
    }

    /* Break cycle before freeing */
    node5->next = NULL;
    list_free(node1);

    printf("\nAll tests completed.\n");

    return 0;
}
