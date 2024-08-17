#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(struct door *doors);
void print_doors(struct door *doors);
void door_sort(struct door *doors);

int main() {
  struct door doors[DOORS_COUNT];

  initialize_doors(doors);
  door_sort(doors);
  print_doors(doors);

  return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door *doors) {
  srand(time(0));

  int seed = rand() % MAX_ID_SEED;
  for (int i = 0; i < DOORS_COUNT; i++) {
    doors[i].id = (i + seed) % DOORS_COUNT;
    doors[i].status = rand() % 2;
  }
}
void door_sort(struct door *doors) {
  for (int i = 0; i < DOORS_COUNT; i++)
    doors[i].status = 0;
  for (int s = DOORS_COUNT / 2; s > 0; s /= 2) {
    for (int i = s; i < DOORS_COUNT; ++i) {
      for (int j = i - s; j >= 0 && doors[j].id > doors[j + s].id; j -= s) {
        struct door temp = doors[j];
        doors[j] = doors[j + s];
        doors[j + s] = temp;
      }
    }
  }
}
void print_doors(struct door *doors) {
  for (int i = 0; i < DOORS_COUNT; i++) {
    printf("%d, %d", doors[i].id, doors[i].status);
    if (i != DOORS_COUNT - 1)
      printf("\n");
  }
}
#ifndef DOOR_STRUCT_H
#define DOOR_STRUCT_H

struct door {
  int id;
  int status;
};

#endif