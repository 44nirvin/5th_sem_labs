//22nd August 2026
/*Implement a program in MPI where even process
 prints factorial of the rank and odd ranked process
 prints ranks Fibonacci number.*/
 
 #include <stdio.h>
 #include "mpi.h"
 
 int fibo(int i){
 	if(i<=1)
 		return i;
 	else
 		return fibo(i-1)+fibo(i-2);
 } 
 int fact(int i){
 	if(i<=1)
 		return 1;
 	else
 		return i*fact(i-1);
 }
 int main(int argc, char *argv[]){
 	int rank, size;
 	MPI_Init(&argc, &argv);
 	
 	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 	MPI_Comm_size(MPI_COMM_WORLD, &size);
 	
 	if(rank%2==0)
 		printf("Factorial of Process %d: %d\n",rank,fact(rank));
 	else
 		printf("Fibonacci value of Process %d: %d\n", rank, fibo(rank));
 	
 	MPI_Finalize();
 	return 0;
 }
 
 /*output: 
 5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week4$ mpicc pgm3.c -o pgm3 -lm
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week4$ mpirun -np 8 ./pgm3
Fibonacci value of Process 3: 2
Fibonacci value of Process 1: 1
Factorial of Process 2: 2
Factorial of Process 4: 24
Fibonacci value of Process 5: 5
Fibonacci value of Process 7: 13
Factorial of Process 0: 1
Factorial of Process 6: 720
*/

/*explanation: 
Even-ranked processes calculate factorial, while odd-ranked processes calculate Fibonacci using their rank. No communication is required.
*/


