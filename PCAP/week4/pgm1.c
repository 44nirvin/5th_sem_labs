//22nd August 2026
/*Implement a simple MPI program to find pow(x, rank)
 for all the processes where x is the integer constant 
 and rank is the rank of the process.*/
 
 #include "mpi.h"
 #include <stdio.h>
 #include <math.h>
 
 int main(int argc, char *argv[]){
 	int rank,size;
 	int x=2;
 	double result;
 	
 	MPI_Init(&argc, &argv);
 	
 	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 	MPI_Comm_size(MPI_COMM_WORLD, &size);
 	
 	result=pow(x,rank);
 	
 	printf("Process %d: pow(%d, %d) = %.0f\n", rank, x, rank, result);
 	
 	MPI_Finalize();
 	return 0;
 }
 
 /*5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week4$ mpicc pgm1.c -o pgm1 -lm
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week4$ mpirun -np 5 ./pgm1
Process 1: pow(2, 1) = 2
Process 2: pow(2, 2) = 4
Process 3: pow(2, 3) = 8
Process 4: pow(2, 4) = 16
Process 0: pow(2, 0) = 1
*/

/*explanation: 
The program initializes the MPI environment and obtains the
rank and total number of processes using MPI_Comm_rank() and MPI_Comm_size(). 
Each process independently calculates x^rank, where x = 2, using the pow() 
function. Since every process has a different rank, each produces a 
different result.
*/
