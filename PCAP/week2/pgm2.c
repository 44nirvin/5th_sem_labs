//1st August 2026

/*2. Implement an OpenMP program to read a matrix A 
     of size 5 × 5 and produce matrix B according to the 
     specified transformation:

     • Principal diagonal = 0
     • Elements below the diagonal = maximum value of the corresponding row in A
     • Elements above the diagonal = minimum value of the corresponding row in A*/
#include <stdio.h>
#include <omp.h>

int main() {
    int A[5][5], B[5][5];
    int i, j;
    printf("Enter the elements of Matrix A (5x5):\n");
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    double start = omp_get_wtime();

    #pragma omp parallel for private(j)
    for(i = 0; i < 5; i++) {
        int max = A[i][0];
        int min = A[i][0];

        for(j = 1; j < 5; j++) {
            if(A[i][j] > max)
                max = A[i][j];
            if(A[i][j] < min)
                min = A[i][j];
        }

        for(j = 0; j < 5; j++) {
            if(i == j)
                B[i][j] = 0;
            else if(i > j)
                B[i][j] = max;
            else
                B[i][j] = min;
        }

        printf("Row %d computed by Thread %d\n", i, omp_get_thread_num());
    }
    double end = omp_get_wtime();
    
    printf("\nMatrix B:\n");
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    printf("\nExecution Time = %lf seconds\n", end - start);
    return 0;
}
