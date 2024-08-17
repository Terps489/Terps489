#include "list.h"
#include "stack.h"
#include <stdio.h>

int main() {
  struct door door1 = {1, 0};
  struct door door2 = {2, 1};

  struct node *stack = init(&door1);
  stack = push(stack, &door2);

  if (stack->data.status == door2.status) {
    printf("SUCCSESS");
  } else {
    printf("FAIL");
  }
  printf("\n");
  stack = push(stack, &door2);
  if (stack->data.status == door2.status) {
    printf("SUCCSESS");
  } else {
    printf("FAIL");
  }
  printf("\n");
  stack = pop(stack);
  stack = pop(stack);
  if (stack->data.status == door1.status) {
    printf("SUCCSESS");
  } else {
    printf("FAIL");
  }
  destroy(stack);

  return 0;
}
