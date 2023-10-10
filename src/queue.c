#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "../lib/queue.h"

void initQueue(Queue *queue) {
  queue->front = 0;
  queue->rear = -1;
}

bool isQueueEmpty(Queue *queue) { return queue->rear < queue->front; }

bool isQueueFull(Queue *queue) { return queue->rear == MAX_SIZE - 1; }

void enqueue(Queue *queue, int value) {
  if (!isQueueFull(queue)) {
    queue->items[++queue->rear] = value;
  }
}

int dequeue(Queue *queue) {
  if (!isQueueEmpty(queue)) {
    int value = queue->items[queue->front++];
    return value;
  }
  return INT_MIN;
}

void saveQueueState(Queue *queue, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file != NULL) {
    for (int i = queue->front; i <= queue->rear; i++) {
      fprintf(
          file, "%d,",
          queue->items[i]); // Gunakan koma sebagai pemisah antara nilai-nilai
    }
    fprintf(file, "\n");
    fclose(file);
  }
}

bool loadQueueState(Queue *queue, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    int value;
    int count = 0;
    while (fscanf(file, "%d, ", &value) == 1) {
      enqueue(queue, value);
      count++;
    }
    fclose(file);
    return count > 0;
  }
  return false;
};