// An example of how to use Malloc and Calloc together
#include <stdio.h>
#include <stdlib.h>

int main() {
    int* arr1;  // Pointer for the first array
    int* arr2;  // Pointer for the second array

    // Using malloc to allocate memory for an array of 5 integers
    arr1 = (int*)malloc(5 * sizeof(int));

    // Check if memory allocation using malloc was successful
    if (arr1 != NULL) {
        printf("Memory for arr1 allocated successfully.\n");

        // Initialize values in arr1
        for (int i = 0; i < 5; ++i) {
            arr1[i] = i + 1;
        }

        // Print values in arr1
        printf("Values in arr1: ");
        for (int i = 0; i < 5; ++i) {
            printf("%d ", arr1[i]);
        }
        printf("\n");
    } else {
        // Memory allocation failed
        printf("Memory allocation for arr1 failed.\n");
    }

    // Using calloc to allocate memory for an array of 5 integers
    arr2 = (int*)calloc(5, sizeof(int));

    // Check if memory allocation using calloc was successful
    if (arr2 != NULL) {
        printf("Memory for arr2 allocated successfully.\n");

        // Initialize values in arr2
        for (int i = 0; i < 5; ++i) {
            arr2[i] = (i + 1) * 2;
        }

        // Print values in arr2
        printf("Values in arr2: ");
        for (int i = 0; i < 5; ++i) {
            printf("%d ", arr2[i]);
        }
        printf("\n");
    } else {
        // Memory allocation failed
        printf("Memory allocation for arr2 failed.\n");
    }

    // Free the allocated memory when done
    free(arr1);
    free(arr2);

    return 0;
}

