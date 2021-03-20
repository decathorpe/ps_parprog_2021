#!/bin/bash

#$ -q lva.q
#$ -cwd
#$ -N sheet_02_3
#$ -o sheet_02_3.dat
#$ -j yes
#$ -pe openmp 8

echo "module load gcc/8.2.0"
module load gcc/8.2.0

echo "make clean"
make clean
echo "make"
make

echo "sequential"
for i in 100000 200000 500000 1000000 2000000 5000000 10000000 20000000 50000000 100000000 200000000 500000000 1000000000; do ./mcpi_seq $i; done
for i in 100000 200000 500000 1000000 2000000 5000000 10000000 20000000 50000000 100000000 200000000 500000000 1000000000; do ./mcpi_seq-O2 $i; done

echo "parallel"
export ITERATIONS=500000000
for i in {1..8}; do ./mcpi_par $ITERATIONS $i; done
for i in {1..8}; do ./mcpi_par-O2 $ITERATIONS $i; done

echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0

