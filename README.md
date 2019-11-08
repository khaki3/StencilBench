# StencilBench const

This repository provides the script to generate "Loop Tiling" and "Hybrid Tiling" code by PPCG. The original code have fixed loop ranges for the reason we described in the paper. 

## Install

At first, clone PPCG from our repository to your local machine:

```
% git clone 'https://github.com/khaki3/ppcg.git' && cd ppcg
```

Then, build it by following commands:

```
% ./get_submodules.sh && ./autogen.sh

% CC=gcc-4.8 CXX=g++-4.8 ./configure && make && make install
```

## Loop Tiling

To generate "Loop Tiling" code and compile it, run `make_ppcg.sh` with a kernel file:

```
% ./make_ppcg.sh j2d5pt.c
/home/user/StencilBench/bin_ppcg/j2d5pt.float
/home/user/StencilBench/bin_ppcg/j2d5pt.double
```

The script shows the paths to the single/double-precision binaries which are executable on both NVIDIA V100 and P100. To execute these binaries, specify the fixed problem size below:
```
% ./bin_ppcg/j2d5pt.float -t 1000 -s 16384 -n 2 -c
[Device warm-up]
3800.9172 ms

[Device execution]
0:   706.3307 GFLOPS,  3800.4219 ms
1:   706.3340 GFLOPS,  3800.4042 ms
Average:   706.3323 GFLOPS,  3800.4131 ms

[CPU execution]
32158.3083 ms
Max Error: 3.051758e-05
RMS Error: 4.138244e-08
```

In the case of 3D stencils:
```
% ./bin_ppcg/j3d27pt.float -t 1000 -s 512 -n 2 -c
```

## Hybrid Tiling

The directory `hybrid-params` provides the result of parameter tuning for "Hybrid Tiling" code. To look up the optimal parameter (while replacing `v100` by your GPU name and `j2d5pt` by the kernel name):

```
% cat hybrid-params/hybrid-parameter-search-log/v100/j2d5pt.log | grep GFLOPS | sort -nr -k 2 | head -n 1
8_6_256_1_256 2814.0697 GFLOPS
% cat hybrid-params/hybrid-parameter-search-log/v100/j3d27pt.log | grep GFLOPS | sort -nr -k 2 | head -n 1
4_1_16_32_1_16_32 2789.3230 GFLOPS
```

The first column in the output is described as follows:
```
[2D] {b_T}_{b_S1}_{b_S2}_{n_thr_S1}_{n_thr_S2}
[3D] {b_T}_{b_S1}_{b_S2}_{b_S3}_{n_thr_S1}_{n_thr_S2}_{n_thr_S3}
```

The script `build_hybrid.sh` prepares every benchmark tuned with the optimal parameter (while taking 10+ mins).
```
% ./build_hybrid.sh
...
```

To execute binaries compiled with several register restrictions, in the case of 2D stencils:
```
% for i in ./bin_hybrid/j2d5pt.float.v100*; do echo ==== $i; $i -t 1000 -s 16384 -n 2 -c; done
==== ./bin_hybrid/j2d5pt.float.v100
[Device warm-up]
857.4926 ms

[Device execution]
0:  3144.1309 GFLOPS,   853.7668 ms
1:  3144.4953 GFLOPS,   853.6679 ms
Average:  3144.3131 GFLOPS,   853.7173 ms

[CPU execution]
32536.5031 ms
Max Error: 3.051758e-05
RMS Error: 4.138244e-08
==== ./bin_hybrid/j2d5pt.float.v100.reg32
[Device warm-up]
931.8388 ms
...
```

In the case of 3D stencils:
```
% for i in ./bin_hybrid/j3d27pt.float.v100*; do echo ==== $i; $i -t 1000 -s 512 -n 2 -c; done
```
