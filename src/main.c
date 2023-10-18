#include "../lib/bstree.h"
#include "../lib/queue.h"
#include "../lib/sorting.h"
#include "../lib/stack.h"
#include "../lib/structure.h"
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
    int originalArr[] = {
	100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84,
	83,  82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67,
	66,  65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50,
	49,  48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33,
	32,  31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,
	15,  14, 13, 12, 11, 10, 9,  8,	 7,  6,	 5,  4,	 3,  2,	 1};
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
	    printf("Time taken for Selection Sort: %f seconds\n",
		   cpu_time_used);

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
	    printf("Time taken for Insertion Sort: %f seconds\n",
		   cpu_time_used);

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

	    memcpy(arr, originalArr, arr_size * sizeof(int));
	    break;
	case 8:
	    printf("Sorting (Shell)\n");
	    printf("Unsorted Array: \n");
	    printArray(arr, arr_size);
	    start = clock();
	    shellSort(arr, arr_size);
	    end = clock();
	    printf("Sorted Array: \n");
	    printArray(arr, arr_size);

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
