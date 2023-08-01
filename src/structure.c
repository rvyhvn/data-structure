#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "../lib/structure.h"

void initStack(Stack *stack) { stack->top = -1; }

bool isStackEmpty(Stack *stack) { return stack->top == -1; }

bool isStackFull(Stack *stack) { return stack->top == MAX_SIZE - 1; }

void pushStack(Stack *stack, int value) {
  if (!isStackFull(stack)) {
    stack->items[++stack->top] = value;
  }
}

int popStack(Stack *stack) {
  if (!isStackEmpty(stack)) {
    int value = stack->items[stack->top--];
    return value;
  }
  return INT_MIN;
}

void saveStackState(Stack *stack, const char *filename) {
  // Open the file in "write" mode to clear it.
  FILE *file = fopen(filename, "w");
  if (file != NULL) {
    // Read the existing contents of the file and store them in memory.
    int existing[MAX_SIZE];
    int count = 0;
    int value;
    while (fscanf(file, "%d,", &value) == 1) {
      existing[count++] = value;
    }
    fclose(file);

    // Append the new stack state to the existing contents in memory.
    for (int i = 0; i <= stack->top; i++) {
      existing[count++] = stack->items[i];
    }

    // Rewrite the file with the combined contents.
    file = fopen(filename, "w");
    if (file != NULL) {
      for (int i = 0; i < count; i++) {
        fprintf(file, "%d", existing[i]);
        if (i != count - 1) {
          fprintf(file, ",");
        }
      }
      fprintf(file, "\n");
      fclose(file);
    }
  }
}

bool loadStackState(Stack *stack, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    int value;
    int i = 0;
    while (fscanf(file, "%d,", &value) == 1) {
      stack->items[i++] = value;
    }
    stack->top = i - 1;
    fclose(file);
    return true;
  }
  return false;
}

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
