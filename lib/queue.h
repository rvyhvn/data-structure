#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
  int items[MAX_SIZE];
  int count;
  Queue;
}

void initQueue(Queue *queue);
bool isQueueEmpty(Queue *queue);
bool isQueueFull(Queue *queue);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
void saveQueueState(Queue *queue, const char *filename);
void loadQueueState(Queue *queue, const char *filename);

#endif // !DEBUG
