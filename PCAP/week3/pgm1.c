//8th August 2026
/*1. Implement an OpenMP program to compute the sum of the 
     first N natural numbers in parallel. Using the same program, 
     demonstrate the effect of the following OpenMP data-sharing 
     clauses:
   	• shared
   	• private
 	• firstprivate
  	• lastprivate

     For each case:
 	 1. Execute the program.
  	 2. Observe the output produced.
  	 3. Explain the effect of the data-sharing clause on:
      		• Variable values
     		• Data accessibility among threads
     		• Correctness of the final result

Finally, compare the outputs obtained for each data-sharing 
clause and explain why they differ.*/

#include <stdio.h>
#include <omp.h>

int main()
{
    int n, i, sum = 0;

    printf("Enter N: ");
    scanf("%d", &n);
    /*
    #pragma omp parallel for shared(n, sum)
    for(i = 1; i <= n; i++)
    {
        sum += i;
    }*/
    /*
    #pragma omp parallel for private(sum)
    for(i = 1; i <= n; i++)
    {
        sum += i;
    }*/
    /*
    #pragma omp parallel for firstprivate(sum)
    for(i = 1; i <= n; i++)
    {
        sum += i;
    }*/
    /*
    #pragma omp parallel for lastprivate(sum)
    for(i = 1; i <= n; i++)
    {
        sum += i;
    }*/

    printf("Sum = %d\n", sum);

    return 0;
}

/*output
SHARED
Enter N: 20
Sum = 44

PRIVATE
Enter N: 20
Sum = 128

FIRSTPRIVATE
Enter N: 20
Sum = 123

LASTPRIVATE
Enter N: 20
Sum = 134

explanation: 
shared: All threads modify the same sum, causing a race condition and an unpredictable result.
private: Each thread has an uninitialized copy of sum, so the original sum is not properly updated.
firstprivate: Each thread gets a separate copy initialized to 0, but the copies are not combined, so the original remains 0.
lastprivate: Each thread has a separate copy, and only the value from the last iteration is copied back.
Thus, none gives 210; reduction(+:sum) should be used for the correct parallel sum.
*/
