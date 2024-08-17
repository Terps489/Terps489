#ifndef DOOR_STRUCT_H
#define DOOR_STRUCT_H

struct door {
  int id;
  int status;
};

struct node {
  struct door data;
  struct node *next;
};

#endif