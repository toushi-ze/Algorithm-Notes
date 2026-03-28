#include "list/list_cycle.h"

int list_cycle_check(struct list_node *head) {
  struct list_node *slow = head;
  struct list_node *fast = head;

  if (!head || !head->next)
    return 0;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast)
      return 1;
  }
  return 0;
}