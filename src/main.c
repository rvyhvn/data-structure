#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../lib/sorting.h"
#include "../lib/structure.h"

void printArray(int arr[], int size) {
  for (int count = 0; count < size; count++) {
    printf("%d", arr[count]);
    if (count != size - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

void printBag(Bag *bag) {
  for (int count = 0; count < bag->count; count++) {
    printf("%d", bag->items[count]);
    if (count != bag->count - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

void printQueue(Queue *queue) {
  for (int i = queue->front; i <= queue->rear; i++) {
    printf("%d", queue->items[i]);
    if (i != queue->rear) {
      printf(", ");
    }
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <command> [options]\n", argv[0]);
    printf("Commands: stack, bags, queue, sort, linkedlist\n");
    return 1;
  }

  if (strcmp(argv[1], "stack") == 0) {
    if (argc < 4) {
      printf("Usage: %s stack <operation> <filename> [value]\n", argv[0]);
      return 1;
    }

    Stack tempStack;
    initStack(&tempStack);

    const char *filename = argv[3];
    if (!loadStackState(&tempStack, filename)) {
      initStack(&tempStack);
    }

    if (strcmp(argv[2], "push") == 0 && argc == 5) {
      int value = atoi(argv[4]);
      pushStack(&tempStack, value);
    } else if (strcmp(argv[2], "pop") == 0 && argc == 4) {
      int value = popStack(&tempStack);
      if (value != INT_MIN) {
        printf("Popped value from Stack: %d\n", value);
      } else {
        printf("Stack is empty.\n");
      }
    } else if (strcmp(argv[2], "is_full") == 0 && argc == 4) {
      bool isFull = isStackFull(&tempStack);
      printf("Is Stack full? %s\n", isFull ? "Yes" : "No");
    } else if (strcmp(argv[2], "is_empty") == 0 && argc == 4) {
      bool isEmpty = isStackEmpty(&tempStack);
      printf("Is Stack empty? %s\n", isEmpty ? "Yes" : "No");
    } else {
      printf("Invalid operation\n");
      return 1;
    }

    saveStackState(&tempStack, filename);
  } else if (strcmp(argv[1], "bags") == 0) {
    if (argc < 4) {
      printf("Usage: %s bags <operation> <filename> [value]\n", argv[0]);
      return 1;
    }

    Bag tempBag;
    initBag(&tempBag);

    const char *filename = argv[3];
    if (!loadBagState(&tempBag, filename)) {
      initBag(&tempBag);
    }

    if (strcmp(argv[2], "push") == 0 && argc == 5) {
      int value = atoi(argv[4]);
      insertToBag(&tempBag, value);
    } else if (strcmp(argv[2], "pop") == 0 && argc == 5) {
      int value = atoi(argv[4]);
      int removedValue = removeFromBag(&tempBag, value);
      if (removedValue != INT_MIN) {
        printf("Removed value from Bag: %d\n", removedValue);
      } else {
        printf("Value not found in the Bag.\n");
      }
    } else {
      printf("Invalid operation\n");
      return 1;
    }

    saveBagState(&tempBag, filename);

  } else if (strcmp(argv[1], "queue") == 0) {
    if (argc < 4) {
      printf("Usage: %s queue <operation> <filename> [value]\n", argv[0]);
      return 1;
    }

    Queue tempQueue;
    initQueue(&tempQueue);

    const char *filename = argv[3];
    if (!loadQueueState(&tempQueue, filename)) {
      initQueue(&tempQueue);
    }

    if (strcmp(argv[2], "enqueue") == 0 && argc == 5) {
      int value = atoi(argv[4]);
      enqueue(&tempQueue, value);
    } else if (strcmp(argv[2], "dequeue") == 0 && argc == 4) {
      int value = dequeue(&tempQueue);
      if (value != INT_MIN) {
        printf("Dequeued value from Queue: %d\n", value);
      } else {
        printf("Queue is empty.\n");
      }
    } else if (strcmp(argv[2], "is_full") == 0 && argc == 4) {
      bool isFull = isQueueFull(&tempQueue);
      printf("Is Queue full? %s\n", isFull ? "Yes" : "No");
    } else if (strcmp(argv[2], "is_empty") == 0 && argc == 4) {
      bool isEmpty = isQueueEmpty(&tempQueue);
      printf("Is Queue empty? %s\n", isEmpty ? "Yes" : "No");
    } else {
      printf("Invalid operation.\n");
      return 1;
    }

    saveQueueState(&tempQueue, filename);
  } else if (strcmp(argv[1], "sort") == 0) {
    int arr[] = {91, 71, 98, 89, 57, 32, 65, 5,  58, 57, 51, 29, 87,  16, 57,
                 17, 22, 83, 50, 7,  78, 20, 43, 99, 93, 19, 51, 10,  82, 57,
                 46, 29, 21, 76, 55, 71, 82, 13, 99, 7,  89, 97, 100, 4,  16,
                 40, 15, 19, 62, 69, 55, 13, 28, 31, 94, 53, 95, 18,  29, 54,
                 62, 59, 44, 37, 47, 70, 2,  48, 7,  27, 28, 4,  94,  66, 78,
                 88, 13, 66, 47, 81, 96, 87, 42, 1,  13, 11, 97, 51,  6,  100,
                 27, 26, 7,  80, 60, 54, 28, 38, 25, 99};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Unsorted array: \n");
    printArray(arr, size);
    printf("\n");
    printf("Array length: %d\n", size);

    if (argc < 3) {
      printf("Usage: %s sort <sorting_algorithm>\n", argv[0]);
      printf(
          "Available sorting algorithms: bubble, heap, insertion, "
          "selection, merge, quick, shell\n");
      return 1;
    }

    char *sortingAlgorithm = argv[2];

    clock_t start_time = clock();
    if (strcmp(sortingAlgorithm, "bubble") == 0) {
      printf("\nUsing bubble sort: \n");
      bubbleSort(arr, size);
    } else if (strcmp(sortingAlgorithm, "insertion") == 0) {
      printf("\nUsing insertion sort: \n");
      insertionSort(arr, size);
    } else if (strcmp(sortingAlgorithm, "selection") == 0) {
      printf("\nUsing selection sort: \n");
      selectionSort(arr, size);
    } else if (strcmp(sortingAlgorithm, "heap") == 0) {
      printf("\nUsing heap sort, heapifying first..\n");
      heapSort(arr, size);
    } else if (strcmp(sortingAlgorithm, "merge") == 0) {
      printf("\nUsing merge sort: \n");
      mergeSort(arr, 0, size - 1);
    } else if (strcmp(sortingAlgorithm, "quick") == 0) {
      printf("\nUsing quick sort: \n");
      quickSort(arr, 0, size - 1);
    } else if (strcmp(sortingAlgorithm, "shell") == 0) {
      printf("\nUsing shell sort: \n");
      shellSort(arr, size);
    } else {
      printf("Unknown sorting algorithms: %s\n", sortingAlgorithm);
      return 1;
    }

    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorted array: \n");
    printArray(arr, size);
    printf("\n");
    printf("Time taken: %f seconds\n", time_taken);
  } else if (strcmp(argv[1], "linkedlist") == 0) {
    struct Node *head = NULL;

    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 3);

    printf("Linked List: ");
    printLinkedList(head);

    return 0;

  } else {
    printf("Unknown command: %s\n", argv[1]);
    printf("Usage: %s <command> [options]\n", argv[0]);
    printf("Commands: stack, bags, queue, sort, linkedlist\n");
    return 1;
  }

  return 0;
}
