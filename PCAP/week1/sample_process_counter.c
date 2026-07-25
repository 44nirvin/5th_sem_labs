//omp_get_thread_num(); gets the thread number.

#include <stdio.h>
#include <omp.h>

int main(){
	#pragma omp parallel
	{
		int id;
		id=omp_get_thread_num();	
		printf("Thread %d\n",id);
	}
	return 0;
}
