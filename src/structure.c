#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "../lib/structure.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "../lib/stack.h"

void initBag(Bag *bag) { bag->count = 0; }

bool isBagEmpty(Bag *bag) { return bag->count == 0; }

bool isBagFull(Bag *bag) { return bag->count == MAX_SIZE; }

void insertToBag(Bag *bag, int value) {
  if (!isBagFull(bag)) {
    bag->items[bag->count++] = value;
  }
}

int removeFromBag(Bag *bag, int value) {
  if (!isBagEmpty(bag)) {
    for (int i = 0; i < bag->count; i++) {
      if (bag->items[i] == value) {
        bag->items[i] = bag->items[bag->count - 1];
        bag->count--;
        return value;
      }
    }
  }
  return INT_MIN;
}

void saveBagState(Bag *bag, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file != NULL) {
    for (int i = 0; i < bag->count; i++) {
      fprintf(file, "%d", bag->items[i]);
      if (i != bag->count - 1) {
        fprintf(file, ", ");
      }
    }
    fprintf(file, "\n");
    fclose(file);
  }
}

bool loadBagState(Bag *bag, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    int value;
    int i = 0;
    while (fscanf(file, "%d,", &value) == 1) {
      bag->items[i++] = value;
      bag->count++;
    }
    fclose(file);
    return true;
  }
  return false;
}


