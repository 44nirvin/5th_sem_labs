// 2nd September 2026
/* 3) Implement an MPI program to read 4 X 4 matrix and display
   the required output using four processes.
  	I/p matrix:     
	    	1  2  3  4
                1  2  3  1
                1  1  1  1
                2  1  2  1

	O/p matrix:     
                1  2  3  4
                2  4  6  5
                3  5  7  6
                5  6  9  7*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    int a[4][4], row[4], result[4];
    int i, j;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0){
        printf("Enter 4 X 4 matrix:\n");
        for(i = 0; i < 4; i++)
            for(j = 0; j < 4; j++)
                scanf("%d", &a[i][j]);
    }
    MPI_Scatter(a, 4, MPI_INT,row, 4, MPI_INT,0, MPI_COMM_WORLD);
    MPI_Scan(row, result, 4, MPI_INT,MPI_SUM, MPI_COMM_WORLD);
    printf("Process %d: ", rank);
    
    for(i = 0; i < 4; i++)
        printf("%d ", result[i]);
        
    printf("\n");
    MPI_Finalize();
    return 0;
}

/*5CSED1@dsl-11:~/Documents/240905318_Anirvin_PCAP/week6$ mpicc pgm3.c -o pgm3
5CSED1@dsl-11:~/Documents/240905318_Anirvin_PCAP/week6$ mpirun -np 4 ./pgm3
Enter 4 X 4 matrix:
1
2
3
4
1
2
3
1
1
1
1
1
2
1
2
1
Process 0: 1 2 3 4 
Process 1: 2 4 6 5 
Process 2: 3 5 7 6 
Process 3: 5 6 9 7
*/
