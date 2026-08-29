//29th August 2026
/*1. Implement a MPI program to read N values in the root process. 
 Root process sends one value to each process. Every process receives
 it and finds the factorial of that number and returns it to the
 root process. Root process gathers the factorial and finds sum of 
 It. Use N number of processes.*/
 
 #include <stdio.h>
 #include <mpi.h>
 
 long long factorial(int n){
 	if(n<=1)
 		return 1;
 	else
 		return n*factorial(n-1);
 }
 
 
int main(int argc, char *argv[]){
    int rank, size;
    int N;
    int value;
    long long fact;
    long long sum = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    N = size;

    int A[N];
    long long B[N];

    if (rank == 0){
        printf("Enter %d values:\n", N);

        for (int i = 0; i < N; i++)
            scanf("%d", &A[i]);
    }

    MPI_Scatter(
        A, 1, MPI_INT,
        &value, 1, MPI_INT,
        0, MPI_COMM_WORLD
    );

    fact = factorial(value);

    MPI_Gather(
        &fact, 1, MPI_LONG_LONG,
        B, 1, MPI_LONG_LONG,
        0, MPI_COMM_WORLD
    );

    if (rank == 0){
        for (int i = 0; i < N; i++)
            sum += B[i];

        printf("Factorials:\n");

        for (int i = 0; i < N; i++)
            printf("%lld ", B[i]);

        printf("\nSum of factorials = %lld\n", sum);
    }

    MPI_Finalize();

    return 0;
}

/*
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week5$ mpirun -np 4 ./pgm1
Enter 4 values:
1
2
3
4
Factorials:
1 2 6 24 
Sum of factorials = 33
*/
