#!/bin/bash

BINDIR="bin_hybrid"
mkdir -p $BINDIR

NVCC_FLAGS="-gencode=arch=compute_60,code=sm_60"
NVCC_FLAGS="$NVCC_FLAGS -gencode=arch=compute_70,code=sm_70"
NVCC_FLAGS="$NVCC_FLAGS --use_fast_math -Xptxas -v -Xcompiler -fopenmp -O3"

COMPILE ()
{
    local input ppcg_option regnum nvcc_option

    input=$1
    sizes=$2
    label=$3

    ppcg_option="--unroll-copy-shared --unroll-gpu-tile --max-shared-memory=49152"
    ppcg_option="$ppcg_option --hybrid --isolate-full-tiles --sizes=${sizes}"

    for regnum in 0 32 64 96; do
        for sb_type in "float" "double"; do
            nvcc_option="${NVCC_FLAGS}"

            if [ $regnum -gt 0 ]; then
                outpath="$(pwd)/${BINDIR}/${input%.*}.$sb_type.$label.reg${regnum}"
                regopt="--maxrregcount=${regnum}"
            else
                outpath="$(pwd)/${BINDIR}/${input%.*}.$sb_type.$label"
                regopt=""
            fi


            if [ -f $outpath           ] &&
                [ $outpath -nt common.h ] &&
                [ $outpath -nt make.sh  ] &&
                [ $outpath -nt $input   ]; then
                continue
            fi

            echo $outpath

        TMPDIR="$(mktemp -d)"
        cp common.h $TMPDIR
        cp $input $TMPDIR/src.c
        cd $TMPDIR
        ppcg -D SB_TYPE=$sb_type $ppcg_option src.c
        nvcc $regopt -D SB_TYPE=$sb_type $nvcc_option src_*.cu 2>/dev/null
        cd -
        cp $TMPDIR/a.out $outpath
        rm -rf $TMPDIR
        done
    done
}

cd $(dirname "$0")

if [[ "$#" != "3"         ]] ||
   [[ ! -f $(basename $1) ]]; then
    echo "Usage: $0 KERNEL_FILE SIZES LABEL" >&2
    exit -1
fi

COMPILE $(basename $1) $2 $3
