#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"
#include "list.h"

void print_doors(struct node *head);

int main() {
  struct door doors[4];
  for (int i = 0; i < 4; i++) {
    doors[i].id = i;
    doors[i].status = (i == 3) ? 1 : 0;
  }

  struct node *head = init(&doors[0]);
  struct node *second = add_door(head, &doors[1]);
  struct node *new = add_door(second, &doors[2]);
  add_door(new, &doors[3]);
  head = remove_door(new, head);
  if (head->data.id == doors[0].id) {
    printf("SUCCESS");
  } else {
    printf("FAIL");
  }
  printf("\n");
  struct node *found_door = find_door(1, head);
  if (found_door == second) {
    printf("SUCCESS");
  } else {
    printf("FAIL");
  }
  printf("\n");

  struct node *found_door2 = find_door(4, head);
  if (found_door2 == NULL) {
    printf("SUCCESS");
  } else {
    printf("FAIL");
  }
  destroy(head);

  return 0;
}

void print_doors(struct node *head) {
  struct node *current = head;
  while (current != NULL) {
    printf("%d, %d\n", current->data.id, current->data.status);
    current = current->next;
  }
}
