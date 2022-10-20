#include "computation.h"
// use AVX2
#include <immintrin.h>

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

void gemv_AVX2_v1(const float *A, const int M, const int N, const float *x, float *y)
{
    // AVX2: 256bit = 8 * 32bit
    const int LANES = 8;
    // process matrix A row by row
    // each time compute the multiplication of one row of A with vector x, and store into y
    // use AVX2 to load and multiply multiple elements at the same time
    for (int row = 0; row < M; row++)
    {
        __m256 vec_Arow, vec_x;
        __m256 vec_result = _mm256_setzero_ps();

        float result = 0.0f;
        int col_beg = 0;
        while(col_beg + LANES <= N)
        {
            // load A(row, col_beg:col_beg + LANES-1) into AVX2 register
            vec_Arow = _mm256_load_ps(A + col_beg + row * N);
            // load x(col_beg:col_beg + LANES-1) into AVX2 register
            vec_x = _mm256_load_ps(x + col_beg);
            // elementwise multiply
            vec_Arow = _mm256_mul_ps(vec_Arow, vec_x);
            // accumulate
            vec_result = _mm256_add_ps(vec_result, vec_Arow);
            // update col_beg
            col_beg += LANES;
        }
        // reduce and accumulate to result
        vec_result = _mm256_hadd_ps(vec_result, vec_result);    // 8 -> 4
        vec_result = _mm256_hadd_ps(vec_result, vec_result);    // 4 -> 2
        result += vec_result[0] + vec_result[4];                // 2 -> 1
        // treat the tail
        while(col_beg < N)
        {
            result += A[col_beg + row * N] * x[col_beg];
            col_beg++;
        }
        // store the result
        y[row] = result;
    }
    // over
    return;
}