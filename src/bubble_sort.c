#include "../lib/bubble-sort.h"
#include <stdio.h>

void bubbleSort(int *arr, int size) {
  int temp;
  int swapped;

  for (int i = 0; i < size; i++) {
    swapped = 0;

    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;

        swapped = 1;
      }
    }
    if (swapped == 0) {
      break;
    }
  }
}
