//22nd August 2026
/*6. Implement an MPI program to read an integer value in the
  root process. Root process sends this value to Process1, Process1
  sends this value to Process2 and so on. Last process sends the
  value back to root process. When sending the value each process
  will first increment the received value by one. Implement the
  program using point to point communication routines.
  */
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
    int rank, size;
    int value;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        printf("Enter an integer: ");
        scanf("%d", &value);

        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Final value at root: %d\n", value);
    }else{
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        value++;

        if (rank == size - 1){
            MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }else{
            MPI_Send(&value, 1, MPI_INT, rank + 1, 0,MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}
/*output:
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week4$ mpicc pgm6.c -o pgm6 -lm
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week4$ mpirun -np 5 ./pgm6
Enter an integer: 15
Final value at root: 19
*/

/*explanation: 
The processes form a communication chain. Each process 
receives the value from the previous rank, increments it, 
and sends it to the next rank. The last process sends the 
final value back to Process 0 using point-to-point 
communication.

If the input is 10:

Root sends 10
Process 1 → 11
Process 2 → 12
Process 3 → 13
Process 4 → 14
Root receives 14
*/
