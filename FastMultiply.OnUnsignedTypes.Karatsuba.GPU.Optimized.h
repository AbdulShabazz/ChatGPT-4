/* 
Q:Add the following: Show how to implement karatsuba on an nvidia 3000 series gpu.

A:To implement the Karatsuba algorithm on an NVIDIA 3000 series GPU, we can use CUDA, which is NVIDIA's parallel computing platform and programming model.

Here is a CUDA implementation of the Karatsuba algorithm for uint64_t types:
 */

#include <cstdint>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

using u64 = uint64_t;

__global__ void karatsuba_kernel(const u64* x, const u64* y, const int n, const int p,
                                 u64* ac, u64* bd, u64* abcd)
{
    int tid = threadIdx.x;
    int bid = blockIdx.x;

    int idx = tid + blockDim.x * bid;

    if (idx >= n)
    {
        return;
    }

    u64 x_i = x[idx];
    u64 y_i = y[idx];

    u64 a = x_i >> (p + 1);
    u64 b = x_i & ((1 << (p + 1)) - 1);
    u64 c = y_i >> (p + 1);
    u64 d = y_i & ((1 << (p + 1)) - 1);

    u64 ac_i = 0;
    u64 bd_i = 0;
    u64 abcd_i = 0;

    if (p == 0)
    {
        ac_i = a * c;
        bd_i = b * d;
    }
    else
    {
        karatsuba_kernel<<<1, n>>>(x, y, n, p >> 1, ac, bd, abcd);

        karatsuba_kernel<<<1, n>>>(x + n, y + n, n, p >> 1, ac + n, bd + n, abcd + n);

        karatsuba_kernel<<<1, n>>>(x + n, y, n, p >> 1, ac + 2 * n, bd + 2 * n, abcd + 2 * n);

        karatsuba_kernel<<<1, n>>>(x, y + n, n, p >> 1, ac + 3 * n, bd + 3 * n, abcd + 3 * n);
    }

    __syncthreads();

    ac[idx] = ac_i;
    bd[idx] = bd_i;
    abcd[idx] = abcd_i;
}

u64 karatsuba_gpu(const u64* x, const u64* y, const int n)
{
    if (n == 1)
    {
        return x[0] * y[0];
    }

    u64* x_gpu;
    u64* y_gpu;
    cudaMalloc(&x_gpu, n * sizeof(u64));
    cudaMalloc(&y_gpu, n * sizeof(u64));
    cudaMemcpy(x_gpu, x, n * sizeof(u64), cudaMemcpyHostToDevice);
    cudaMemcpy(y_gpu, y, n * sizeof(u64), cudaMemcpyHostToDevice);

    int p = 1;
    while (p < n)
    {
        p <<= 1;
    }
    p >>= 1;

    u64* ac_gpu;
    u64* bd_gpu;
    u64* abcd_gpu;
    cudaMalloc(&ac_gpu, 4 * n * sizeof(u64));
    cudaMalloc(&bd_gpu, 4 * n * sizeof(u64));
    cudaMalloc(&abcd_gpu, 4 * n * sizeof(u64));

    cudaMemset(ac_gpu, 0, 4 * n * sizeof(u64));
    cudaMemset(bd_gpu, 0, 4 * n * sizeof(u64));
    cudaMemset(abcd_gpu, 0, 4 * n * sizeof(u64));
    
    karatsuba_kernel<<<1, n>>>(x_gpu, y_gpu, n, p, ac_gpu, bd_gpu, abcd_gpu);
    cudaDeviceSynchronize();

    u64* ac = new u64[4 * n];
    u64* bd = new u64[4 * n];
    u64* abcd = new u64[4 * n];
    cudaMemcpy(ac, ac_gpu, 4 * n * sizeof(u64), cudaMemcpyDeviceToHost);
    cudaMemcpy(bd, bd_gpu, 4 * n * sizeof(u64), cudaMemcpyDeviceToHost);
    cudaMemcpy(abcd, abcd_gpu, 4 * n * sizeof(u64), cudaMemcpyDeviceToHost);

    cudaFree(x_gpu);
    cudaFree(y_gpu);
    cudaFree(ac_gpu);
    cudaFree(bd_gpu);
    cudaFree(abcd_gpu);

    u64 result = 0;

    for (int i = 0; i < n; ++i)
    {
        result += (ac[i] << (2 * p + i * 2)) + (abcd[i] << (p + i * 2)) + bd[i];
    }

    delete[] ac;
    delete[] bd;
    delete[] abcd;

    return result;
}

/* 
Explanation:

    We first check if n is 1, in which case we simply return the product of the two input numbers.

    We allocate memory on the GPU for the input numbers x and y.

    We compute the number of bits required to represent n and use that to split the numbers into halves.

    We allocate memory on the GPU for the intermediate results ac, bd, and abcd.

    We call the karatsuba_kernel function with the input numbers and intermediate results as arguments.

    We copy the intermediate results back from the GPU to the host.

    We free the memory allocated on the GPU.

    We combine the intermediate results using the Karatsuba formula to compute the final product.

    We free the memory allocated on the host.

The karatsuba_kernel function is a CUDA kernel that performs the Karatsuba algorithm recursively on the GPU. The kernel is launched with a single thread block containing n threads.

The __global__ keyword specifies that the function is a kernel that can be called from the host and executed on the GPU.

The tid and bid variables compute the thread and block indices.

The idx variable computes the global index of the thread.

The kernel first computes the halves a, b, c, and d for the input numbers at the current index.

If p is 0, the kernel computes the products of the corresponding halves and stores them in ac_i and bd_i, respectively. Otherwise, the kernel launches four recursive calls to itself with the appropriate arguments.

The __syncthreads() function is called to ensure that all threads have finished executing before the intermediate results are written back to global memory.

The final product is computed by combining the intermediate results using the Karatsuba formula in the host code.

This implementation of the Karatsuba algorithm on an NVIDIA 3000 series GPU should provide significant speedups over the CPU-based implementation for large input sizes. 
*/