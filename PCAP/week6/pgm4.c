// 2nd September 2026
/* 4) Implement parallel odd-even transposition sort using MPI. */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, value, temp, phase;
    int a[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        printf("Enter %d values:\n", size);
        for(int i = 0; i < size; i++)
            scanf("%d", &a[i]);
    }

    MPI_Scatter(a, 1, MPI_INT, &value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for(phase = 0; phase < size; phase++){
        if(phase % 2 == 0){
            if(rank % 2 == 0 && rank + 1 < size){
                MPI_Sendrecv(&value, 1, MPI_INT, rank + 1, 0, &temp, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if(value > temp)
                    value = temp;
            }
            else if(rank % 2 == 1){
                MPI_Sendrecv(&value, 1, MPI_INT, rank - 1, 0, &temp, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if(value < temp)
                    value = temp;
            }
        }else{
            if(rank % 2 == 1 && rank + 1 < size){
                MPI_Sendrecv(&value, 1, MPI_INT, rank + 1, 0, &temp, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if(value > temp)
                    value = temp;
            }else if(rank % 2 == 0 && rank > 0){
                MPI_Sendrecv(&value, 1, MPI_INT, rank - 1, 0, &temp, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if(value < temp)
                    value = temp;
            }
        }

        MPI_Barrier(MPI_COMM_WORLD);
    }

    printf("Process %d: %d\n", rank, value);

    MPI_Finalize();
    return 0;
}

/*5CSED1@dsl-11:~/Documents/240905318_Anirvin_PCAP/week6$ mpirun -np 10 ./pgm4
Enter 10 values:
37 12 45 8 23 91 4 56 19 72 
Process 0: 4
Process 1: 8
Process 2: 12
Process 3: 19
Process 4: 23
Process 5: 37
Process 6: 45
Process 7: 56
Process 8: 72
Process 9: 91
*/
