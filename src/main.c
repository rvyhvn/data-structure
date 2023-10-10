#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/queue.h"
#include "../lib/stack.h"
#include "../lib/sorting.h"
#include "../lib/structure.h"

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

int main() {
  int mainChoice;
  do {
        printf("Main Menu:\n");
        printf("1. Data Structure (Stack)\n");
        printf("2. Data Structure (Queue)\n");
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
            case 0:
                printf("Quitting\n");
                break;
            default:
                printf("Menu invalid!\n");
        }

    } while (mainChoice != 0);

  return 0;
}
