#!/bin/bash

#$ -q lva.q
#$ -cwd
#$ -N sheet_05_1
#$ -o sheet_05_1.dat
#$ -j yes
#$ -pe openmp 8

echo "module load gcc/8.2.0"
module load gcc/8.2.0

echo "make clean"
make clean
echo "make"
make

echo "Sequential"
./delannoy_seq 12
./delannoy_seq 12
./delannoy_seq 12
./delannoy_seq 12

echo "OMP_NUM_THREADS=1"
export OMP_NUM_THREADS=1
./delannoy_par_rec 12
echo "OMP_NUM_THREADS=2"
export OMP_NUM_THREADS=2
./delannoy_par_rec 12
echo "OMP_NUM_THREADS=3"
export OMP_NUM_THREADS=3
./delannoy_par_rec 12
echo "OMP_NUM_THREADS=4"
export OMP_NUM_THREADS=4
./delannoy_par_rec 12

echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0

