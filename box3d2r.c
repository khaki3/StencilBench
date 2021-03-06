#define BENCH_DIM 3
#define BENCH_FPP 249
#define BENCH_RAD 2

#include "common.h"

double kernel_stencil(SB_TYPE *A1, int compsize, int timestep, bool scop)
{
  double start_time = sb_time(), end_time = 0.0;
  int dimsize = compsize + BENCH_RAD * 2;
  SB_TYPE (*A)[dimsize][dimsize][dimsize]
    = (SB_TYPE (*)[dimsize][dimsize][dimsize])A1;

  if (scop) {
#pragma scop
    for (int t = 0; t < timestep; t++)
      for (int i = BENCH_RAD; i < dimsize - BENCH_RAD; i++)
        for (int j = BENCH_RAD; j < dimsize - BENCH_RAD; j++)
          for (int k = BENCH_RAD; k < dimsize - BENCH_RAD; k++)
            A[(t+1)%2][i][j][k] =
              -0.324f*A[t%2][i-2][j][k] +
              0.0020f*A[t%2][i-2][j-2][k-2] +
              0.0030f*A[t%2][i-2][j-2][k-1] +
              0.0040f*A[t%2][i-2][j-2][k] +
              0.0050f*A[t%2][i-2][j-2][k+1] +
              0.0060f*A[t%2][i-2][j-2][k+2] +
              0.0070f*A[t%2][i-2][j-1][k-2] +
              0.0080f*A[t%2][i-2][j-1][k-1] +
              0.0090f*A[t%2][i-2][j-1][k] +
              0.0100f*A[t%2][i-2][j-1][k+1] +
              0.0110f*A[t%2][i-2][j-1][k+2] +
              0.0120f*A[t%2][i-2][j][k-2] +
              0.0130f*A[t%2][i-2][j][k-1] +
              0.0140f*A[t%2][i-2][j][k+1] +
              0.0150f*A[t%2][i-2][j][k+2] +
              0.0160f*A[t%2][i-2][j+1][k-2] +
              0.0170f*A[t%2][i-2][j+1][k-1] +
              0.0180f*A[t%2][i-2][j+1][k] +
              0.0190f*A[t%2][i-2][j+1][k+1] +
              0.0200f*A[t%2][i-2][j+1][k+2] +
              0.0210f*A[t%2][i-2][j+2][k-2] +
              0.0220f*A[t%2][i-2][j+2][k-1] +
              0.0230f*A[t%2][i-2][j+2][k] +
              0.0240f*A[t%2][i-2][j+2][k+1] +
              0.0250f*A[t%2][i-2][j+2][k+2] -

              0.3264f*A[t%2][i-1][j][k] +
              0.0021f*A[t%2][i-1][j-2][k-2] +
              0.0031f*A[t%2][i-1][j-2][k-1] +
              0.0041f*A[t%2][i-1][j-2][k] +
              0.0051f*A[t%2][i-1][j-2][k+1] +
              0.0061f*A[t%2][i-1][j-2][k+2] +
              0.0071f*A[t%2][i-1][j-1][k-2] +
              0.0081f*A[t%2][i-1][j-1][k-1] +
              0.0091f*A[t%2][i-1][j-1][k] +
              0.0101f*A[t%2][i-1][j-1][k+1] +
              0.0111f*A[t%2][i-1][j-1][k+2] +
              0.0121f*A[t%2][i-1][j][k-2] +
              0.0131f*A[t%2][i-1][j][k-1] +
              0.0141f*A[t%2][i-1][j][k+1] +
              0.0151f*A[t%2][i-1][j][k+2] +
              0.0161f*A[t%2][i-1][j+1][k-2] +
              0.0171f*A[t%2][i-1][j+1][k-1] +
              0.0181f*A[t%2][i-1][j+1][k] +
              0.0191f*A[t%2][i-1][j+1][k+1] +
              0.0201f*A[t%2][i-1][j+1][k+2] +
              0.0211f*A[t%2][i-1][j+2][k-2] +
              0.0221f*A[t%2][i-1][j+2][k-1] +
              0.0231f*A[t%2][i-1][j+2][k] +
              0.0241f*A[t%2][i-1][j+2][k+1] +
              0.0251f*A[t%2][i-1][j+2][k+2] +

              0.6712f*A[t%2][i][j][k] +
              0.0022f*A[t%2][i][j-2][k-2] +
              0.0032f*A[t%2][i][j-2][k-1] +
              0.0042f*A[t%2][i][j-2][k] +
              0.0052f*A[t%2][i][j-2][k+1] +
              0.0062f*A[t%2][i][j-2][k+2] +
              0.0072f*A[t%2][i][j-1][k-2] +
              0.0082f*A[t%2][i][j-1][k-1] +
              0.0092f*A[t%2][i][j-1][k] +
              0.0102f*A[t%2][i][j-1][k+1] +
              0.0112f*A[t%2][i][j-1][k+2] +
              0.0122f*A[t%2][i][j][k-2] +
              0.0132f*A[t%2][i][j][k-1] +
              0.0142f*A[t%2][i][j][k+1] +
              0.0152f*A[t%2][i][j][k+2] +
              0.0162f*A[t%2][i][j+1][k-2] +
              0.0172f*A[t%2][i][j+1][k-1] +
              0.0182f*A[t%2][i][j+1][k] +
              0.0192f*A[t%2][i][j+1][k+1] +
              0.0202f*A[t%2][i][j+1][k+2] +
              0.0212f*A[t%2][i][j+2][k-2] +
              0.0222f*A[t%2][i][j+2][k-1] +
              0.0232f*A[t%2][i][j+2][k] +
              0.0242f*A[t%2][i][j+2][k+1] +
              0.0252f*A[t%2][i][j+2][k+2] -

              0.3312f*A[t%2][i+1][j][k] +
              0.0023f*A[t%2][i+1][j-2][k-2] +
              0.0033f*A[t%2][i+1][j-2][k-1] +
              0.0043f*A[t%2][i+1][j-2][k] +
              0.0053f*A[t%2][i+1][j-2][k+1] +
              0.0063f*A[t%2][i+1][j-2][k+2] +
              0.0073f*A[t%2][i+1][j-1][k-2] +
              0.0083f*A[t%2][i+1][j-1][k-1] +
              0.0093f*A[t%2][i+1][j-1][k] +
              0.0103f*A[t%2][i+1][j-1][k+1] +
              0.0113f*A[t%2][i+1][j-1][k+2] +
              0.0123f*A[t%2][i+1][j][k-2] +
              0.0133f*A[t%2][i+1][j][k-1] +
              0.0143f*A[t%2][i+1][j][k+1] +
              0.0153f*A[t%2][i+1][j][k+2] +
              0.0163f*A[t%2][i+1][j+1][k-2] +
              0.0173f*A[t%2][i+1][j+1][k-1] +
              0.0183f*A[t%2][i+1][j+1][k] +
              0.0193f*A[t%2][i+1][j+1][k+1] +
              0.0203f*A[t%2][i+1][j+1][k+2] +
              0.0213f*A[t%2][i+1][j+2][k-2] +
              0.0223f*A[t%2][i+1][j+2][k-1] +
              0.0233f*A[t%2][i+1][j+2][k] +
              0.0243f*A[t%2][i+1][j+2][k+1] +
              0.0253f*A[t%2][i+1][j+2][k+2] -

              0.3336f*A[t%2][i+2][j][k] +
              0.0024f*A[t%2][i+2][j-2][k-2] +
              0.0034f*A[t%2][i+2][j-2][k-1] +
              0.0044f*A[t%2][i+2][j-2][k] +
              0.0054f*A[t%2][i+2][j-2][k+1] +
              0.0064f*A[t%2][i+2][j-2][k+2] +
              0.0074f*A[t%2][i+2][j-1][k-2] +
              0.0084f*A[t%2][i+2][j-1][k-1] +
              0.0094f*A[t%2][i+2][j-1][k] +
              0.0104f*A[t%2][i+2][j-1][k+1] +
              0.0114f*A[t%2][i+2][j-1][k+2] +
              0.0124f*A[t%2][i+2][j][k-2] +
              0.0134f*A[t%2][i+2][j][k-1] +
              0.0144f*A[t%2][i+2][j][k+1] +
              0.0154f*A[t%2][i+2][j][k+2] +
              0.0164f*A[t%2][i+2][j+1][k-2] +
              0.0174f*A[t%2][i+2][j+1][k-1] +
              0.0184f*A[t%2][i+2][j+1][k] +
              0.0194f*A[t%2][i+2][j+1][k+1] +
              0.0204f*A[t%2][i+2][j+1][k+2] +
              0.0214f*A[t%2][i+2][j+2][k-2] +
              0.0224f*A[t%2][i+2][j+2][k-1] +
              0.0234f*A[t%2][i+2][j+2][k] +
              0.0244f*A[t%2][i+2][j+2][k+1] +
              0.0254f*A[t%2][i+2][j+2][k+2];
#pragma endscop
  }
  else {
    for (int t = 0; t < timestep; t++)
#pragma omp parallel for
      for (int i = BENCH_RAD; i < dimsize - BENCH_RAD; i++)
        for (int j = BENCH_RAD; j < dimsize - BENCH_RAD; j++)
          for (int k = BENCH_RAD; k < dimsize - BENCH_RAD; k++)
            A[(t+1)%2][i][j][k] =
              -0.324f*A[t%2][i-2][j][k] +
              0.0020f*A[t%2][i-2][j-2][k-2] +
              0.0030f*A[t%2][i-2][j-2][k-1] +
              0.0040f*A[t%2][i-2][j-2][k] +
              0.0050f*A[t%2][i-2][j-2][k+1] +
              0.0060f*A[t%2][i-2][j-2][k+2] +
              0.0070f*A[t%2][i-2][j-1][k-2] +
              0.0080f*A[t%2][i-2][j-1][k-1] +
              0.0090f*A[t%2][i-2][j-1][k] +
              0.0100f*A[t%2][i-2][j-1][k+1] +
              0.0110f*A[t%2][i-2][j-1][k+2] +
              0.0120f*A[t%2][i-2][j][k-2] +
              0.0130f*A[t%2][i-2][j][k-1] +
              0.0140f*A[t%2][i-2][j][k+1] +
              0.0150f*A[t%2][i-2][j][k+2] +
              0.0160f*A[t%2][i-2][j+1][k-2] +
              0.0170f*A[t%2][i-2][j+1][k-1] +
              0.0180f*A[t%2][i-2][j+1][k] +
              0.0190f*A[t%2][i-2][j+1][k+1] +
              0.0200f*A[t%2][i-2][j+1][k+2] +
              0.0210f*A[t%2][i-2][j+2][k-2] +
              0.0220f*A[t%2][i-2][j+2][k-1] +
              0.0230f*A[t%2][i-2][j+2][k] +
              0.0240f*A[t%2][i-2][j+2][k+1] +
              0.0250f*A[t%2][i-2][j+2][k+2] -

              0.3264f*A[t%2][i-1][j][k] +
              0.0021f*A[t%2][i-1][j-2][k-2] +
              0.0031f*A[t%2][i-1][j-2][k-1] +
              0.0041f*A[t%2][i-1][j-2][k] +
              0.0051f*A[t%2][i-1][j-2][k+1] +
              0.0061f*A[t%2][i-1][j-2][k+2] +
              0.0071f*A[t%2][i-1][j-1][k-2] +
              0.0081f*A[t%2][i-1][j-1][k-1] +
              0.0091f*A[t%2][i-1][j-1][k] +
              0.0101f*A[t%2][i-1][j-1][k+1] +
              0.0111f*A[t%2][i-1][j-1][k+2] +
              0.0121f*A[t%2][i-1][j][k-2] +
              0.0131f*A[t%2][i-1][j][k-1] +
              0.0141f*A[t%2][i-1][j][k+1] +
              0.0151f*A[t%2][i-1][j][k+2] +
              0.0161f*A[t%2][i-1][j+1][k-2] +
              0.0171f*A[t%2][i-1][j+1][k-1] +
              0.0181f*A[t%2][i-1][j+1][k] +
              0.0191f*A[t%2][i-1][j+1][k+1] +
              0.0201f*A[t%2][i-1][j+1][k+2] +
              0.0211f*A[t%2][i-1][j+2][k-2] +
              0.0221f*A[t%2][i-1][j+2][k-1] +
              0.0231f*A[t%2][i-1][j+2][k] +
              0.0241f*A[t%2][i-1][j+2][k+1] +
              0.0251f*A[t%2][i-1][j+2][k+2] +

              0.6712f*A[t%2][i][j][k] +
              0.0022f*A[t%2][i][j-2][k-2] +
              0.0032f*A[t%2][i][j-2][k-1] +
              0.0042f*A[t%2][i][j-2][k] +
              0.0052f*A[t%2][i][j-2][k+1] +
              0.0062f*A[t%2][i][j-2][k+2] +
              0.0072f*A[t%2][i][j-1][k-2] +
              0.0082f*A[t%2][i][j-1][k-1] +
              0.0092f*A[t%2][i][j-1][k] +
              0.0102f*A[t%2][i][j-1][k+1] +
              0.0112f*A[t%2][i][j-1][k+2] +
              0.0122f*A[t%2][i][j][k-2] +
              0.0132f*A[t%2][i][j][k-1] +
              0.0142f*A[t%2][i][j][k+1] +
              0.0152f*A[t%2][i][j][k+2] +
              0.0162f*A[t%2][i][j+1][k-2] +
              0.0172f*A[t%2][i][j+1][k-1] +
              0.0182f*A[t%2][i][j+1][k] +
              0.0192f*A[t%2][i][j+1][k+1] +
              0.0202f*A[t%2][i][j+1][k+2] +
              0.0212f*A[t%2][i][j+2][k-2] +
              0.0222f*A[t%2][i][j+2][k-1] +
              0.0232f*A[t%2][i][j+2][k] +
              0.0242f*A[t%2][i][j+2][k+1] +
              0.0252f*A[t%2][i][j+2][k+2] -

              0.3312f*A[t%2][i+1][j][k] +
              0.0023f*A[t%2][i+1][j-2][k-2] +
              0.0033f*A[t%2][i+1][j-2][k-1] +
              0.0043f*A[t%2][i+1][j-2][k] +
              0.0053f*A[t%2][i+1][j-2][k+1] +
              0.0063f*A[t%2][i+1][j-2][k+2] +
              0.0073f*A[t%2][i+1][j-1][k-2] +
              0.0083f*A[t%2][i+1][j-1][k-1] +
              0.0093f*A[t%2][i+1][j-1][k] +
              0.0103f*A[t%2][i+1][j-1][k+1] +
              0.0113f*A[t%2][i+1][j-1][k+2] +
              0.0123f*A[t%2][i+1][j][k-2] +
              0.0133f*A[t%2][i+1][j][k-1] +
              0.0143f*A[t%2][i+1][j][k+1] +
              0.0153f*A[t%2][i+1][j][k+2] +
              0.0163f*A[t%2][i+1][j+1][k-2] +
              0.0173f*A[t%2][i+1][j+1][k-1] +
              0.0183f*A[t%2][i+1][j+1][k] +
              0.0193f*A[t%2][i+1][j+1][k+1] +
              0.0203f*A[t%2][i+1][j+1][k+2] +
              0.0213f*A[t%2][i+1][j+2][k-2] +
              0.0223f*A[t%2][i+1][j+2][k-1] +
              0.0233f*A[t%2][i+1][j+2][k] +
              0.0243f*A[t%2][i+1][j+2][k+1] +
              0.0253f*A[t%2][i+1][j+2][k+2] -

              0.3336f*A[t%2][i+2][j][k] +
              0.0024f*A[t%2][i+2][j-2][k-2] +
              0.0034f*A[t%2][i+2][j-2][k-1] +
              0.0044f*A[t%2][i+2][j-2][k] +
              0.0054f*A[t%2][i+2][j-2][k+1] +
              0.0064f*A[t%2][i+2][j-2][k+2] +
              0.0074f*A[t%2][i+2][j-1][k-2] +
              0.0084f*A[t%2][i+2][j-1][k-1] +
              0.0094f*A[t%2][i+2][j-1][k] +
              0.0104f*A[t%2][i+2][j-1][k+1] +
              0.0114f*A[t%2][i+2][j-1][k+2] +
              0.0124f*A[t%2][i+2][j][k-2] +
              0.0134f*A[t%2][i+2][j][k-1] +
              0.0144f*A[t%2][i+2][j][k+1] +
              0.0154f*A[t%2][i+2][j][k+2] +
              0.0164f*A[t%2][i+2][j+1][k-2] +
              0.0174f*A[t%2][i+2][j+1][k-1] +
              0.0184f*A[t%2][i+2][j+1][k] +
              0.0194f*A[t%2][i+2][j+1][k+1] +
              0.0204f*A[t%2][i+2][j+1][k+2] +
              0.0214f*A[t%2][i+2][j+2][k-2] +
              0.0224f*A[t%2][i+2][j+2][k-1] +
              0.0234f*A[t%2][i+2][j+2][k] +
              0.0244f*A[t%2][i+2][j+2][k+1] +
              0.0254f*A[t%2][i+2][j+2][k+2];
  }

  return (((end_time != 0.0) ? end_time : sb_time()) - start_time);
}
