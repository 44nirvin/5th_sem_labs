//8th August 2026
/*2. Implement a C program using OpenMP to process an integer array 
     in parallel and demonstrate the use of the following synchronization 
     constructs:
	  • critical
 	  • atomic
 	  • reduction
 	  • master

     The program should perform the following tasks:
 	  1. The master thread should initialize the array and display 
 	     the total number of threads participating in the computation.
   	  2. Use the reduction clause to compute the sum of all array elements 
   	     in parallel.
   	  3. Use the atomic construct to count the number of even elements in 
   	     the array.
          4. Use the critical construct to allow each thread to safely display its 
             thread ID and the partial sum of the array elements processed by that thread.
   	  5. After all threads complete execution, the master thread should display the final 
             sum of the array elements and the total count of even numbers.*/
         
#include <stdio.h>
#include <omp.h>

int main()
{
    int n, i;
    int sum = 0;
    int evenCount = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter elements:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("\nNumber of threads = %d\n", omp_get_num_threads());
        }

        #pragma omp for reduction(+:sum)
        for(i = 0; i < n; i++)
            sum += a[i];
        

        #pragma omp for
        for(i = 0; i < n; i++){
            if(a[i] % 2 == 0)
            {
                #pragma omp atomic
                evenCount++;
            }
        }

        #pragma omp for
        for(i = 0; i < n; i++){
            #pragma omp critical
            {
                printf("Thread %d processed element %d\n",
                       omp_get_thread_num(), a[i]);
            }
        }
    }

    printf("\nFinal sum = %d\n", sum);
    printf("Total even numbers = %d\n", evenCount);

    return 0;
    
    
    
}
/*input:
Enter number of elements: 10
Enter elements:
1
2
3
4
5
6
7
8
9
10
/*
/*output: 
Number of threads = 20
Thread 3 processed element 4
Thread 6 processed element 7
Thread 7 processed element 8
Thread 8 processed element 9
Thread 9 processed element 10
Thread 1 processed element 2
Thread 2 processed element 3
Thread 4 processed element 5
Thread 5 processed element 6
Thread 0 processed element 1

Final sum = 55
Total even numbers = 5
*/

/*master: The master thread displays the total number of threads, which is 20.
reduction: Each thread calculates part of the array sum, and OpenMP safely combines them to get 55.
atomic: Each even number increments evenCount safely, giving 5 even numbers.
critical: Only one thread prints at a time, preventing multiple threads from interfering with each other's output.
The threads process different elements in parallel, improving execution speed while synchronization prevents incorrect results.*/
