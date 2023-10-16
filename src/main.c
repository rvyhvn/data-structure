#include "../lib/queue.h"
#include "../lib/sorting.h"
#include "../lib/stack.h"
#include "../lib/structure.h"
#include "../lib/tree.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void printArray(int arr[], int size) {
  for (int count = 0; count < size; count++) {
    printf("%d", arr[count]);
    if (count != size - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

void stackMenu();
void queueMenu();
void bstreeMenu();

int main() {
  int originalArr[] = {5, 4, 3, 2, 1};
  int arr_size = sizeof(originalArr) / sizeof(originalArr[0]);
  int arr[arr_size];

  // Copy the original array to arr
  memcpy(arr, originalArr, arr_size * sizeof(int));

  int mainChoice;
  clock_t start, end;
  double cpu_time_used;

  do {
    printf("Main Menu:\n");
    printf("1. Data Structure (Stack)\n");
    printf("2. Data Structure (Queue)\n");
    printf("3. Data Structure (Tree)\n");
    printf("4. Sorting (Bubble)\n");
    printf("5. Sorting (Selection)\n");
    printf("6. Sorting (Insertion)\n");
    printf("7. Advanced Sorting (Merge)\n");
    printf("8. Advanced Sorting (Shell)\n");
    printf("9. Advanced Sorting (Quick Sort)\n");
    printf("0. Quit\n");
    printf("Option: ");
    scanf("%d", &mainChoice);

    switch (mainChoice) {
    case 1:
      printf("Data Structure (Stack)\n");
      stackMenu();
      break;
    case 2:
      printf("Data Structure (Queue)\n");
      queueMenu();
      break;
    case 3:
      printf("Data Structure (Tree)\n");
      bstreeMenu();
      break;
    case 4:
      printf("Sorting (Bubble)\n");
      printf("Unsorted Array: \n");
      printArray(arr, arr_size);
      start = clock();
      bubbleSort(arr, arr_size);
      end = clock();
      printf("Sorted Array: \n");
      printArray(arr, arr_size);
      cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Time taken for Bubble Sort: %f seconds\n", cpu_time_used);
      // Restore arr to its original values
      memcpy(arr, originalArr, arr_size * sizeof(int));
      break;
    case 5:
      printf("Sorting (Selection)\n");
      printf("Unsorted Array: \n");
      printArray(arr, arr_size);
      start = clock();
      selectionSort(arr, arr_size);
      end = clock();
      printf("Sorted Array: \n");
      printArray(arr, arr_size);
      cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Time taken for Selection Sort: %f seconds\n", cpu_time_used);
      // Restore arr to its original values
      memcpy(arr, originalArr, arr_size * sizeof(int));
      break;
    case 6:
      printf("Sorting (Insertion)\n");
      printf("Unsorted Array: \n");
      printArray(arr, arr_size);
      start = clock();
      insertionSort(arr, arr_size);
      end = clock();
      printf("Sorted Array: \n");
      printArray(arr, arr_size);
      cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Time taken for Insertion Sort: %f seconds\n", cpu_time_used);
      // Restore arr to its original values
      memcpy(arr, originalArr, arr_size * sizeof(int));
      break;
    case 7:
      printf("Advanced Sorting (Merge)\n");
      printf("Unsorted Array: \n");
      printArray(arr, arr_size);
      start = clock();
      mergeSort(arr, 0, arr_size - 1);
      end = clock();
      printf("Sorted Array: \n");
      printArray(arr, arr_size);
      cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Time taken for Merge Sort: %f seconds\n", cpu_time_used);
      // Restore arr to its original values
      memcpy(arr, originalArr, arr_size * sizeof(int));
      break;
    case 8:
      printf("Sorting (Shell)\n");
      printf("Unsorted Array: \n");
      printArray(arr, arr_size);
      // Implement shell sort first!
      // Calculate time here
      printf("Sorted Array: \n");
      printArray(arr, arr_size);
      // Restore arr to its original values
      memcpy(arr, originalArr, arr_size * sizeof(int));
      break;
    case 9:
      printf("Sorting (Quick Sort)\n");
      printf("Unsorted Array: \n");
      printArray(arr, arr_size);
      start = clock();
      quickSort(arr, 0, arr_size - 1);
      end = clock();
      printf("Sorted Array: \n");
      printArray(arr, arr_size);
      cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Time taken for Quick Sort: %f seconds\n", cpu_time_used);
      // Restore arr to its original values
      memcpy(arr, originalArr, arr_size * sizeof(int));
      break;
    case 0:
      printf("Quitting\n");
      break;
    default:
      printf("Menu invalid!\n");
    }

  } while (mainChoice != 0);

  return 0;
}
