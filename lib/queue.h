#ifndef QUEUE_H
#define QUEUE_H

typedef struct NodeQueue NodeQueue;
NodeQueue *createQueue(int value);
void enqueue(NodeQueue **front, NodeQueue **rear, int value);
int dequeue(NodeQueue **front, NodeQueue **rear);
int peekQueue(NodeQueue *front);

#endif // QUEUE_H
