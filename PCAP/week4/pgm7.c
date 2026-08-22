//22nd August 2026
/*7. Implement an MPI program to read N elements of the 
array in the root process (process 0) where N is equal 
to the total number of processes. The root process sends 
one value to each of the slaves. Let even ranked process 
finds square of the received element and odd ranked process 
inds cube of received element. Use Buffered send.*/

#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int *buffer;
    int value;
    int arr[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        int buffer_size = size * (sizeof(int) + MPI_BSEND_OVERHEAD);

        buffer = malloc(buffer_size);
        MPI_Buffer_attach(buffer, buffer_size);
        printf("Enter %d elements:\n", size);

        for (int i = 0; i < size; i++)
            scanf("%d", &arr[i]);
        
        if (rank % 2 == 0)
            printf("Process 0: %d -> %d\n",arr[0], arr[0] * arr[0]);

        for (int i = 1; i < size; i++)
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        
        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);
    }else{
        MPI_Recv(&value, 1, MPI_INT, 0, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (rank % 2 == 0){
            printf("Process %d: %d -> %d\n",
                   rank, value, value * value);
        }else{
            printf("Process %d: %d -> %d\n",
                   rank, value, value * value * value);
        }
    }

    MPI_Finalize();
    return 0;
}

/*output:
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week4$ mpirun -np 5 ./pgm7
Enter 5 elements:
5
6
7
8
9
Process 0: 5 -> 25
Process 1: 6 -> 216
Process 2: 7 -> 49
Process 3: 8 -> 512
Process 4: 9 -> 81
*/

/*explanation:
 Process 0 reads N elements and attaches a user-provided
 buffer for buffered communication. It uses MPI_Bsend() to
 send one element to each slave. Even-ranked slaves calculate
 the square of their received value, while odd-ranked slaves
 calculate its cube.*/
