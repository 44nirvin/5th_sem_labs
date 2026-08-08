//8th august 2026
/*4. Write a parallel program using OpenMP to implement 
     the Merge Sort algorithm. Analyze the performance 
     by computing:
   	• Sequential execution time
  	• Parallel execution time
     	• Speedup
   	• Efficiency

for varying input sizes and thread counts.*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int a[], int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = 0;

    int *temp = (int *)malloc((high - low + 1) * sizeof(int));

    while(i <= mid && j <= high)
    {
        if(a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while(i <= mid)
        temp[k++] = a[i++];

    while(j <= high)
        temp[k++] = a[j++];

    for(i = low, k = 0; i <= high; i++, k++)
        a[i] = temp[k];

    free(temp);
}

void mergeSort(int a[], int low, int high)
{
    if(low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);

        merge(a, low, mid, high);
    }
}

void parallelMergeSort(int a[], int low, int high)
{
    if(low < high)
    {
        int mid = (low + high) / 2;

        #pragma omp task
        parallelMergeSort(a, low, mid);

        #pragma omp task
        parallelMergeSort(a, mid + 1, high);

        #pragma omp taskwait
        merge(a, low, mid, high);
    }
}

int main()
{
    int n, threads, i;
    double start, end;
    double serialTime, parallelTime;
    double speedup, efficiency;

    printf("Enter array size: ");
    scanf("%d", &n);

    printf("Enter number of threads: ");
    scanf("%d", &threads);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for(i = 0; i < n; i++)
    {
        a[i] = rand() % 100000;
        b[i] = a[i];
    }

    /* Sequential Merge Sort */
    start = omp_get_wtime();

    mergeSort(a, 0, n - 1);

    end = omp_get_wtime();

    serialTime = end - start;

    /* Parallel Merge Sort */
    omp_set_num_threads(threads);

    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        parallelMergeSort(b, 0, n - 1);
    }

    end = omp_get_wtime();

    parallelTime = end - start;

    speedup = serialTime / parallelTime;
    efficiency = speedup / threads;

    printf("\nSequential execution time = %f seconds\n", serialTime);
    printf("Parallel execution time   = %f seconds\n", parallelTime);
    printf("Speedup                   = %f\n", speedup);
    printf("Efficiency                = %f\n", efficiency);

    free(a);
    free(b);

    return 0;
}

/*output:
Enter array size: 100000
Enter number of threads: 5

Sequential execution time = 0.010967 seconds
Parallel execution time   = 0.066417 seconds
Speedup                   = 0.165128
Efficiency                = 0.033026




expanation: 
The program implements Merge Sort in both sequential and parallel forms. The array is first filled with random values, then the sequential version sorts one copy while the parallel version divides the sorting work into separate OpenMP tasks. The execution time of both versions is measured using omp_get_wtime(). Speedup is calculated by comparing sequential time with parallel time, while efficiency is calculated by dividing speedup by the number of threads. The results can be affected by thread/task overhead, but with larger input sizes the parallel version is expected to make better use of multiple threads.
*/



