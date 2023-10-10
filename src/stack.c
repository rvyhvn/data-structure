#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "../lib/stack.h"

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
