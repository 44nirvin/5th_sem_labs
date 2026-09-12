//12 september
/*1. Implement CUDA program to determine the number of CUDA
capable devices in the system. For each device, examine the 
following device’s properties:

a. Device name
b. Number of Streaming Multiprocessors
c. Maximum number of threads per block
d. Maximum thread dimensions (x,y,z)
e. Maximum grid dimensions (x,y,z)
f. The device clock frequency*/
#include <stdio.h>
#include <cuda_runtime.h>

int main()
{
    int dev_count;

    // Find number of CUDA-capable devices
    cudaGetDeviceCount(&dev_count);
    printf("Number of CUDA-capable devices: %d\n\n", dev_count);
    // Examine each device
    for (int i = 0; i < dev_count; i++)
    {
        cudaDeviceProp dev_prop;
        cudaGetDeviceProperties(&dev_prop, i);
        printf("Device %d\n", i);
        printf("-----------------------------\n");
        printf("Device Name: %s\n", dev_prop.name);
        printf("Number of Streaming Multiprocessors: %d\n",dev_prop.multiProcessorCount);
        printf("Maximum Threads per Block: %d\n",dev_prop.maxThreadsPerBlock);
        printf("Maximum Thread Dimensions: (%d, %d, %d)\n",
               dev_prop.maxThreadsDim[0],
               dev_prop.maxThreadsDim[1],
               dev_prop.maxThreadsDim[2]);
        printf("Maximum Grid Dimensions: (%d, %d, %d)\n",
               dev_prop.maxGridSize[0],
               dev_prop.maxGridSize[1],
               dev_prop.maxGridSize[2]);
        printf("Device Clock Frequency: %d MHz\n",dev_prop.clockRate / 1000);
        printf("\n");
    }

    return 0;
}


//output
/*
Number of CUDA-capable devices: 1

Device 0
-----------------------------
Device Name: NVIDIA GeForce GT 1030
Number of Streaming Multiprocessors: 3
Maximum Threads per Block: 1024
Maximum Thread Dimensions: (1024, 1024, 64)
Maximum Grid Dimensions: (2147483647, 65535, 65535)
Device Clock Frequency: 1468 MHz
*/
