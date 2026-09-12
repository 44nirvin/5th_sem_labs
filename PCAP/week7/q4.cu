//12th September 2026
/*4. Implement a program in CUDA to process a 1D array containing angles in radians
to generate sine of the angle in the output array. Use appropriate function.*/
#include <stdio.h>
#include <cuda_runtime.h>
#include <math.h>

#define N 8

__global__ void calculateSine(float *angles, float *output){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N){
        output[i] = sinf(angles[i]);
    }
}

int main(){
    float h_angles[N] ={
        0.0f,
        0.523599f,
        0.785398f,
        1.047198f,
        1.570796f,
        3.141593f,
        4.712389f,
        6.283185f
    };
    float h_output[N];
    float *d_angles;
    float *d_output;

    cudaMalloc((void**)&d_angles, N * sizeof(float));
    cudaMalloc((void**)&d_output, N * sizeof(float));
    cudaMemcpy(d_angles, h_angles, N * sizeof(float),cudaMemcpyHostToDevice);
               
    calculateSine<<<1, N>>>(d_angles, d_output);
    cudaMemcpy(h_output, d_output, N * sizeof(float),cudaMemcpyDeviceToHost);
    printf("Angle (radians)    sin(angle)\n");
    for (int i = 0; i < N; i++){
        printf("%f          %f\n",h_angles[i], h_output[i]);
    }
    cudaFree(d_angles);
    cudaFree(d_output);
    return 0;
}

/* output: 

Angle (radians)    sin(angle)
0.000000          0.000000
0.523599          0.500000
0.785398          0.707107
1.047198          0.866026
1.570796          1.000000
3.141593          -0.000000
4.712389          -1.000000
6.283185          -0.000000
*/
