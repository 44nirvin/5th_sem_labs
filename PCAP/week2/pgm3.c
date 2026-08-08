//1st August 2026

/*q3: Implement an OpenMP program that reads a matrix
      of size MxN and produces
      - Matrix B where non border elements become replaced by their 1's complement 
      - Matrix D where the said 1's compliment is converted back to decimal*/
      
/*1  2  3  4    	1  2  3   4  
  6  5  8  3      to    6  10 111 3   to
  2  4  10 1		2  11 101 1
  9  1  2  5 		9  1  2   5
  
  1  2  3  4 
  6  2  7  3
  2  3  5  1
  9  1  2  5 */
  
#include <stdio.h>
#include <omp.h>

int main()
{
    int m, n;

    printf("Enter number of rows and columns: ");
    scanf("%d%d", &m, &n);

    int A[m][n], B[m][n], D[m][n];

    printf("Enter matrix elements:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < m; i++)
    {
        int tid = omp_get_thread_num();

        for (int j = 0; j < n; j++)
        {
            if (i == 0 || i == m - 1 || j == 0 || j == n - 1)
            {
                B[i][j] = A[i][j];
                D[i][j] = A[i][j];
            }
            else
            {
                int num = A[i][j];
                int temp = num;
                int bits = 0;

                while (temp > 0)
                {
                    bits++;
                    temp /= 2;
                }

                if (bits == 0)
                    bits = 1;

                int binary = 0;
                int place = 1;

                for (int b = 0; b < bits; b++)
                {
                    if ((num >> b) & 1)
                        binary += 0 * place;
                    else
                        binary += 1 * place;

                    place *= 10;
                }

                B[i][j] = binary;

                int mask = (1 << bits) - 1;
                D[i][j] = (~num) & mask;
            }
        }

        printf("Row %d processed by Thread %d\n", i, tid);
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%6d", B[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix D:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%6d", D[i][j]);
        }
        printf("\n");
    }

    return 0;
}
