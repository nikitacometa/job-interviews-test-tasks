# Script for comparing the utility to a different binary with same functionality

#!/usr/bin/env bash

FILENAME=$1

SINGLE_THREAD=single
MULTI_THREAD=multi

BLOCK_SIZE=1048576
if [[ ! -z $2 ]]
then
    BLOCK_SIZE=$2
    echo ${BLOCK_SIZE}
fi

make || exit

echo -en "\nEvaluating single-threaded signer..."
time ./${SINGLE_THREAD} -i ${FILENAME} -o single_output -b ${BLOCK_SIZE} || exit

echo -en "\nEvaluating multi-threaded signer..."
time ./${MULTI_THREAD} -i ${FILENAME} -o multi_output -b ${BLOCK_SIZE} -s spam || exit

diff single_output multi_output && rm -f single_output multi_output
