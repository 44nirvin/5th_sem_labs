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

int ones(int n) {
    return n ^ 15;
}
void printBinary(int n) {
    int started = 0;

    for(int i = 3; i >= 0; i--) {
        if((n >> i) & 1)
            started = 1;

        if(started)
            printf("%d", (n >> i) & 1);
    }

    if(!started)
        printf("0");
}
int main(){
	int m,n;
	int i,j;
	printf("Enter number of rows and columns: ");
	scanf("%d %d", &m,&n);
	int a[m][n],b[m][n],d[m][n];
	printf("Enter the elements of Matrix A :\n");
   	for(i = 0; i < m; i++) {
   	     for(j = 0; j < n; j++) {
   	         scanf("%d", &a[i][j]);
       	 	}
  	}
  	#pragma omp parallel for private(j)
	for(i = 0; i < m; i++) {
        	for(j = 0; j < n; j++) {
            		if(i == 0 || j == 0 || i == m-1 || j == n-1) {
              		  b[i][j] = a[i][j];
               		  d[i][j] = a[i][j];
           	 	}
            		else {
                		b[i][j] = ones(a[i][j]);
                		d[i][j] = b[i][j];
            		}
        	}
    	}
printf("\nMatrix B:\n");
for(i = 0; i < m; i++) {
    for(j = 0; j < n; j++) {
        if(i == 0 || j == 0 || i == m-1 || j == n-1)
            printf("%d ", b[i][j]);
        else {
            printBinary(b[i][j]);
            printf(" ");
        }
    }
    printf("\n");
}
    	
    printf("\nMatrix D:\n");
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }

    return 0;
  	
  		
}


