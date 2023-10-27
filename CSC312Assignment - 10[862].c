#include <stdio.h>
#include <stdlib.h>

//structure for a linked list node
struct Node {
    float data;
    struct Node* next;
};

//insertion sort function
struct Node* InsertionSort(struct Node* list) {
    if (list == NULL || list->next == NULL) {
        return list;
    }

    struct Node* start = (struct Node*)malloc(sizeof(struct Node));
    start->next = list;

    struct Node* curr = list, *prev = start;
    while (curr) {
        if (curr->next && (curr->next->data < curr->data)) { 
            // Insertion 
            while (prev->next && (prev->next->data < curr->next->data)) { 
                prev = prev->next;
            }
            struct Node* temp = prev->next;
            prev->next = curr->next;
            curr->next = curr->next->next;
            prev->next->next = temp;
            prev = start;
        } else
            curr = curr->next;
    }
    struct Node* sortedList = start->next;
    free(start);  // Free the start node
    return sortedList;
}

// Function to print the elements in a bucket
void PrintBucket(struct Node* list) {
    struct Node* current = list;

    while (current != NULL) {
        printf("%.2f -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Bucket sort Function
void BucketSort(float A[], int n) {
    if (n <= 0) {
        return;
    }

    // Creating Buckets --> array of linkrd lists
    int numBuckets = n;
    struct Node* buckets[numBuckets];
    
    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = NULL;
    }

    // Place elements in their respective buckets
    for (int i = 0; i < n; i++) {
        int index = (int)(A[i] * numBuckets);
        
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = A[i];
        newNode->next = buckets[index];
        //newNode->next = NULL;
        buckets[index] = newNode;
    }

    // Print the elements in each bucket
    for (int i = 0; i < numBuckets; i++) {
        printf("Bucket %d: ", i);
        PrintBucket(buckets[i]);
    }

    // Sorting each bucket using insertion sort
    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = InsertionSort(buckets[i]);
    }

    // Print the elements in each bucket
    for (int i = 0; i < numBuckets; i++) {
        printf("Bucket %d: ", i);
        PrintBucket(buckets[i]);
    }

    // Merge the sorted buckets back into the original array
    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        struct Node* current = buckets[i];
        while (current != NULL) {
            A[index] = current->data;
            index++;
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// Function to print the sorted array
void PrintArray(float A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", A[i]);
    }
    printf("\n");
}

int main() {
    float A[] = {0.85, 0.45, 0.95, 0.67, 0.92, 0.34, 0.56, 0.78, 0.23, 0.49};
    int n = sizeof(A) / sizeof(A[0]);
    //int n=10;

    printf("Unsorted Array: ");
    PrintArray(A, n);

    BucketSort(A, n);

    printf("Sorted Array: ");
    PrintArray(A, n);

    return 0;
}

