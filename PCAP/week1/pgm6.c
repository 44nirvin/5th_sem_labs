//25 July 2026
/*q6:   Implement an OpenMP program to compute the 
	sum of elements of a large array in parallel
	using the parallel for directive. Measure and 
	display the execution time of the parallel
	program using the omp_get_wtime() runtime 
	function and compare it with the
	corresponding serial implementation.*/
	
#include <stdio.h>
#include <omp.h>


int main()
{
    int n;
    int sum1 = 0, sum2 = 0;

    printf("Enter Array Length: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements of the array:\n");
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    // -------- Serial --------
    double start = omp_get_wtime();
    for(int i = 0; i < n; i++){
        sum2 += arr[i];
    }

    double end = omp_get_wtime();
    double serial_time = end - start;

    // -------- Parallel --------
    start = omp_get_wtime();
    
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        #pragma omp critical
        {
            sum1 += arr[i];
        }
    }
    end = omp_get_wtime();
    double parallel_time = end - start;

    printf("\nSerial Sum = %d", sum2);
    printf("\nParallel Sum = %d", sum1);

    printf("\n\nSerial Time = %lf seconds", serial_time);
    printf("\nParallel Time = %lf seconds", parallel_time);

    return 0;
}
