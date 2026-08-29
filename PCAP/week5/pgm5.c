//29th August
/**/
#include <mpi.h>
#include <stdio.h>

void selectionSort(int A[], int n){
    for (int i = 0; i < n - 1; i++){
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (A[j] < A[min])
                min = j;

        int temp = A[i];
        A[i] = A[min];
        A[min] = temp;
    }
}

void merge(int A[], int l, int m, int r){
    int temp[1000];
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r){
        if (A[i] < A[j])
            temp[k++] = A[i++];
        else
            temp[k++] = A[j++];
    }
    while (i <= m)
        temp[k++] = A[i++];

    while (j <= r)
        temp[k++] = A[j++];

    for (i = l; i <= r; i++)
        A[i] = temp[i];
}

int main(int argc, char *argv[]){
    int rank, size;
    int A[1000], local[1000];
    int n, chunk;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        printf("Enter number of elements: ");
        scanf("%d", &n);

        printf("Enter elements:\n");
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    chunk = n / size;
    MPI_Scatter(A, chunk, MPI_INT,
                local, chunk, MPI_INT,
                0, MPI_COMM_WORLD);

    selectionSort(local, chunk);

    MPI_Gather(local, chunk, MPI_INT,
               A, chunk, MPI_INT,
               0, MPI_COMM_WORLD);

    if (rank == 0){
        for (int step = chunk; step < n; step *= 2){
            for (int i = 0; i < n; i += 2 * step){
                int mid = i + step - 1;
                int end = i + 2 * step - 1;
                if (mid < n)
                {
                    if (end >= n)
                        end = n - 1;

                    merge(A, i, mid, end);
                }
            }
        }

        printf("Sorted array:\n");

        for (int i = 0; i < n; i++)
            printf("%d ", A[i]);

        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
/*
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week5$ mpirun -np 5 ./pgm5
Enter number of elements: 10
Enter elements:
6
11
901
43
101
455
16
299
150
151
Sorted array:
6 11 16 43 101 150 151 299 455 901 

*/
