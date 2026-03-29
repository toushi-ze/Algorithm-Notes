#include "list/list_k_group_reverse.h"
#include "list/list_merge.h"
#include "list/list_nth_remove.h"
#include "list/list_range_reverse.h"
#include "list/list_reverse.h"
#include "list/list_cycle.h"
#include "list/list_cycle_ii.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct list_node* list_nodeCreate(int val);
static void list_nodePrint(struct list_node* head);
static void list_nodeFree(struct list_node* head);

/* todo: 注意驼峰或下划线用一种方式，不要又驼峰，又下划线*/
static struct list_node* list_nodeCreate(int val) {
  struct list_node* node = (struct list_node*)malloc(sizeof(struct list_node));
  memset(node, 0, sizeof(*node));
  node->val = val;
  node->next = NULL;
  return node;
}

static void list_nodePrint(struct list_node* head) {
  struct list_node* curr = head;
  printf("[");
  while (curr != NULL) {
    printf("%d", curr->val);
    if (curr->next != NULL)
      printf(", ");
    curr = curr->next;
  }
  printf("]\n");
}

static void list_nodeFree(struct list_node* head) {
  struct list_node* curr = head;
  while (curr != NULL) {
    struct list_node* tmp = curr;
    curr = curr->next;
    free(tmp);
  }
}

static void testCaseListReverse(void) {
  printf("=== Test listReverse ===\n");
  struct list_node* head = list_nodeCreate(1);
  head->next = list_nodeCreate(2);
  head->next->next = list_nodeCreate(3);
  head->next->next->next = list_nodeCreate(4);
  head->next->next->next->next = list_nodeCreate(5);

  printf("Input:  ");
  list_nodePrint(head);
  head = listReverse(head);
  printf("Output: ");
  list_nodePrint(head);
  printf("\n");
  list_nodeFree(head);
}

static void testCaseListMerge(void) {
  printf("=== Test listMerge ===\n");
  struct list_node* list1 = list_nodeCreate(1);
  list1->next = list_nodeCreate(2);
  list1->next->next = list_nodeCreate(4);

  struct list_node* list2 = list_nodeCreate(1);
  list2->next = list_nodeCreate(3);
  list2->next->next = list_nodeCreate(4);

  printf("List1:  ");
  list_nodePrint(list1);
  printf("List2:  ");
  list_nodePrint(list2);
  struct list_node* merged = listMerge(list1, list2);
  printf("Output: ");
  list_nodePrint(merged);
  printf("\n");
  list_nodeFree(merged);
}

static void testCaseListNthRemove(void) {
  printf("=== Test listNthRemove ===\n");
  struct list_node* head = list_nodeCreate(1);
  head->next = list_nodeCreate(2);
  head->next->next = list_nodeCreate(3);
  head->next->next->next = list_nodeCreate(4);
  head->next->next->next->next = list_nodeCreate(5);

  printf("Input:  ");
  list_nodePrint(head);
  head = listNthRemove(head, 2);
  printf("Output: ");
  list_nodePrint(head);
  printf("\n");
  list_nodeFree(head);
}

static void testCaseListRangeReverse(void) {
  printf("=== Test listRangeReverse ===\n");
  struct list_node* head = list_nodeCreate(1);
  head->next = list_nodeCreate(2);
  head->next->next = list_nodeCreate(3);
  head->next->next->next = list_nodeCreate(4);
  head->next->next->next->next = list_nodeCreate(5);

  printf("Input:  ");
  list_nodePrint(head);
  head = listRangeReverse(head, 2, 4);
  printf("Output: ");
  list_nodePrint(head);
  printf("\n");
  list_nodeFree(head);
}

static void testCaseListKGroupReverse(void) {
  printf("=== Test listKGroupReverse ===\n");
  struct list_node* head = list_nodeCreate(1);
  head->next = list_nodeCreate(2);
  head->next->next = list_nodeCreate(3);
  head->next->next->next = list_nodeCreate(4);
  head->next->next->next->next = list_nodeCreate(5);

  printf("Input:  ");
  list_nodePrint(head);
  head = listKGroupReverse(head, 2);
  printf("Output: ");
  list_nodePrint(head);
  printf("\n");
  list_nodeFree(head);
}

static void testCaseListCycle(void) {
  printf("=== Test list_cycle_check & list_cycle_entry_find ===\n");

  struct list_node* head = list_nodeCreate(3);
  struct list_node* node2 = list_nodeCreate(2);
  struct list_node* node0 = list_nodeCreate(0);
  struct list_node* node_tail = list_nodeCreate(-4);

  head->next = node2;
  node2->next = node0;
  node0->next = node_tail;

  printf("Has Cycle: %s\n", list_cycle_check(head) ? "True" : "False");
  node_tail->next = node2;

  int has_cycle = list_cycle_check(head);
  printf("Has Cycle: %s\n", has_cycle ? "True" : "False");

  if (has_cycle) {
    struct list_node* entry = list_cycle_entry_find(head);
    if (entry != NULL)
      printf("Cycle Entry Val: %d (expect 2)\n", entry->val);
  }

  node_tail->next = NULL;
  list_nodeFree(head);
  printf("\n");
}

int main(void) {
  testCaseListReverse();
  testCaseListMerge();
  testCaseListNthRemove();
  testCaseListRangeReverse();
  testCaseListKGroupReverse();
  testCaseListCycle();

  printf("All tests completed.\n");
  return 0;
}