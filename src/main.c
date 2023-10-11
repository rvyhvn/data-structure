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
void treeMenu();

int main() {

  int arr[] = {5, 4, 3, 2, 1};
  int arr_size = sizeof(arr) / sizeof(arr[0]);
  int mainChoice;
  do {
    printf("Main Menu:\n");
    printf("1. Data Structure (Stack)\n");
    printf("2. Data Structure (Queue)\n");
    printf("3. Data Structure (Tree)\n");
    printf("4. Sorting (Bubble)\n");
    printf("5. Sorting (Selection) \n");
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
      treeMenu();
      break;
    case 4:
      printf("Sorting (Bubble)\n");
      bubbleSort(arr, arr_size);
      printArray(arr, arr_size);
      break;
    case 5:
      printf("Sorting (Selection)\n");
      selectionSort(arr, arr_size);
      printArray(arr, arr_size);
      break;
    case 6:
      printf("Sorting (Insertion)\n");
      insertionSort(arr, arr_size);
      printArray(arr, arr_size);
      break;
    case 7:
      printf("Advanced Sorting (Merge)\n");
      mergeSort(arr, 0, arr_size - 1);
      printArray(arr, arr_size);
      break;
    case 8:
      printf("Sorting (Shell)\n");
      shellSort(arr, arr_size);
      printArray(arr, arr_size);
      break;
    case 9:
      printf("Sorting (Quick Sort)\n");
      quickSort(arr, 0, arr_size - 1);
      printArray(arr, arr_size);
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
