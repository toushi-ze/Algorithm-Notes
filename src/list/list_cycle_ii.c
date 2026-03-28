#include "list/list_cycle_ii.h"

struct list_node *list_cycle_entry_find(struct list_node *head) {
  struct list_node *slow = head;
  struct list_node *fast = head;

  if (!head || !head->next)
    return NULL;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast) {
      slow = head;
      while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
      }
      return slow;
    }
  }
  return NULL;
}