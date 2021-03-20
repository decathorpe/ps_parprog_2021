#!/bin/bash

#$ -q lva.q
#$ -cwd
#$ -N sheet_02_2
#$ -o sheet_02_2.dat
#$ -j yes

echo "module load gcc/8.2.0"
module load gcc/8.2.0

echo "make clean"
make clean
echo "make"
make

echo "smart"
echo "cachegrind"
valgrind --tool=cachegrind ./hadamard_smart
echo "perf"
perf stat -e cache-references,cache-misses ./hadamard_smart

echo "stupid"
echo "cachegrind"
valgrind --tool=cachegrind ./hadamard_stupid
echo "perf"
perf stat -e cache-references,cache-misses ./hadamard_stupid

echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0

