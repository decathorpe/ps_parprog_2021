#!/bin/bash

#$ -q lva.q
#$ -cwd
#$ -N sheet_12
#$ -o sheet_12.dat
#$ -j yes
#$ -pe openmp 8

echo "module load gcc/10.3.0"
module load gcc/10.3.0

echo "make clean"
make clean
echo "make"
make

echo "./nbody 5000 100 0"
/usr/bin/time -v ./nbody 5000 100 0
/usr/bin/time -v ./nbody 5000 100 0
/usr/bin/time -v ./nbody 5000 100 0

echo "OMP_NUM_THREADS=1 ./pnbody 5000 100 0"
OMP_NUM_THREADS=1 /usr/bin/time -v ./pnbody 5000 100 0
OMP_NUM_THREADS=1 /usr/bin/time -v ./pnbody 5000 100 0
OMP_NUM_THREADS=1 /usr/bin/time -v ./pnbody 5000 100 0
echo "OMP_NUM_THREADS=2 ./pnbody 5000 100 0"
OMP_NUM_THREADS=2 /usr/bin/time -v ./pnbody 5000 100 0
OMP_NUM_THREADS=2 /usr/bin/time -v ./pnbody 5000 100 0
OMP_NUM_THREADS=2 /usr/bin/time -v ./pnbody 5000 100 0
echo "OMP_NUM_THREADS=4 ./pnbody 5000 100 0"
OMP_NUM_THREADS=4 /usr/bin/time -v ./pnbody 5000 100 0
OMP_NUM_THREADS=4 /usr/bin/time -v ./pnbody 5000 100 0
OMP_NUM_THREADS=4 /usr/bin/time -v ./pnbody 5000 100 0
echo "OMP_NUM_THREADS=8 ./pnbody 5000 100 0"
OMP_NUM_THREADS=8 /usr/bin/time -v ./pnbody 5000 100 0
OMP_NUM_THREADS=8 /usr/bin/time -v ./pnbody 5000 100 0
OMP_NUM_THREADS=8 /usr/bin/time -v ./pnbody 5000 100 0

echo "make clean"
make clean

echo "module unload gcc/10.3.0"
module unload gcc/10.3.0

