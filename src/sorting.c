#include "../lib/sorting.h"

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

void insertionSort(int *arr, int size) {
  int key, j;

  for (int i = 1; i < size; i++) {
    key = arr[i];
    j = i - 1;

    // Berpindah ke array 0 sampai i-1 yang nilainya lebih besar dari key(kunci)
    // ke posisi paling depan dari posisi value terkini
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }

    arr[j + 1] = key;
  }
}

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
}

void heapSort(int *arr, int size) {
  (void)arr;
  (void)size;
}
