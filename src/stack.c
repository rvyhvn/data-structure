#include "../lib/stack.h"
#include <stdio.h>
#include <stdlib.h>

struct NodeStack {
  int data;
  struct NodeStack *next;
};

NodeStack *createStack(int value) {
  NodeStack *newStack = (NodeStack *)malloc(sizeof(NodeStack));
  if (newStack != NULL) {
    newStack->data = value;
    newStack->next = NULL;
  }
  return newStack;
}

void push(NodeStack **top, int value) {
  NodeStack *newNode = createStack(value);
  if (newNode != NULL) {
    newNode->next = *top;
    *top = newNode;
  }
}

int pop(NodeStack **top) {
  if (*top == NULL) {
    return -1; // Stack is empty
  }
  int data = (*top)->data;
  NodeStack *temp = *top;
  *top = (*top)->next;
  free(temp);
  return data;
}

int peekStack(NodeStack *top) {
  if (top == NULL) {
    return -1; // Stack is empty
  }
  return top->data;
}

void stackMenu() {
  NodeStack *top = NULL;
  int stackChoice;

  do {
    printf("Stack Menu:\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Peek\n");
    printf("0. Back\n");
    printf("Option: ");
    scanf("%d", &stackChoice);

    switch (stackChoice) {
    case 1:
      printf("Enter a value to push: ");
      int value;
      scanf("%d", &value);
      push(&top, value);
      break;
    case 2: {
      int popped = pop(&top);
      if (popped != -1) {
        printf("Popped value: %d\n", popped);
      } else {
        printf("Stack is empty.\n");
      }
      break;
    }
    case 3: {
      int peeked = peekStack(top);
      if (peeked != -1) {
        printf("Top value: %d\n", peeked);
      } else {
        printf("Stack is empty.\n");
      }
      break;
    }
    case 0:
      break;
    default:
      printf("Menu invalid!\n");
    }

  } while (stackChoice != 0);
}
