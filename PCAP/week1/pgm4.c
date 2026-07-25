//25 July 2026

/*q4:   Implement an OpenMP program to perform 
	the addition of two one-dimensional arrays of
	size N using the parallel for directive. Display 
	the resulting array and identify the Thread
	ID that computes each array element.*/

#include <stdio.h>
#include <omp.h>

int main(){
	int n;
	printf("Enter Array length: ");
	scanf("%d",&n);
	int arr1[n], arr2[n];
	int res[n];
	int thread_responsible[n];
	
	for(int i=0;i<n;i++){
		printf("\nEnter element %d of array 1: ",i+1);
		scanf("%d",&arr1[i]);
		printf("\nEnter element %d of array 2: ",i+1);
		scanf("%d",&arr2[i]);
	}
	omp_set_num_threads(5);
	#pragma omp parallel for
	for(int i = 0; i < n; i++){
   		res[i] = arr1[i] + arr2[i];
   		thread_responsible[i] = omp_get_thread_num();
	}
	printf("\n\nResult: \n");
	for(int i=0;i<n;i++){
		printf("%d ",res[i]);
	}
	printf("\n");
	for(int i=0;i<n;i++){
		printf("Thread responsible for element %d : %d\n",i+1,thread_responsible[i]);
	}	
	return 0;
}

/*output:

Result: 
2 4 6 8 10 12 14 16 18 20 
Thread responsible for element 1 : 0
Thread responsible for element 2 : 0
Thread responsible for element 3 : 1
Thread responsible for element 4 : 1
Thread responsible for element 5 : 2
Thread responsible for element 6 : 2
Thread responsible for element 7 : 3
Thread responsible for element 8 : 3
Thread responsible for element 9 : 4
Thread responsible for element 10 : 4
*/
