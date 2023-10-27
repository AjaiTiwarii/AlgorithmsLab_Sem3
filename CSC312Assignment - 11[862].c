#include <stdio.h>

#define M 1000

int parent[M];
int rank[M];

void makeset(int v);
int findset(int v);
// int munion(int u, int v);
void munion(int u, int v);

int main() {
    int n, i, t, flag, count = 0;

    printf("How many disjoint sets do you want to create? ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        makeset(i);
    }

    printf("%d number of makeset operations are executed\n", n);

    printf("To stop Union operation, press -1\n");

    while (t != -1) {
        printf("Enter the value of t: ");
        scanf("%d", &t);
        if (t != -1) {
            int i, j;
            printf("Enter i and j to perform Union(i, j) operation\n");
            printf("i = ");
            scanf("%d", &i);
            printf("j = ");
            scanf("%d", &j);
            munion(i, j);
            printf("UNION(%d, %d) is finished\n", i, j);
        }
    }

    
    for (i = 1; i <= n; i++) {
        if (findset(i) == i) {
            count++;
        }
    }
    printf("The number of connected components is %d\n", count);
    

    return 0;
}

void makeset(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int findset(int v) {
    if (v != parent[v]) {
        parent[v] = findset(parent[v]); // Path compression
    }
    return parent[v];
}


void munion(int u, int v) {
    u = findset(u);
    v = findset(v);

    if (u != v) {
        if (rank[u] < rank[v]) {
            parent[u] = v;
        } else if (rank[u] > rank[v]) {
            parent[v] = u;
        } else {
            parent[v] = u;
            rank[u]++;
        }
        return;
    }
    return ;
}