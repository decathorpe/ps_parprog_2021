#!/bin/bash

#$ -q lva.q
#$ -cwd
#$ -N sheet_02_1
#$ -o sheet_02_1.dat
#$ -j yes
#$ -pe openmp 8

echo "module load gcc/8.2.0"
module load gcc/8.2.0

echo "make clean"
make clean
echo "make"
make

echo "sequential"
echo "no optimizations"
for i in {1..10}; do ./mandelbrot; done
echo "-O2"
for i in {1..10}; do ./mandelbrot-O2; done
echo "-O3"
for i in {1..10}; do ./mandelbrot-O3; done

echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0

