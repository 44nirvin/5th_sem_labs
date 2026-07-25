//25 July 2026
/*q5:   Implement an OpenMP program to perform 
	the addition of two matrices of size M×N using
	the parallel for directive. Display the resultant 
	matrix and indicate the Thread ID
	responsible for computing each row 
	(or element) of the result.*/
	
#include <stdio.h>
#include <omp.h>

int main(){
	int m,n;
	printf("Enter ROWS and COLUMNS: ");
	scanf("%d %d",&m,&n);
	
	int arr1[m][n], arr2[m][n], res[m][n], thread_responsible[m][n];
	
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			printf("\nEnter element %d,%d of array 1: ",i+1,j+1);
			scanf("%d",&arr1[i][j]);
			printf("\nEnter element %d,%d of array 2: ",i+1,j+1);
			scanf("%d",&arr2[i][j]);
		}
	}
	
	#pragma omp parallel for
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			res[i][j]=arr1[i][j]+arr2[i][j];
			thread_responsible[i][j]=omp_get_thread_num();
		}
	}
	printf("\n\nResult:\n");
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			printf("%d ",res[i][j]);
		}
		printf("\n");
	}
	printf("\n\nThreads responsible: \n");
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			printf("thread %d\t",thread_responsible[i][j]);
		}
		printf("\n");
	}
}
	
	
	
	
