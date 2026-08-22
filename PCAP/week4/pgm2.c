//22nd August 2026
/*Implement a program in MPI to toggle the character 
of a given string indexed by the rank of the process.

Hint: Suppose the string is HELLO and there are 5 
processes, then process 0 toggles H to h, process 1 
toggles E to e, and so on.*/

#include <stdio.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    char str[] = "HELLO";

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank < (int)(sizeof(str) - 1))
    {
        char c = str[rank];

        if (islower(c))
            str[rank] = toupper(c);
        else if (isupper(c))
            str[rank] = tolower(c);

        printf("Process %d: %c toggled -> %c\n",
               rank, c, str[rank]);
    }

    MPI_Finalize();

    return 0;
}

/*output:
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week4$ mpicc pgm2.c -o pgm2 -lm
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week4$ mpirun -np 5 ./pgm2
Process 0: H toggled -> h
Process 1: E toggled -> e
Process 2: L toggled -> l
Process 3: L toggled -> l
Process 4: O toggled -> o
*/

/*explanation: The program initializes MPI and obtains 
the rank of each process. Each process uses its rank as 
the index to select a character from the string and toggles 
its case using toupper() or tolower(). Since MPI processes 
have separate memory, each process modifies its own copy 
of the string independently.
/*

