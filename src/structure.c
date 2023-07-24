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
  return -1;
};
