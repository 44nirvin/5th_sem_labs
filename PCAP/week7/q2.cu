//12th September
/*2. Given two vectors of length N, implement a program in 
CUDA that launches two kernel to do the following tasks:

a) Add two vectors 
  (kernel execution configuration: Block size as N)

b) Dot product of two vectors 
  (kernel execution configuration: N threads)*/
  
#include <stdio.h>
#include <cuda_runtime.h>

#define N 8

__global__ void vAdd(float *A, float *B, float* C){
	int i= threadIdx.x;
	C[i]=A[i]+B[i];
}
__global__ void vdotprod(float *A, float *B, float* result){
	int i= threadIdx.x;
	__shared__ float partialSum[N];
	partialSum[i]=A[i]*B[i];
	__syncthreads();
	
	for(int stride=N/2;stride>0;stride/=2){
		if(i<stride)
			partialSum[i]+= partialSum[i+stride];
		__syncthreads();
	}
	if(i==0)	
		*result=partialSum[0];
}
int main(){
	float h_A[N]={1,2,3,4,5,6,7,8};
	float h_B[N]={8,7,6,5,4,3,2,1};
	float h_C[N];
	float h_dot;
	float *d_A, *d_B, *d_C, *d_result;
   	cudaMalloc((void**)&d_A, N * sizeof(float));
    	cudaMalloc((void**)&d_B, N * sizeof(float));
    	cudaMalloc((void**)&d_C, N * sizeof(float));
    	cudaMalloc((void**)&d_result, sizeof(float));	
    	cudaMemcpy(d_A, h_A, N * sizeof(float),cudaMemcpyHostToDevice);
    	cudaMemcpy(d_B, h_B, N * sizeof(float),cudaMemcpyHostToDevice);	
    	
    	vAdd<<<1,N>>>(d_A, d_B,d_C);
    	cudaMemcpy(h_C,d_C,N*sizeof(float),cudaMemcpyDeviceToHost);
    	printf("Vector Addition: ");
    	for (int i = 0; i < N; i++){
        	printf("C[%d] = %.2f\n", i, h_C[i]);
    	}
    	vdotprod<<<1, N>>>(d_A, d_B, d_result);
    	// Copy dot product back to host
    	cudaMemcpy(&h_dot, d_result, sizeof(float),cudaMemcpyDeviceToHost);
    	printf("\nDot Product = %.2f\n", h_dot);
    	cudaFree(d_A);
    	cudaFree(d_B);
    	cudaFree(d_C);
    	cudaFree(d_result);
    	return 0;
}
/*
output:

Vector Addition: C[0] = 9.00
C[1] = 9.00
C[2] = 9.00
C[3] = 9.00
C[4] = 9.00
C[5] = 9.00
C[6] = 9.00
C[7] = 9.00

Dot Product = 120.00
*/
