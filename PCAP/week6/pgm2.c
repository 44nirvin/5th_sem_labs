//2nd September 2026
/*2) Implement an MPI program to read a 3 X 3 matrix. Enter an element 
to be searched in the root process. Find the number of occurrences of this 
element in the matrix using three processes.*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int a[3][3], row[3], element;
    int count = 0, total;
    int i, j;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0){
        printf("Enter 3 X 3 matrix:\n");
        for(i = 0; i < 3; i++)
            for(j = 0; j < 3; j++)
                scanf("%d", &a[i][j]);
        printf("Enter element to search: ");
        scanf("%d", &element);
    }
    MPI_Bcast(&element, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(a, 3, MPI_INT,row, 3, MPI_INT, 0, MPI_COMM_WORLD);
    for(i = 0; i < 3; i++){
        if(row[i] == element)
            count++;
    }
    MPI_Reduce(&count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0)
        printf("Number of occurrences = %d\n", total);
    MPI_Finalize();
    return 0;
}

/*5CSED1@dsl-11:~/Documents/240905318_Anirvin_PCAP/week6$ mpirun -np 5 ./pgm2
Enter 3 X 3 matrix:
1
1
4
3
7
4
9
9
10
Enter element to search: 4
Number of occurrences = 2
*/

