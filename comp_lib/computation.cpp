#include "computation.h"

void gemv(const float *A, const int M, const int N, const float *x, float *y)
{
    for (int row = 0; row < M; row++)
    {
        float result = 0.0f;
        for (int col = 0; col < N; col++)
        {
            result += A[col + row * N] * x[col];
        }
        y[row] = result;
    }
    // over
    return;
}