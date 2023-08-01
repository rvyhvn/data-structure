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

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("Usage: %s <command> [options]\n", argv[0]);
    printf("Commands: stack, bags, sort\n");
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
  } else if (strcmp(argv[1], "sort") == 0) {
    int arr[] = {22, 42, 41, 17, 64, 91, 54, 11, 52, 87, 65, 23};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Unsorted array: \n");
    printArray(arr, size);
    printf("\n");
    printf("Array length: %d\n", size);

    if (argc < 3) {
      printf("Usage: %s sort <sorting_algorithm>\n", argv[0]);
      printf("Available sorting algorithms: bubble, heap, insertion, "
             "selection, merge, quick\n");
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
    } else {
      printf("Unknown sorting algorithms: %s\n", sortingAlgorithm);
      return 1;
    }

    clock_t end_time = clock();

    double time_taken =
        ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;
    printf("Sorted array: \n");
    printArray(arr, size);
    printf("\n");
    printf("Time taken: %f\n", time_taken);
  } else {
    printf("Unknown command: %s\n", argv[1]);
    printf("Usage: %s <command> [options]\n", argv[0]);
    printf("Commands: stack, bags, sort\n");
    return 1;
  }

  return 0;
}
