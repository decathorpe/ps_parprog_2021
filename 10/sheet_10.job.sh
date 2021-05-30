#!/bin/bash

#$ -q lva.q
#$ -cwd
#$ -N sheet_10
#$ -o sheet_10.dat
#$ -j yes
#$ -pe openmp 8

echo "module load gcc/8.2.0"
module load gcc/8.2.0

echo "make clean"
make clean
echo "make"
make

echo "Sequential"
/usr/bin/time -v ./real
/usr/bin/time -v ./real
/usr/bin/time -v ./real
/usr/bin/time -v ./real
/usr/bin/time -v ./real

echo "Parallelized"
for i in 1 2 4 8; do
    echo "OMP_NUM_THREADS=$i"
    export OMP_NUM_THREADS=$i
    /usr/bin/time -v ./real_omp
    /usr/bin/time -v ./real_omp
    /usr/bin/time -v ./real_omp
    /usr/bin/time -v ./real_omp
    /usr/bin/time -v ./real_omp
done

echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0

