//25th July 2026

/*q1:   Implement an OpenMP program to determine 
	and display the total number of threads
	participating in a parallel region using 
	the omp_get_num_threads() runtime function.*/
	
#include <stdio.h>
#include <omp.h>

int main(){
	#pragma omp parallel
	{
		if(omp_get_thread_num()==0){//otherwise it prints ts on all threads lol
			int num= omp_get_num_threads();
			printf("Total threads: %d\n",num);
		}
	}
	return 0;
}
