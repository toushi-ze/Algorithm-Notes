#include "list/list_reverse.h"
#include <stddef.h>

struct list_node* listReverse(struct list_node* head) {
  struct list_node* prev = NULL;
  struct list_node* curr = head;

  while (NULL != curr) {
    struct list_node* nextTemp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = nextTemp;
  }

  return prev;
}
