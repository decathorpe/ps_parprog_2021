#!/bin/bash

#$ -q lva.q
#$ -cwd
#$ -N sheet_03_2
#$ -o sheet_03_2.dat
#$ -j yes
#$ -pe openmp 8

echo "module load gcc/8.2.0"
module load gcc/8.2.0

echo "make clean"
make clean
echo "make"
make

echo "original"
for i in 1 2 4 8; do OMP_NUM_THREADS=$i ./ex2 1500; done
echo "bugfree"
for i in 1 2 4 8; do OMP_NUM_THREADS=$i ./ex2_bugfree 1500; done
echo "better"
for i in 1 2 4 8; do OMP_NUM_THREADS=$i ./ex2_better 1500; done

echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0

