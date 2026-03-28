#include "list/list_k_group_reverse.h"
#include <stdlib.h>
#include <string.h>

static struct list_node* getKthNode(struct list_node* curr, int k) {
  while (NULL != curr && k > 0) {
    curr = curr->next;
    k--;
  }
  return curr;
}

struct list_node* listKGroupReverse(struct list_node* head, int k) {
  if (NULL == head || 1 == k) {
    return head;
  }

  struct list_node* dummy = (struct list_node*)malloc(sizeof(struct list_node));
  memset(dummy, 0, sizeof(*dummy));
  dummy->next = head;

  struct list_node* groupPrev = dummy;

  while (1) {
    struct list_node* kthNode = getKthNode(groupPrev, k);
    if (NULL == kthNode) {
      break;
    }

    struct list_node* groupNext = kthNode->next;

    struct list_node* prev = groupNext;
    struct list_node* curr = groupPrev->next;
    struct list_node* tmp = NULL;

    for (int i = 0; i < k; i++) {
      tmp = curr->next;
      curr->next = prev;
      prev = curr;
      curr = tmp;
    }

    struct list_node* nextGroupPrev = groupPrev->next;
    groupPrev->next = kthNode;
    groupPrev = nextGroupPrev;
  }

  struct list_node* newHead = dummy->next;
  free(dummy);

  return newHead;
}
