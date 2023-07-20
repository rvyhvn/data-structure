#include "../lib/bubble-sort.h"
#include "../lib/selection-sort.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  int arr[] = {4, 2, 5, 7, 3, 1, 9};
  int size = sizeof(arr) / sizeof(arr[0]);

  printf("Unsorted array:\n");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  /* bubbleSort(arr, size); */

  selectionSort(arr, size);
  printf("Sorted: \n");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}
