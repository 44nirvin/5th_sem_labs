//12th September 2026
/*3. Implement a CUDA program to compute the Euclidean distance between two
randomly initialized arrays A and B, each of length N. Keep the number of
threads per block fixed at 256 and dynamically determine the number of blocks
required to process all N elements.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>

#define N 1000
#define THREADS_PER_BLOCK 256

__global__ void euclideanDistance(float *A, float *B, float *result, int n)
{
    __shared__ float partialSum[THREADS_PER_BLOCK];
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    float value = 0.0f;
    if (i < n){
        float diff = A[i] - B[i];
        value = diff * diff;
    }
    partialSum[threadIdx.x] = value;
    __syncthreads();
    for (int stride = blockDim.x / 2; stride > 0; stride /= 2){
        if (threadIdx.x < stride){
            partialSum[threadIdx.x] +=
                partialSum[threadIdx.x + stride];
        }
        __syncthreads();
    }
    if (threadIdx.x == 0){
        atomicAdd(result, partialSum[0]);
    }
}

int main()
{
    float *h_A;
    float *h_B;
    float h_result;
    float *d_A;
    float *d_B;
    float *d_result;
    h_A = (float*)malloc(N * sizeof(float));
    h_B = (float*)malloc(N * sizeof(float));
    for (int i = 0; i < N; i++){
        h_A[i] = (float)rand() / RAND_MAX;
        h_B[i] = (float)rand() / RAND_MAX;
    }
    cudaMalloc((void**)&d_A, N * sizeof(float));
    cudaMalloc((void**)&d_B, N * sizeof(float));
    cudaMalloc((void**)&d_result, sizeof(float));
    cudaMemcpy(d_A, h_A, N * sizeof(float),cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, N * sizeof(float),cudaMemcpyHostToDevice);
    // Initialize result to zero
    cudaMemset(d_result, 0, sizeof(float));
    int blocks = (N + THREADS_PER_BLOCK - 1)/ THREADS_PER_BLOCK;
    printf("N = %d\n", N);
    printf("Threads per block = %d\n", THREADS_PER_BLOCK);
    printf("Number of blocks = %d\n", blocks);

    euclideanDistance<<<blocks, THREADS_PER_BLOCK>>>(
        d_A, d_B, d_result, N
    );

    cudaMemcpy(&h_result, d_result, sizeof(float),
               cudaMemcpyDeviceToHost);

    h_result = sqrtf(h_result);
    printf("Euclidean Distance = %f\n", h_result);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_result);
    free(h_A);
    free(h_B);
    return 0;
}

/*output: 

N = 1000
Threads per block = 256
Number of blocks = 4
Euclidean Distance = 12.630071
*/
