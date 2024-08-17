#ifndef STACK_H
#define STACK_H

#include "door_struct.h"

struct node *push(struct node *elem, struct door *door);
struct node *pop(struct node *head);

#endif