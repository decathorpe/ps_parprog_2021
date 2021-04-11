#!/bin/bash

#$ -q lva.q
#$ -cwd
#$ -N sheet_03_1
#$ -o sheet_03_1.dat
#$ -j yes
#$ -pe openmp 8

echo "module load gcc/8.2.0"
module load gcc/8.2.0

echo "make clean"
make clean
echo "make"
make

echo "critical"
for i in 1 2 4 8; do OMP_NUM_THREADS=$i ./mcpi_critical; done
echo "atomic"
for i in 1 2 4 8; do OMP_NUM_THREADS=$i ./mcpi_atomic; done
echo "reduction"
for i in 1 2 4 8; do OMP_NUM_THREADS=$i ./mcpi_reduction; done

echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0

