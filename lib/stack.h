#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
  int items[MAX_SIZE];
  int top;
  Stack;
}

void initStack(Stack *stack);
bool isStackEmpty(Stack *stack);
bool isStackFull(Stack *stack);
void pushStack(Stack *stack, int value);
int popStack(Stack *stack);
void saveStackState(Stack *stack, const char *filename);
bool loadStackState(Stack *stack, const char *filename);
#endif // !
#define STACK_H



