//22nd August 2026
/*Implement an MPI program using synchronous send. The sender 
process sends a word to the receiver. The second process receives 
the word, toggles each letter of the word and sends it back to 
the first process. Both processes use synchronous send operations.*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank;
    char word[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        strcpy(word, "HELLO");

        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent: %s\n", word);

        MPI_Recv(word, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received: %s\n", word);
    }
    else if (rank == 1)
    {
        MPI_Recv(word, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received: %s\n", word);

        for (int i = 0; word[i] != '\0'; i++)
        {
            if (isupper(word[i]))
                word[i] = tolower(word[i]);
            else if (islower(word[i]))
                word[i] = toupper(word[i]);
        }

        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
/*output:
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week4$ mpicc pgm4.c -o pgm4 -lm
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week4$ mpirun -np 5 ./pgm4
Process 0 sent: HELLO
Process 1 received: HELLO
Process 0 received: hello
*/

/*explanation: 
The program uses MPI_Ssend() to synchronously send the word from Process 0 to Process 1. Process 1 receives the word, toggles the case of each character using toupper()/tolower(), and sends the modified word back to Process 0.
*/

