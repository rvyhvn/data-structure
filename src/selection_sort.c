#include "../lib/selection-sort.h"

void selectionSort(int *arr, int size) {
  int minIndex, temp;

  for (int i = 0; i < size - 1; i++) {
    minIndex = i;

    for (int j = i + 1; j < size; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }

    temp = arr[i];
    arr[i] = arr[minIndex];
    arr[minIndex] = temp;
  }
};
