//29th August 2026
/*Implement a MPI program to read an integer value M
 and NXM elements into an ID array in the root process,
 where N is the number of processes. Root process sends M 
 elements to each process. Each process finds average of 
 M elements it received and sends these average values to 
 root. Root collects all the values and finds the total average. 
 Use collective communication routines.*/
 
 #include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size, M;
    int A[1000], local[100];
    float avg, averages[100], total = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        printf("Enter M: ");
        scanf("%d", &M);

        printf("Enter %d elements:\n", M * size);
        for (int i = 0; i < M * size; i++)
            scanf("%d", &A[i]);
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(A, M, MPI_INT,
                local, M, MPI_INT,
                0, MPI_COMM_WORLD);

    avg = 0;

    for (int i = 0; i < M; i++)
        avg += local[i];

    avg /= M;

    MPI_Gather(&avg, 1, MPI_FLOAT,averages, 1, MPI_FLOAT,0, MPI_COMM_WORLD);

    if (rank == 0){
        for (int i = 0; i < size; i++)
            total += averages[i];
        total /= size;
        printf("Total average = %.2f\n", total);
    }

    MPI_Finalize();
    return 0;
}
/*
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week5$ mpicc pgm2.c -o pgm2
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week5$ mpirun -np 5 ./pgm2
Enter M: 4
Enter 20 elements:
1
2
3
4
5
6
7
8
9
0
11
1
2
15
199
10
112
187
156
100
Total average = 41.90
*/
