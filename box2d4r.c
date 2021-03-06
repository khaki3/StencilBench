#define BENCH_DIM 2
#define BENCH_FPP 161
#define BENCH_RAD 4

#include "common.h"

double kernel_stencil(SB_TYPE *A1, int compsize, int timestep, bool scop)
{
  double start_time = sb_time(), end_time = 0.0;
  int dimsize = compsize + BENCH_RAD * 2;
  SB_TYPE (*A)[dimsize][dimsize] = (SB_TYPE (*)[dimsize][dimsize])A1;

  if (scop) {
#pragma scop
    for (int t = 0; t < timestep; t++)
      for (int i = BENCH_RAD; i < dimsize - BENCH_RAD; i++)
        for (int j = BENCH_RAD; j < dimsize - BENCH_RAD; j++)
          A[(t+1)%2][i][j] =
            0.00930f * A[t%2][i-4][j-4] +
            0.00931f * A[t%2][i-4][j-3] +
            0.00932f * A[t%2][i-4][j-2] +
            0.00933f * A[t%2][i-4][j-1] +
            0.00934f * A[t%2][i-4][j] +
            0.00935f * A[t%2][i-4][j+1] +
            0.00936f * A[t%2][i-4][j+2] +
            0.00937f * A[t%2][i-4][j+3] +
            0.00938f * A[t%2][i-4][j+4] +

            0.00939f * A[t%2][i-3][j-4] +
            0.00940f * A[t%2][i-3][j-3] +
            0.00941f * A[t%2][i-3][j-2] +
            0.00942f * A[t%2][i-3][j-1] +
            0.00943f * A[t%2][i-3][j] +
            0.00944f * A[t%2][i-3][j+1] +
            0.00945f * A[t%2][i-3][j+2] +
            0.00946f * A[t%2][i-3][j+3] +
            0.00947f * A[t%2][i-3][j+4] +

            0.00948f * A[t%2][i-2][j-4] +
            0.00949f * A[t%2][i-2][j-3] +
            0.00950f * A[t%2][i-2][j-2] +
            0.00951f * A[t%2][i-2][j-1] +
            0.00952f * A[t%2][i-2][j] +
            0.00953f * A[t%2][i-2][j+1] +
            0.00954f * A[t%2][i-2][j+2] +
            0.00955f * A[t%2][i-2][j+3] +
            0.00956f * A[t%2][i-2][j+4] +

            0.00957f * A[t%2][i-1][j-4] +
            0.00958f * A[t%2][i-1][j-3] +
            0.00959f * A[t%2][i-1][j-2] +
            0.00960f * A[t%2][i-1][j-1] +
            0.00961f * A[t%2][i-1][j] +
            0.00962f * A[t%2][i-1][j+1] +
            0.00963f * A[t%2][i-1][j+2] +
            0.00964f * A[t%2][i-1][j+3] +
            0.00965f * A[t%2][i-1][j+4] +

            0.00966f * A[t%2][i][j-4] +
            0.00967f * A[t%2][i][j-3] +
            0.00968f * A[t%2][i][j-2] +
            0.00969f * A[t%2][i][j-1] +
            0.22400f * A[t%2][i][j] +
            0.00971f * A[t%2][i][j+1] +
            0.00972f * A[t%2][i][j+2] +
            0.00973f * A[t%2][i][j+3] +
            0.00974f * A[t%2][i][j+4] +

            0.00975f * A[t%2][i+1][j-4] +
            0.00976f * A[t%2][i+1][j-3] +
            0.00977f * A[t%2][i+1][j-2] +
            0.00978f * A[t%2][i+1][j-1] +
            0.00979f * A[t%2][i+1][j] +
            0.00980f * A[t%2][i+1][j+1] +
            0.00981f * A[t%2][i+1][j+2] +
            0.00982f * A[t%2][i+1][j+3] +
            0.00983f * A[t%2][i+1][j+4] +

            0.00984f * A[t%2][i+2][j-4] +
            0.00985f * A[t%2][i+2][j-3] +
            0.00986f * A[t%2][i+2][j-2] +
            0.00987f * A[t%2][i+2][j-1] +
            0.00988f * A[t%2][i+2][j] +
            0.00989f * A[t%2][i+2][j+1] +
            0.00990f * A[t%2][i+2][j+2] +
            0.00991f * A[t%2][i+2][j+3] +
            0.00992f * A[t%2][i+2][j+4] +

            0.00993f * A[t%2][i+3][j-4] +
            0.00994f * A[t%2][i+3][j-3] +
            0.00995f * A[t%2][i+3][j-2] +
            0.00996f * A[t%2][i+3][j-1] +
            0.00997f * A[t%2][i+3][j] +
            0.00998f * A[t%2][i+3][j+1] +
            0.00999f * A[t%2][i+3][j+2] +
            0.01000f * A[t%2][i+3][j+3] +
            0.01001f * A[t%2][i+3][j+4] +

            0.01002f * A[t%2][i+4][j-4] +
            0.01003f * A[t%2][i+4][j-3] +
            0.01004f * A[t%2][i+4][j-2] +
            0.01005f * A[t%2][i+4][j-1] +
            0.01006f * A[t%2][i+4][j] +
            0.01007f * A[t%2][i+4][j+1] +
            0.01008f * A[t%2][i+4][j+2] +
            0.01009f * A[t%2][i+4][j+3] +
            0.01010f * A[t%2][i+4][j+4];
#pragma endscop
  }
  else {
    for (int t = 0; t < timestep; t++)
#pragma omp parallel for
      for (int i = BENCH_RAD; i < dimsize - BENCH_RAD; i++)
        for (int j = BENCH_RAD; j < dimsize - BENCH_RAD; j++)
          A[(t+1)%2][i][j] =
            0.00930f * A[t%2][i-4][j-4] +
            0.00931f * A[t%2][i-4][j-3] +
            0.00932f * A[t%2][i-4][j-2] +
            0.00933f * A[t%2][i-4][j-1] +
            0.00934f * A[t%2][i-4][j] +
            0.00935f * A[t%2][i-4][j+1] +
            0.00936f * A[t%2][i-4][j+2] +
            0.00937f * A[t%2][i-4][j+3] +
            0.00938f * A[t%2][i-4][j+4] +

            0.00939f * A[t%2][i-3][j-4] +
            0.00940f * A[t%2][i-3][j-3] +
            0.00941f * A[t%2][i-3][j-2] +
            0.00942f * A[t%2][i-3][j-1] +
            0.00943f * A[t%2][i-3][j] +
            0.00944f * A[t%2][i-3][j+1] +
            0.00945f * A[t%2][i-3][j+2] +
            0.00946f * A[t%2][i-3][j+3] +
            0.00947f * A[t%2][i-3][j+4] +

            0.00948f * A[t%2][i-2][j-4] +
            0.00949f * A[t%2][i-2][j-3] +
            0.00950f * A[t%2][i-2][j-2] +
            0.00951f * A[t%2][i-2][j-1] +
            0.00952f * A[t%2][i-2][j] +
            0.00953f * A[t%2][i-2][j+1] +
            0.00954f * A[t%2][i-2][j+2] +
            0.00955f * A[t%2][i-2][j+3] +
            0.00956f * A[t%2][i-2][j+4] +

            0.00957f * A[t%2][i-1][j-4] +
            0.00958f * A[t%2][i-1][j-3] +
            0.00959f * A[t%2][i-1][j-2] +
            0.00960f * A[t%2][i-1][j-1] +
            0.00961f * A[t%2][i-1][j] +
            0.00962f * A[t%2][i-1][j+1] +
            0.00963f * A[t%2][i-1][j+2] +
            0.00964f * A[t%2][i-1][j+3] +
            0.00965f * A[t%2][i-1][j+4] +

            0.00966f * A[t%2][i][j-4] +
            0.00967f * A[t%2][i][j-3] +
            0.00968f * A[t%2][i][j-2] +
            0.00969f * A[t%2][i][j-1] +
            0.22400f * A[t%2][i][j] +
            0.00971f * A[t%2][i][j+1] +
            0.00972f * A[t%2][i][j+2] +
            0.00973f * A[t%2][i][j+3] +
            0.00974f * A[t%2][i][j+4] +

            0.00975f * A[t%2][i+1][j-4] +
            0.00976f * A[t%2][i+1][j-3] +
            0.00977f * A[t%2][i+1][j-2] +
            0.00978f * A[t%2][i+1][j-1] +
            0.00979f * A[t%2][i+1][j] +
            0.00980f * A[t%2][i+1][j+1] +
            0.00981f * A[t%2][i+1][j+2] +
            0.00982f * A[t%2][i+1][j+3] +
            0.00983f * A[t%2][i+1][j+4] +

            0.00984f * A[t%2][i+2][j-4] +
            0.00985f * A[t%2][i+2][j-3] +
            0.00986f * A[t%2][i+2][j-2] +
            0.00987f * A[t%2][i+2][j-1] +
            0.00988f * A[t%2][i+2][j] +
            0.00989f * A[t%2][i+2][j+1] +
            0.00990f * A[t%2][i+2][j+2] +
            0.00991f * A[t%2][i+2][j+3] +
            0.00992f * A[t%2][i+2][j+4] +

            0.00993f * A[t%2][i+3][j-4] +
            0.00994f * A[t%2][i+3][j-3] +
            0.00995f * A[t%2][i+3][j-2] +
            0.00996f * A[t%2][i+3][j-1] +
            0.00997f * A[t%2][i+3][j] +
            0.00998f * A[t%2][i+3][j+1] +
            0.00999f * A[t%2][i+3][j+2] +
            0.01000f * A[t%2][i+3][j+3] +
            0.01001f * A[t%2][i+3][j+4] +

            0.01002f * A[t%2][i+4][j-4] +
            0.01003f * A[t%2][i+4][j-3] +
            0.01004f * A[t%2][i+4][j-2] +
            0.01005f * A[t%2][i+4][j-1] +
            0.01006f * A[t%2][i+4][j] +
            0.01007f * A[t%2][i+4][j+1] +
            0.01008f * A[t%2][i+4][j+2] +
            0.01009f * A[t%2][i+4][j+3] +
            0.01010f * A[t%2][i+4][j+4];
  }

  return (((end_time != 0.0) ? end_time : sb_time()) - start_time);
}
