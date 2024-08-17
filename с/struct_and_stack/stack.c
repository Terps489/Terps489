#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

struct node *push(struct node *elem, struct door *door) {
  struct node *new_node = malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("n/a\n");
    return NULL;
  }
  new_node->data = *door;
  new_node->next = elem;
  return new_node;
}

struct node *pop(struct node *head) {
  if (head == NULL) {
    printf("n/a\n");
    return NULL;
  }
  struct node *temp = head->next;
  free(head);
  return temp;
}
