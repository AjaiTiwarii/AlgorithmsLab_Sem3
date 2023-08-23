// DIVIDE AND CONQUER APPROACH

#include<stdio.h>

void matrixMultiplication(int n,int a[][n],int b[][n],int c[][n])
{
    if(n==1)
    {
        c[0][0]=a[0][0]*b[0][0];
    }
    else
    {
        int mid=n/2;
        int a11[mid][mid],a12[mid][mid],a21[mid][mid],a22[mid][mid];
        int b11[mid][mid],b12[mid][mid],b21[mid][mid],b22[mid][mid];
        int c11[mid][mid],c12[mid][mid],c21[mid][mid],c22[mid][mid];
        int cn11[mid][mid],cn12[mid][mid],cn21[mid][mid],cn22[mid][mid];
       
        for(int i=0;i<mid;i++)
        {
            for(int j=0;j<mid;j++)
            {
                a11[i][j]=a[i][j];
                a12[i][j]=a[i][j+mid];
                a21[i][j]=a[i+mid][j];
                a22[i][j]=a[i+mid][j+mid];
               
                b11[i][j]=b[i][j];
                b12[i][j]=b[i][j+mid];
                b21[i][j]=b[i+mid][j];
                b22[i][j]=b[i+mid][j+mid];
            }
        }
       
        matrixMultiplication(mid,a11,b11,c11);
        matrixMultiplication(mid,a12,b21,c12);
        matrixMultiplication(mid,a11,b12,c21);
        matrixMultiplication(mid,a12,b22,c22);
       
        matrixMultiplication(mid,a21,b11,cn11);
        matrixMultiplication(mid,a22,b21,cn12);
        matrixMultiplication(mid,a21,b12,cn21);
        matrixMultiplication(mid,a22,b22,cn22);
       
        for(int i=0;i<mid;i++)
        {
            for(int j=0;j<mid;j++)
            {
                c[i][j]=c11[i][j]+c12[i][j];
                c[i][j+mid]=c21[i][j]+c22[i][j];
                c[i+mid][j]=cn11[i][j]+cn12[i][j];
                c[i+mid][j+mid]=cn21[i][j]+cn22[i][j];
            }
        }
    }
}
int main()
{
    int n;
    printf("Enter the number of rows or columns:");
    scanf("%d",&n);
    int a[n][n],b[n][n],c[n][n];
    printf("Enter the elements of  matrix a:\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    printf("Enter the elements of matrix b:\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&b[i][j]);
        }
    }
   
    matrixMultiplication(n,a,b,c);
   
    printf("Answer:\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d\t",c[i][j]);
        }
        printf("\n");
    }
   
    return 0;
}




// VOLKER STRASSEN'S APPROACH

#include <stdio.h>


void matrixAdd(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}


void matrixSub(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}


void matrix_multiply(int n, int A[][n], int B[][n], int C[][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    
    int m = n / 2;
    int A11[m][m], A12[m][m], A21[m][m], A22[m][m];
    int B11[m][m], B12[m][m], B21[m][m], B22[m][m];
    int C11[m][m], C12[m][m], C21[m][m], C22[m][m];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];
            A22[i][j] = A[i + m][j + m];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + m];
            B21[i][j] = B[i + m][j];
            B22[i][j] = B[i + m][j + m];
        }
    }

    
    int P1[m][m], P2[m][m], P3[m][m], P4[m][m];
    int P5[m][m], P6[m][m], P7[m][m];

    matrixAdd(m, A11, A22, C11);
    matrixAdd(m, B11, B22, C12);
    matrix_multiply(m, C11, C12, P1);

    matrixAdd(m, A21, A22, C11);
    matrix_multiply(m, C11, B11, P2);

    matrixSub(m, B12, B22, C12);
    matrix_multiply(m, A11, C12, P3);

    matrixSub(m, B21, B11, C12);
    matrix_multiply(m, A22, C12, P4);

    matrixAdd(m, A11, A12, C11);
    matrix_multiply(m, C11, B22, P5);

    matrixSub(m, A21, A11, C11);
    matrixAdd(m, B11, B12, C12);
    matrix_multiply(m, C11, C12, P6);

    matrixSub(m, A12, A22, C11);
    matrixAdd(m, B21, B22, C12);
    matrix_multiply(m, C11, C12, P7);

    //result to be stored in C11, C12, C21, C22
    int T1[m][m], T2[m][m];

    matrixAdd(m, P1, P4, T1);
    matrixSub(m, T1, P5, T2);
    matrixAdd(m, T2, P7, C11);

    matrixAdd(m, P3, P5, C12);

    matrixAdd(m, P2, P4, C21);

    matrixSub(m, P1, P2, T1);
    matrixAdd(m, T1, P3, T2);
    matrixAdd(m, T2, P6, C22);

    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = C11[i][j];
            C[i][j + m] = C12[i][j];
            C[i + m][j] = C21[i][j];
            C[i + m][j + m] = C22[i][j];
        }
    }
}


void printMatrix(int n, int matrix[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the size of matrices: ");
    scanf("%d", &n);

    int A[n][n], B[n][n], C[n][n];

    printf("Enter matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    matrix_multiply(n, A, B, C);

    printf("Resultant matrix C:\n");
    printMatrix(n, C);

    return 0;
}