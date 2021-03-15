#!/bin/bash

#$ -q lva.q
#$ -cwd
#$ -N sheet_01
#$ -o sheet_01.dat
#$ -j yes
#$ -pe openmp 8

echo "module load gcc/8.2.0"
module load gcc/8.2.0

echo "make clean"
make clean
echo "make"
make

echo "OMP_NUM_THREADS=1"
export OMP_NUM_THREADS=1

echo "slow"
./slow
echo "slow-O2"
./slow-O2
echo "slow-O3"
./slow-O3

echo "medium"
./medium
echo "medium-O2"
./medium-O2
echo "medium-O3"
./medium-O3

echo "fast"
./fast
echo "fast-O2"
./fast-O2
echo "fast-O3"
./fast-O3

echo "OMP_NUM_THREADS=8"
export OMP_NUM_THREADS=8

echo "slow"
./slow
echo "slow-O2"
./slow-O2
echo "slow-O3"
./slow-O3

echo "medium"
./medium
echo "medium-O2"
./medium-O2
echo "medium-O3"
./medium-O3

echo "fast"
./fast
echo "fast-O2"
./fast-O2
echo "fast-O3"
./fast-O3

echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0

