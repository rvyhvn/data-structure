#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "../lib/queue.h"

struct NodeQueue {
  int data;
  struct NodeQueue *next;
};

NodeQueue* createQueue(int value) {
  NodeQueue *newQueue = (NodeQueue *)malloc(sizeof(NodeQueue));
  if (newQueue != NULL) {
    newQueue->data = value;
    newQueue->next = NULL;
  }
  return newQueue;
}

void enqueue(NodeQueue **front, NodeQueue **rear, int value) {
  NodeQueue *newNode = createQueue(value);
  if (newNode != NULL) {
    if (*rear == NULL) {
      *front = newNode;
      *rear = newNode;
    } else {
      (*rear)->next = newNode;
      *rear = newNode;
    }
  }
}

int dequeue(NodeQueue **front, NodeQueue **rear) {
  if (*front == NULL) {
    return -1; // Queue is empty
  }
  int data = (*front)->data;
  NodeQueue *temp = *front;
  *front = (*front)->next;
  if (*front == NULL) {
    *rear = NULL; // If the last element is dequeued
  }
  free(temp);
  return data;
}

int peekQueue(NodeQueue *front) {
  if (front == NULL) {
    return -1; // Queue is empty
  }
  return front->data;
}

void queueMenu() {
    NodeQueue *front = NULL;
    NodeQueue *rear = NULL;
    int queueChoice;

    do {
        printf("Queue Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("0. Back\n");
        printf("Option: ");
        scanf("%d", &queueChoice);

        switch (queueChoice) {
            case 1:
                printf("Enter a value to enqueue: ");
                int value;
                scanf("%d", &value);
                enqueue(&front, &rear, value);
                break;
            case 2: {
                int dequeued = dequeue(&front, &rear);
                if (dequeued != -1) {
                    printf("Dequeued value: %d\n", dequeued);
                } else {
                    printf("Queue is empty.\n");
                }
                break;
            }
            case 3: {
                int peeked = peekQueue(front);
                if (peeked != -1) {
                    printf("Front value: %d\n", peeked);
                } else {
                    printf("Queue is empty.\n");
                }
                break;
            }
            case 0:
                break;
            default:
                printf("Menu invalid!\n");
        }

    } while (queueChoice != 0);
}


