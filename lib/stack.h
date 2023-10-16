#ifndef STACK_H
#define STACK_H

typedef struct NodeStack NodeStack;
NodeStack *createStack(int value);
void push(NodeStack **top, int value);
int pop(NodeStack **top);
int peekStack(NodeStack *top);

#endif // STACK_H


