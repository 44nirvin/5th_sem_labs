//29th August 2026
/*Implement a MPI program to read two strings S1 and S2 
of same length in the root process. Using N processes including 
the root (string length is evenly divisible by N), produce the 
resultant string as shown below. Use collective communication 
routines. Display the resultant string in the root process.

Example:
String S1: string
String S2: length
Resultant String: slternitgth*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size, len, chunk;
    char S1[1000], S2[1000];
    char A[1000], B[1000], local[2000], result[2000];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        printf("Enter S1: ");
        scanf("%s", S1);

        printf("Enter S2: ");
        scanf("%s", S2);

        len = strlen(S1);
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    chunk = len / size;
    MPI_Scatter(S1, chunk, MPI_CHAR,
                A, chunk, MPI_CHAR,
                0, MPI_COMM_WORLD);
    MPI_Scatter(S2, chunk, MPI_CHAR,
                B, chunk, MPI_CHAR,
                0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk; i++){
        local[2 * i] = A[i];
        local[2 * i + 1] = B[i];
    }

    MPI_Gather(local, 2 * chunk, MPI_CHAR,
               result, 2 * chunk, MPI_CHAR,
               0, MPI_COMM_WORLD);

    if (rank == 0){
        result[2 * len] = '\0';
        printf("Resultant String: %s\n", result);
    }
    MPI_Finalize();
    return 0;
}
/*
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week5$ mpicc pgm4.c -o pgm4
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week5$ mpirun -np 5 ./pgm4
Enter S1: Hello
Enter S2: Goodbye
Resultant String: HGeololdob
*/
