#!/bin/bash

GPUNAME=$(nvidia-smi -L | grep -oP '[PV]100' | head -n1 | tr '[PV]' '[pv]')

if [[ -z $GPUNAME ]]
then
	echo "Could not find Tesla P100 or V100"
	exit 1
fi

./build_hybrid.sh

while [[ `ps -A | grep make_hybrid2.sh | wc -l` -gt 0 ]]
do
    echo "Waiting for remaining compilations to finish..."
    sleep 5
done

run ()
{
    bin=$1
    if [[ $i =~ "2d" ]]; then
        size="16384"
    elif [[ $i =~ "3d" ]]; then
        size="512"
    fi

    echo @@@ $bin @@@
    $bin -s $size -t 1000 -n 5
}

{
    for i in $(ls bin_hybrid/ | grep $GPUNAME) ; do
        run ./bin_hybrid/$i
    done
} | tee hybrid.log

for i in *.c ; do
    for regnum in 0 32 64; do
        ./make_ppcg.sh $i $regnum
    done
done

{
    for i in $(ls bin_ppcg/) ; do
        run ./bin_ppcg/$i;
    done
} | tee loop_tiling.log
