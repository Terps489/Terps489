#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct node *init(struct door *door) {
  struct node *new_node = malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("n/a");
  }
  new_node->data = *door;
  new_node->next = NULL;
  return new_node;
}

struct node *add_door(struct node *elem, struct door *door) {
  struct node *new_node = malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("n/a");
  }
  new_node->data = *door;
  new_node->next = elem->next;
  elem->next = new_node;
  return new_node;
}

struct node *find_door(int door_id, struct node *root) {
  struct node *current = root;
  while (current != NULL) {
    if (current->data.id == door_id) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

struct node *remove_door(struct node *elem, struct node *root) {
  if (root == NULL || elem == NULL) {
    return root;
  }

  if (root == elem) {
    struct node *temp = root->next;
    free(root);
    return temp;
  }

  struct node *current = root;
  while (current->next != NULL && current->next != elem) {
    current = current->next;
  }

  if (current->next == elem) {
    struct node *temp = current->next;
    current->next = elem->next;
    free(temp);
  }
  return root;
}

void destroy(struct node *root) {
  while (root != NULL) {
    struct node *temp = root;
    root = root->next;
    free(temp);
  }
}
