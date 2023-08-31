#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int *randomizedpartition(int *arr, int *p, int *r) {
    srand(time(NULL));
    int RandomIndex = rand() % (*r - *p + 1) + *p;
    swap(&arr[RandomIndex], &arr[*r]);
    int pivot = arr[*r];
    int i = *p - 1;
    for (int j = *p; j < *r; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[*r]);
    return &arr[i + 1];
}

void randomizedquickSort(int *arr, int p, int r) {
     if (p < r) {
        int *q = randomizedpartition(arr, &p, &r);
        randomizedquickSort(arr, p, q - arr - 1);
        randomizedquickSort(arr, q + 1 - arr, r);
    }
}

void printArray(int *arr, int *p, int *r) {
    for (int i = *p; i <= *r; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int u;
    printf("enter the length of array");
    scanf("%d",&u);
    int arr[u];
    printf("enter the array");
    for(int i=0;i<u;i++)
    {
        scanf("%d",arr+i);
    }
    int n = sizeof(arr) / sizeof(arr[0]);
    int p = 0;
    int r = n - 1;
    // printf("Original array: ");
    // printArray(arr, &p, &r);
    randomizedquickSort(arr, p, r);
    printf("Sorted array: ");
    printArray(arr, &p, &r);
    return 0;
}