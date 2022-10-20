#ifndef MY_COMPUTATION_H
#define MY_COMPUTATION_H

// compute matrix vector multiplication y = A * x
// size of A = M rows x N cols
// length of x = N
// output buffer y should be allocated beforehand
void gemv(const float* A, const int M, const int N, const float* x, float* y);

#endif