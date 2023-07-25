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
    return stack->items[stack->top--];
  }
  return INT_MIN;
}

void saveStackState(Stack *stack, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file != NULL) {
    for (int i = 0; i <= stack->top; i++) {
      fprintf(file, "%d", stack->items[i]);
      if (i != stack->top) {
        fprintf(file, ",");
      }
    }
    fprintf(file, "\n");
    fclose(file);
  }
}

bool loadStackState(Stack *stack, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    int value;
    int i = 0;
    while (fscanf(file, "%d", &value) == 1) {
      stack->items[i++] = value;
    }
    stack->top = i - 1;
    fclose(file);
    return true;
  }
  return false;
}
