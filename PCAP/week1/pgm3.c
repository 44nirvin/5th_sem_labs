//25 July 2026

/*q3: Implement an OpenMP program to initialize 
all elements of a 5 × 5 matrix with consecutive
integers inside a parallel region using the parallel 
directive. Display the initialized matrix
and print the Thread ID responsible for 
initializing each row.*/

#include <stdio.h>
#include <omp.h>

int main()
{
    int arr[5][5];
    int thread_responsible[5];
    int value = 1;
    omp_set_num_threads(5);
    int j;
    //int j initialised outside; for the use of "for private(j)" instead of just for
    //this will make it so that the parallel processes are truly parallel. (read end of file)
    #pragma omp parallel for private(j)
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            arr[i][j] = i * 5 + j + 1;
        }
        thread_responsible[i] = omp_get_thread_num();
    }
    printf("Matrix:\n");
    
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++)
            printf("%3d ", arr[i][j]);
        printf("\n");
    }

    printf("\n");

    for(int i = 0; i < 5; i++)
        printf("Row %d initialized by Thread %d\n",
               i + 1,
               thread_responsible[i]);

    return 0;
}

//pragma omp parallel "for" is used.
//it makes parallel framework for the usage of parallel for loops. preventing race condition.
		
//Another thing that can be done:
//#pragma omp parallel for private(j)
//this will give each thread its own version of j so there is no race condition
		
