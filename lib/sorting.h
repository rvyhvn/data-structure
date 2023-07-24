#ifndef SORTING_H
#define SORTING_H

void bubbleSort(int arr[], int size);

/* Functionality for heap sort */
void swap(int *a, int *b);
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int size);
/* ============= */

void insertionSort(int arr[], int size);
void selectionSort(int arr[], int size);
/* Functionality for merge sort */
void merge(int arr[], int p, int q, int r);
void mergeSort(int arr[], int l, int m);
/* ============ */
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);

#endif
