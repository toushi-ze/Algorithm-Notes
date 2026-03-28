#include "list/list_nth_remove.h"
#include <stdlib.h>
#include <string.h>

struct list_node* listNthRemove(struct list_node* head, int n) {
  struct list_node* dummy = (struct list_node*)malloc(sizeof(struct list_node));
  memset(dummy, 0, sizeof(*dummy));
  dummy->next = head;

  struct list_node* fast = dummy;
  struct list_node* slow = dummy;

  for (int i = 0; i <= n; i++) {
    fast = fast->next;
  }

  while (NULL != fast) {
    fast = fast->next;
    slow = slow->next;
  }

  struct list_node* target = slow->next;
  slow->next = slow->next->next;

  free(target);

  struct list_node* newHead = dummy->next;
  free(dummy);

  return newHead;
}
