#define BENCH_DIM 2
#define BENCH_FPP 10
#define BENCH_RAD 1

#include "common.h"

double kernel_stencil(SB_TYPE *A1, int compsize, int timestep, bool scop)
{
  double start_time = sb_time(), end_time = 0.0;
  #define timestep 1000
  #define compsize 16384
  #define dimsize (compsize + BENCH_RAD * 2)
  SB_TYPE (*A)[dimsize][dimsize] = (SB_TYPE (*)[dimsize][dimsize])A1;

  if (scop) {
#pragma scop
    for (int t = 0; t < timestep; t++)
      for (int i = BENCH_RAD; i < compsize + BENCH_RAD; i++)
        for (int j = BENCH_RAD; j < compsize + BENCH_RAD; j++)
          A[(t+1)%2][i][j] = (5.1f * A[t%2][i-1][j]
                              + 12.1f * A[t%2][i][j-1] + 15.0f * A[t%2][i][j]
                              + 12.2f * A[t%2][i][j+1] + 5.2f * A[t%2][i+1][j]) / 118;
#pragma endscop
  }
  else {
    for (int t = 0; t < timestep; t++)
#pragma omp parallel for
      for (int i = BENCH_RAD; i < compsize + BENCH_RAD; i++)
        for (int j = BENCH_RAD; j < compsize + BENCH_RAD; j++)
          A[(t+1)%2][i][j] = (5.1f * A[t%2][i-1][j]
                              + 12.1f * A[t%2][i][j-1] + 15.0f * A[t%2][i][j]
                              + 12.2f * A[t%2][i][j+1] + 5.2f * A[t%2][i+1][j]) / 118;
  }

  return (((end_time != 0.0) ? end_time : sb_time()) - start_time);
}
