#include "list/list_range_reverse.h"
#include <stddef.h>
#include <string.h>

struct list_node* listRangeReverse(struct list_node* head, int left, int right) {
  struct list_node dummy;
  struct list_node* prev = &dummy;

  memset(&dummy, 0, sizeof(dummy));
  dummy.next = head;

  for (int i = 0; i < left - 1; i++) {
    prev = prev->next;
  }

  struct list_node* curr = prev->next;
  struct list_node* nextNode = NULL;

  for (int i = 0; i < right - left; i++) {
    nextNode = curr->next;
    curr->next = nextNode->next;
    nextNode->next = prev->next;
    prev->next = nextNode;
  }

  return dummy.next;
}
