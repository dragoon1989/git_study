#include <iostream>
#include <fstream>

#include "computation.h"
#include "utility.h"

const int M = 64;
const int N = 64;

int main(int argc, char *argv[])
{
    float *pfA = reinterpret_cast<float *>(align_malloc(sizeof(float) * M * N));
    float *pfx = reinterpret_cast<float *>(align_malloc(sizeof(float) * N));
    float *pfy = reinterpret_cast<float *>(align_malloc(sizeof(float) * M));

    for (int row = 0; row < M; row++)
    {
        for (int col = 0; col < N; col++)
        {
            pfA[col + row * N] = static_cast<float>(col);
        }
        pfx[row] = static_cast<float>(row);
    }

    gemv_AVX2_v1(pfA, M, N, pfx, pfy);

    // output to disk
    std::ofstream outs("D:/workspace/files/output.dat", std::ios::binary);
    outs.write((char *)pfy, sizeof(float) * M);
    outs.close();
    // release memory
    free_mem(pfA);
    free_mem(pfx);
    free_mem(pfy);
    // over
    std::cout << "test complete!" << std::endl;
    return 0;
}