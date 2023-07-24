#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
  int items[MAX_SIZE];
  int top;
} Stack;

// Functions for stack
void initStack(Stack *stack);
bool isStackEmpty(Stack *stack);
bool isStackFull(Stack *stack);
void pushStack(Stack *stack, int value);
int popStack(Stack *stack);

#endif
