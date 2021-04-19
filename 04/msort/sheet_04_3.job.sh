#!/bin/bash

#$ -q lva.q
#$ -cwd
#$ -N sheet_04_3
#$ -o sheet_04_3.dat
#$ -j yes
#$ -pe openmp 8

echo "module load gcc/8.2.0"
module load gcc/8.2.0

echo "make clean"
make clean
echo "make"
make

echo "Recursive Sequential"
./msort_seq
./msort_seq
./msort_seq
./msort_seq

echo "OMP_NUM_THREADS=1"
export OMP_NUM_THREADS=1
./msort_par
echo "OMP_NUM_THREADS=2"
export OMP_NUM_THREADS=2
./msort_par
echo "OMP_NUM_THREADS=4"
export OMP_NUM_THREADS=4
./msort_par
echo "OMP_NUM_THREADS=8"
export OMP_NUM_THREADS=8
./msort_par

echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0

