//29th August
/*3. Implement a MPI program to read a string. Using N 
processes (string length is evenly divisible by N), find the 
number of non-vowels in the string. In the root process 
print number of non-vowels found by each process and print 
the total number of non-vowels.*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size, len, chunk;
    char str[1000], local[1000];
    int count = 0, counts[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        printf("Enter string: ");
        scanf("%s", str);
        len = strlen(str);
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    chunk = len / size;
    MPI_Scatter(str, chunk, MPI_CHAR,
                local, chunk, MPI_CHAR,
                0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk; i++){
        if (local[i] != 'a' && local[i] != 'e' &&
            local[i] != 'i' && local[i] != 'o' &&
            local[i] != 'u')
            count++;
    }
    MPI_Gather(&count, 1, MPI_INT,
               counts, 1, MPI_INT,
               0, MPI_COMM_WORLD);

    if (rank == 0){
        int total = 0;
        for (int i = 0; i < size; i++){
            printf("Process %d: %d non-vowels\n", i, counts[i]);
            total += counts[i];
        }

        printf("Total non-vowels = %d\n", total);
    }

    MPI_Finalize();
    return 0;
}
/*5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week5$ mpirun -np 5 ./pgm3
Enter string: Anirvin
Process 0: 1 non-vowels
Process 1: 1 non-vowels
Process 2: 0 non-vowels
Process 3: 1 non-vowels
Process 4: 1 non-vowels
Total non-vowels = 4
*/
