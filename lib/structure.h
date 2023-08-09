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
void saveStackState(Stack *stack, const char *filename);
bool loadStackState(Stack *stack, const char *filename);

typedef struct {
  int items[MAX_SIZE];
  int count;
} Bag;

void initBag(Bag *bag);
bool isBagEmpty(Bag *bag);
bool isBagFull(Bag *bag);
void insertToBag(Bag *bag, int value);
int removeFromBag(Bag *bag, int value);
void saveBagState(Bag *bag, const char *filename);
bool loadBagState(Bag *bag, const char *filename);

typedef struct {
  int items[MAX_SIZE];
  int front;
  int rear;
} Queue;

void initQueue(Queue *queue);
bool isQueueEmpty(Queue *queue);
bool isQueueFull(Queue *queue);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
void saveQueueState(Queue *queue, const char *filename);
bool loadQueueState(Queue *queue, const char *filename);

// Structure for a node in the linked list
struct Node {
  int value;
  struct Node *next;
};

// Function declarations
struct Node *createNode(int value);
void appendNode(struct Node **head, int value);
void printLinkedList(struct Node *head);

#endif
