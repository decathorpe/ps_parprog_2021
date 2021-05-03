#!/bin/bash

#$ -q lva.q
#$ -cwd
#$ -N sheet_06_1
#$ -o sheet_06_1.dat
#$ -j yes
#$ -pe openmp 8

echo "module load gcc/8.2.0"
module load gcc/8.2.0

echo "make clean"
make clean
echo "make"
make

echo "Sequential"
./presum_seq 1000000000
./presum_seq 1000000000
./presum_seq 1000000000
./presum_seq 1000000000
./presum_seq 1000000000

echo "OMP_NUM_THREADS=1"
export OMP_NUM_THREADS=1
./presum_par 1000000000
echo "OMP_NUM_THREADS=2"
export OMP_NUM_THREADS=2
./presum_par 1000000000
echo "OMP_NUM_THREADS=3"
export OMP_NUM_THREADS=3
./presum_par 1000000000
echo "OMP_NUM_THREADS=4"
export OMP_NUM_THREADS=4
./presum_par 1000000000
echo "OMP_NUM_THREADS=5"
export OMP_NUM_THREADS=5
./presum_par 1000000000
echo "OMP_NUM_THREADS=6"
export OMP_NUM_THREADS=6
./presum_par 1000000000
echo "OMP_NUM_THREADS=7"
export OMP_NUM_THREADS=7
./presum_par 1000000000
echo "OMP_NUM_THREADS=8"
export OMP_NUM_THREADS=8
./presum_par 1000000000

echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0

