#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list_node {
  int val;
  struct list_node *next;
};

#endif