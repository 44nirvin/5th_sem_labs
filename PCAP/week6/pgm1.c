// 2nd September 2026
/* 1. Implement an MPI program using N processes to find
   1! + 2! + ..... + N!. Use scan. Also, handle different errors
   using error handling routines. */

#include <stdio.h>
#include <mpi.h>

int fact(int i){
    if(i <= 0)
        return 1;
    else
        return i * fact(i - 1);
}

int main(int argc, char* argv[]){
    int rank, size, value, sum, i;
    int error;
    char error_string[MPI_MAX_ERROR_STRING];
    int length;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    value = fact(rank + 1);
    
    /*
    // ERROR TEST: invalid rank
    error = MPI_Send(&value, 1, MPI_INT, size, 0, MPI_COMM_WORLD);

    if(error != MPI_SUCCESS){
        MPI_Error_string(error, error_string, &length);
        printf("Process %d: %s\n", rank, error_string);
    }
*/
    
    error = MPI_Scan(&value, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if(error != MPI_SUCCESS){
        MPI_Error_string(error, error_string, &length);
        printf("Process %d: %s\n", rank, error_string);
    }else{
        printf("Process %d: factorial = %d, sum = %d\n",
               rank, value, sum);
    }

    MPI_Finalize();
    return 0;
}

/*
5CSED1@dsl-11:~/Documents/240905318_Anirvin_PCAP/week6$ mpicc pgm1.c -o pgm1
5CSED1@dsl-11:~/Documents/240905318_Anirvin_PCAP/week6$ mpirun -np 6 ./pgm1
Process 1: factorial = 2, sum = 3
Process 2: factorial = 6, sum = 9
Process 3: factorial = 24, sum = 33
Process 4: factorial = 120, sum = 153
Process 0: factorial = 1, sum = 1
Process 5: factorial = 720, sum = 873

after changes.

5CSED1@dsl-11:~/Documents/240905318_Anirvin_PCAP/week6$ mpicc pgm1.c -o pgm1
5CSED1@dsl-11:~/Documents/240905318_Anirvin_PCAP/week6$ mpirun -np -1 ./pgm1
Process 0: Invalid rank, error stack:
internal_Send(120): MPI_Send(buf=0x7ffcf39a0750, count=1, MPI_INT, 1, 0, MPI_COMM_WORLD) failed
internal_Send(78).: Invalid rank has value 1 but must be nonnegative and less than 1
*/
