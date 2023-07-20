#include "../lib/insertion-sort.h"

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
};
