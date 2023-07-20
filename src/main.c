#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../lib/sorting.h"

void printArray(int arr[], int size) {
  for (int count = 0; count < size; count++) {
    printf("%d", arr[count]);
    if (count < size - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("Usage: %s <sorting_algoritm>\n", argv[0]);
    printf(
        "Available sorting algorithms: bubble, heap, insertion, selection\n");
    return 1;
  }
  int arr[] = {22, 42, 41, 17, 64, 91, 54, 11, 52, 87, 65, 23};
  int size = sizeof(arr) / sizeof(arr[0]);
  printf("Unsorted array: \n");
  printArray(arr, size);
  printf("\n");
  printf("Array length: %d\n", size);

  char *sortingAlgorithm = argv[1];

  clock_t start_time = clock();
  if (strcmp(sortingAlgorithm, "bubble") == 0) {
    printf("\nUsing bubble sort: \n");
    bubbleSort(arr, size);
  } else if (strcmp(sortingAlgorithm, "heap") == 0) {
    printf("\nUsing heap sort: \n");
    heapSort(arr, size);
  } else if (strcmp(sortingAlgorithm, "insertion") == 0) {
    printf("\nUsing insertion sort: \n");
    insertionSort(arr, size);
  } else if (strcmp(sortingAlgorithm, "selection") == 0) {
    printf("\nUsing selection sort: \n");
    selectionSort(arr, size);
  } else {
    printf("Unknown sorting algorithms: %s\n", sortingAlgorithm);
    return 1;
  }

  clock_t end_time = clock();

  double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;
  /* bubbleSort(arr, size); */
  printf("Sorted array: \n");
  printArray(arr, size);
  printf("\n");
  printf("Time taken: %f\n", time_taken);
  return 0;
}
