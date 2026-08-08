//8th august 2026

/*3. Implement an OpenMP program using C to determine the 
     number of prime numbers within a given range (1 to N) 
     using the parallel for directive. Since checking whether 	
     a number is prime requires a varying amount of computation 
     depending on the number being tested, this problem 
     exhibits an imbalanced workload across loop iterations.
     
     Execute the program separately using the following 
     OpenMP scheduling policies:
   	• schedule(static)
   	• schedule(dynamic)
   	• schedule(guided)

     For each scheduling policy:
   	• Record the thread ID responsible for processing 
   	  each number.
   	• Measure the execution time using omp_get_wtime().
   	• Observe how loop iterations are distributed among the 
   	  threads.
   	• Compare the load balancing and execution time obtained
   	  with each scheduling policy.
*/

#include <stdio.h>
#include <omp.h>

int isPrime(int n)
{
    int i;

    if(n < 2)
        return 0;

    for(i = 2; i * i <= n; i++)
    {
        if(n % i == 0)
            return 0;
    }

    return 1;
}

int main()
{
    int n, i, count = 0;
    double start, end;

    printf("Enter N: ");
    scanf("%d", &n);

    start = omp_get_wtime();
    
    #pragma omp parallel for schedule(dynamic) reduction(+:count)
    for(i = 1; i <= n; i++)
    {
        if(isPrime(i))
        {
            count++;
            printf("Number %d -> Thread %d\n", i, omp_get_thread_num());
        }
    }
    /*
    #pragma omp parallel for schedule(dynamic) reduction(+:count)
    for(i = 1; i <= n; i++)
    {
        if(isPrime(i))
        {
            count++;
            printf("Number %d -> Thread %d\n", i, omp_get_thread_num());
        }
    }
    
    #pragma omp parallel for schedule(guided) reduction(+:count)
    for(i = 1; i <= n; i++)
    {
        if(isPrime(i))
        {
            count++;
            printf("Number %d -> Thread %d\n", i, omp_get_thread_num());
        }
    }*/
    end = omp_get_wtime();

    printf("\nNumber of prime numbers = %d\n", count);
    printf("Execution time = %f seconds\n", end - start);

    return 0;
}

/*ouput: 

STATIC
Enter N: 20
Number 2 -> Thread 18
Number 5 -> Thread 19
Number 19 -> Thread 14
Number 7 -> Thread 6
Number 11 -> Thread 12
Number 13 -> Thread 5
Number 17 -> Thread 18
Number 3 -> Thread 17

Number of prime numbers = 8
Execution time = 0.014687 seconds



DYNAMIC
Enter N: 20
Number 2 -> Thread 3
Number 13 -> Thread 7
Number 3 -> Thread 14
Number 11 -> Thread 15
Number 5 -> Thread 6
Number 7 -> Thread 17
Number 17 -> Thread 12
Number 19 -> Thread 10

Number of prime numbers = 8
Execution time = 0.000641 seconds




GUIDED
Enter N: 20
Number 2 -> Thread 8
Number 5 -> Thread 19
Number 7 -> Thread 1
Number 3 -> Thread 18
Number 11 -> Thread 16
Number 13 -> Thread 15
Number 17 -> Thread 4
Number 19 -> Thread 13

Number of prime numbers = 8
Execution time = 0.002480 seconds



explanation:
static: Iterations are divided among threads beforehand, so workload distribution is fixed; execution took 0.014687 s.
dynamic: Threads receive new iterations as they finish their current work, giving better load balancing and the fastest time of 0.000641 s.
guided: Iterations are initially assigned in larger chunks that gradually decrease, giving a balance between static and dynamic scheduling. time 0.02480 s.
All three methods correctly identified the 8 prime numbers between 1 and 20.
For this small input, the execution times can vary significantly due to thread and scheduling overhead.
*/
