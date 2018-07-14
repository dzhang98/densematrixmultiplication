#include<stdlib.h>
#include<stdio.h>
#define MATSIZE 8

void freeMatrix(int n, int ** matrix);
int readMatrixSize(char * filename);
int **readMatrix(char * filename);
void denseMatrixMult(int **matrix1, int **matrix2, int ***resultMatrix, int n);
void initMatrix(int ***matrix, int n);
int **sum(int ** A, int ** B, int x1, int y1, int x2, int y2, int n);
int **sub(int ** A, int ** B, int x1, int y1, int x2, int y2, int n);
void printMatrix(int n, int ** A);


void denseMatrixMult(int ** A, int ** B, int *** resultMatrix, int n)
{
    int **C;
    initMatrix(&C, n);
    if(n==1){
        **C = A[0][0] * B[0][0];
    }
    else{

    int **A00, **A01, **A10, **A11, **B00, **B01, **B10, **B11;
    int i, j, k, m;
    int **A0011, **B0011, **A1011, **B0111, **B1000, **A0001, **A1000, **B0001, **A0111, **B1011;
    int **M0, **M1, **M2, **M3, **M4, **M5, **M6;
    int **M03, **M034, **M01, **M012;
    int **C00, **C01, **C10, **C11;

    initMatrix(&A00, n/2);
    initMatrix(&A01, n/2);
    initMatrix(&A10, n/2);
    initMatrix(&A11, n/2);
    initMatrix(&B00, n/2);
    initMatrix(&B01, n/2);
    initMatrix(&B10, n/2);
    initMatrix(&B11, n/2);

    for (i=0; i<n/2; i++)
    {
        for (j=0; j<n/2; j++)
        {
            A00[i][j] = A[i][j];
            A01[i][j] = A[i+n/2][j];
            A10[i][j] = A[i][j+n/2];
            A11[i][j] = A[i+n/2][j+n/2];
            B00[i][j] = B[i][j];
            B01[i][j] = B[i+n/2][j];
            B10[i][j] = B[i][j+n/2];
            B11[i][j] = B[i+n/2][j+n/2];
        }

    }
    A0011 = sum(A00, A11, 0, 0, 0, 0, n/2);
    B0011 = sum(B00, B11, 0, 0, 0, 0, n/2);
    A1011 = sum(A10, A11, 0, 0, 0, 0, n/2);
    B0111 = sub(B01, B11, 0, 0, 0, 0, n/2);
    B1000 = sub(B10, B00, 0, 0, 0, 0, n/2);
    A0001 = sum(A00, A01, 0, 0, 0, 0, n/2);
    A1000 = sub(A10, A00, 0, 0, 0, 0, n/2);
    B0001 = sum(B00, B01, 0, 0, 0, 0, n/2);
    A0111 = sub(A01, A11, 0, 0, 0, 0, n/2);
    B1011 = sum(B10, B11, 0, 0, 0, 0, n/2);

    denseMatrixMult(A0011, B0011, &M0, n/2);
    denseMatrixMult(A1011, B00, &M1, n/2);
    denseMatrixMult(A00, B0111, &M2, n/2);
    denseMatrixMult(A11, B1000, &M3, n/2);
    denseMatrixMult(A0001, B11, &M4, n/2);
    denseMatrixMult(A1000, B0001, &M5, n/2);
    denseMatrixMult(A0111, B1011, &M6, n/2);

    M03 = sum(M0, M3, 0, 0, 0, 0, n/2);
    M034 = sub(M03, M4, 0, 0, 0, 0, n/2);
    C00 = sum(M034, M6, 0, 0, 0, 0, n/2);
    C01 = sum(M2, M4, 0, 0, 0, 0, n/2);
    C10 = sum(M1, M3, 0, 0, 0, 0, n/2);
    M01 = sub(M0, M1, 0, 0, 0, 0, n/2);
    M012 = sum(M01, M2, 0, 0, 0, 0, n/2);
    C11 = sum(M012, M5, 0, 0, 0, 0, n/2);

    for (k=0; k<n/2; k++){
        for (m=0; m<n/2; m++){
            C[k][m] = C00[k][m];
            C[k+n/2][m] = C01[k][m];
            C[k][m+n/2] = C10[k][m];
            C[k+n/2][m+n/2] = C11[k][m];
        }
    }

    freeMatrix(n/2, A00);
    freeMatrix(n/2, A01);
    freeMatrix(n/2, A10);
    freeMatrix(n/2, A11);
    freeMatrix(n/2, B00);
    freeMatrix(n/2, B01);
    freeMatrix(n/2, B10);
    freeMatrix(n/2, B11);
    freeMatrix(n/2, A0011);
    freeMatrix(n/2, B0011);
    freeMatrix(n/2, A1011);
    freeMatrix(n/2, B0111);
    freeMatrix(n/2, B1000);
    freeMatrix(n/2, A0001);
    freeMatrix(n/2, A1000);
    freeMatrix(n/2, B0001);
    freeMatrix(n/2, A0111);
    freeMatrix(n/2, B1011);
    freeMatrix(n/2, M0);
    freeMatrix(n/2, M1);
    freeMatrix(n/2, M2);
    freeMatrix(n/2, M3);
    freeMatrix(n/2, M4);
    freeMatrix(n/2, M5);
    freeMatrix(n/2, M6);
    freeMatrix(n/2, M03);
    freeMatrix(n/2, M034);
    freeMatrix(n/2, M01);
    freeMatrix(n/2, M012);
    freeMatrix(n/2, C00);
    freeMatrix(n/2, C01);
    freeMatrix(n/2, C10);
    freeMatrix(n/2, C11);



    }
     *resultMatrix = C;
}

int **sum(int ** A, int ** B, int x1, int y1, int x2, int y2, int n)
{
    int i, j, k;
    int ** sum = (int **)malloc(n*sizeof(int*));
    if (sum != NULL){
        for (i=0; i<n; i++){
            sum[i] = (int *)malloc(n*sizeof(int));
        }
    }
    for (j=0; j<n; j++){
        for (k=0; k<n; k++){
            sum[j][k] = A[x1+j][y1+k] + B[x2+j][y2+k];
        }
    }
    return sum;
}

int **sub(int **A, int **B, int x1, int y1, int x2, int y2, int n)
{
    int i, j, k;
    int ** sub = (int **)malloc(n*sizeof(int*));
    if (sub != NULL){
        for (i=0; i<n; i++){
            sub[i] = (int *)malloc(n*sizeof(int));
        }
    }
    for (j=0; j<n; j++){
        for (k=0; k<n; k++){
            sub[j][k] = A[x1+j][y1+k] - B[x2+j][y2+k];
        }
    }
    return sub;
}

void initMatrix(int ***mat,int n)
{
    int i, j;
    int **a = (int **)malloc(n*sizeof(int*));
    if (a != NULL){
        for (i=0; i<n; i++){
            a[i] = (int *)malloc(n*sizeof(int));
            for(j=0; j<n; j++){
                a[i][j]=0;
            }
        }

    }
    *mat = a;
}

int **readMatrix(char * filename)
{
    FILE * fp = fopen(filename, "r");
    int ** mat;
    initMatrix(&mat, MATSIZE);
    int i, j;
    for (i=0; i<MATSIZE; i++){
        for (j=0; j<MATSIZE; j++){
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    fclose(fp);
    return mat;

}

void freeMatrix(int n, int ** matrix)
{
    int i;
    for (i=0; i<n; i++){
        free(matrix[i]);
    }
    free(matrix);
}

void printMatrix(int n, int ** A)
{
    int i, j;
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

}
