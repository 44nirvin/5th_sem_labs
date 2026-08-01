//1st August 2026

/*q1: 1. Implement an OpenMP program using the 
	parallel for work-sharing construct to perform 
	the addition of two matrices of size M×N. Display 
	the resultant matrix and the Thread ID responsible 
	for computing each row. Compare the execution time 
	of the serial and parallel implementations and 
	comment on the distribution of loop iterations 
	among the threads.*/
	
#include <stdio.h>
#include <omp.h>

int main(){
    int M, N;
    int i, j;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &M, &N);

    int A[M][N], B[M][N], C[M][N];

    printf("\nEnter Matrix A:\n");
    for(i = 0; i < M; i++) {
        for(j = 0; j < N; j++){
            scanf("%d", &A[i][j]);
        }
    }

    printf("\nEnter Matrix B:\n");
    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++){
            scanf("%d", &B[i][j]);
        }
    }

    double start, end;
    double serial_time, parallel_time;

    /* Serial Matrix Addition */
    start = omp_get_wtime();

    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    end = omp_get_wtime();
    serial_time = end - start;

    printf("\nSerial Result Matrix:\n");
    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++){
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    /* Parallel Matrix Addition */
    start = omp_get_wtime();

    #pragma omp parallel for private(j)
    for(i = 0; i < M; i++){
        int tid = omp_get_thread_num();
        printf("Row %d computed by Thread %d\n", i, tid);
        for(j = 0; j < N; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    end = omp_get_wtime();
    parallel_time = end - start;

    printf("\nParallel Result Matrix:\n");
    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++){
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    printf("\nSerial Execution Time   : %lf seconds\n", serial_time);
    printf("Parallel Execution Time : %lf seconds\n", parallel_time);

    return 0;
}

/*Serial Result Matrix:
10 10 10 
10 10 10 
10 10 10 
Row 0 computed by Thread 0
Row 1 computed by Thread 1
Row 2 computed by Thread 2

Parallel Result Matrix:
10 10 10 
10 10 10 
10 10 10 

Serial Execution Time   : 0.000001 seconds
Parallel Execution Time : 0.013140 seconds*/
		
		

