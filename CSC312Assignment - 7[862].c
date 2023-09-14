#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int partition(int *A, int p, int r) {
    int i = p + rand() % (r - p + 1);
    int x = A[i];
    A[i] = A[r];
    A[r] = x;
    i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            int y = A[i];
            A[i] = A[j];
            A[j] = y;
        }
    }
    int y = A[i + 1];
    A[i + 1] = A[r];
    A[r] = y;
    return i + 1;
}

int random_parti(int *A, int *p, int *r) {
    srand(time(NULL));
    return partition(A, *p, *r);
}


int random_select(int *A, int *p, int *r, int *i) {
    if (*p == *r) {
        return A[*p];
    }
    int q = random_parti(A, p, r);
    int k = q - *p + 1;
    if (*i == k) {
        return A[q];
    } else if (*i < k) {
        return random_select(A, p, &q - 1, i);
    } else {
        int t =(*i - k);
        return random_select(A, &q + 1, r, &t);
    }
}

int Dpartition(int *A, int p, int r,int k) {
    int x = k;
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            int y = A[i];
            A[i] = A[j];
            A[j] = y;
        }
    }

    int y = A[i + 1];
    A[i + 1] = A[r];
    A[r] = y;

    return i + 1;
}

int baby_median(int *A, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
    return A[n / 2];
}

int deterministic_select(int *A, int p, int r, int i) {
    if (p == r) {
        return A[p];
    }
    int n = r - p + 1;
    int num_groups = n / 5;
    if (n % 5 != 0) {
        num_groups++;
    }
    int medians[num_groups];
    for (int j = 0; j < num_groups; j++) {
        int group_size = (j == num_groups - 1) ? n % 5 : 5;
        int group[group_size];
        for (int k = 0; k < group_size; k++) {
            group[k] = A[p + j * 5 + k];
        }
        medians[j] = baby_median(group, group_size);
    }
    int x = deterministic_select(medians, 0, num_groups - 1, num_groups / 2);
    int q = Dpartition(A, p, r, x);
    int k = q - p + 1;
    if (i == k) {
        return A[q];
    } else if (i < k) {
        return deterministic_select(A, p, q - 1, i);
    } else {
        return deterministic_select(A, q + 1, r, i - k);
    }
}


int main() {
    int i, j, n, x, z, p, r, A[20];
    printf("Enter the number lower and upper bounds of the array elements\n");
    scanf("%d %d", &p, &r);
    n = r - p + 1;
    printf("Enter %d number of array elements\n", n);
    for (j = p; j <= r; j++) {
        scanf("%d", &A[j]);
    }
    printf("Enter the minimum element you want to search\n");
    scanf("%d", &i);
    do {
        printf("\n1. Randomized Select\n");
        printf("2. Deterministic Select\n");
        printf("3. Exit from the program\n");
        printf("Enter your option: ");
        scanf("%d", &x);
        switch (x) {
            case 1:
                z = random_select(A, &p, &r, &i);
                printf("The %d minimum element is %d", i, z);
                break;
            case 2:
                z = deterministic_select(A, p, r, i);
                printf("The %d minimum element is %d", i,z);
                break;
        }
    } while (x <= 2);
    return 0;
}
