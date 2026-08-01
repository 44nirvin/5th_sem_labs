//1st August 2026

/* q4: Implement an OpenMP program to perform matrix-vector
       multiplication. Record the effect of increasing matrix
       size on execution time.*/
       
#include <stdio.h>
#include <omp.h>

int main() {
    int M, N;
    int i, j;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &M, &N);

    int A[M][N], B[N], C[M];

    printf("Enter Matrix A:\n");
    for(i = 0; i < M; i++) {
        for(j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter Vector B:\n");
    for(i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }

    double start = omp_get_wtime();

    #pragma omp parallel for private(j)
    for(i=0;i<M;i++){
    	C[i]=0;
    	for(j=0;j<N;j++){
		C[i] += A[i][j] * B[j];
	}
	printf("Row %d by Thread %d\n",i, omp_get_thread_num());
    }

    double end = omp_get_wtime();

    printf("\nResultant Vector:\n");
    for(i = 0; i < M; i++) {
        printf("%d ", C[i]);
    }

    printf("\n\nExecution Time = %lf seconds\n", end - start);

    return 0;
}
