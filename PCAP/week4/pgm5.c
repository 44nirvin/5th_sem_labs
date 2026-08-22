//22nd August
/*5. Implement an MPI program where the master process (process 0)
 sends a number to each of the slaves and the slave processes receive
 the number and print it. Use standard send.*/
 
 #include <stdio.h>
 #include <mpi.h>
 
 int main(int argc, char* argv[]){
 	int rank, size;
 	int num;
 	MPI_Init(&argc, &argv);
 	
 	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 	MPI_Comm_size(MPI_COMM_WORLD,&size);
 	
 	if(rank==0){
		printf("Enter a Number: ");
		scanf("%d",&num);
		for(int i=1;i<size;i++)
			MPI_Send(&num,1,MPI_INT,i,0,MPI_COMM_WORLD);
	}else{
		MPI_Recv(&num,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Process %d received: %d\n",rank,num);
	}
	
	MPI_Finalize();
	return 0;
}
/*output:
5CSED1@dsl-11:~/Documents/240905318_Anivin_PCAP/week4$ mpirun -np 5 ./pgm5
Enter a Number: 10
Process 1 received: 10
Process 2 received: 10
Process 3 received: 10
Process 4 received: 10
*/

/*explanation:
Process 0 reads a number and uses MPI_Send() to send it to every slave process. Each slave uses MPI_Recv() to receive and print the number. This uses standard blocking send as specified in the manual.
*/
