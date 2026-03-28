#include "list/list_merge.h"
#include <stddef.h>
#include <string.h>

struct list_node* listMerge(struct list_node* list1, struct list_node* list2) {
  struct list_node dummy;
  struct list_node* curr = &dummy;

  memset(&dummy, 0, sizeof(dummy));

  while (NULL != list1 && NULL != list2) {
    if (list1->val < list2->val) {
      curr->next = list1;
      list1 = list1->next;
    } else {
      curr->next = list2;
      list2 = list2->next;
    }
    curr = curr->next;
  }

  if (NULL != list1) {
    curr->next = list1;
  } else {
    curr->next = list2;
  }

  return dummy.next;
}
