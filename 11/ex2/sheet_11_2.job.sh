#!/bin/bash

#$ -q lva.q
#$ -cwd
#$ -N sheet_11_2
#$ -o sheet_11_2.dat
#$ -j yes
#$ -pe openmp 8

echo "module load gcc/8.2.0"
module load gcc/8.2.0

echo "make clean"
make clean
echo "make"
make

perf stat -d ./snippet1_orig_opto3
perf stat -d ./snippet1_orig_unopt
perf stat -d ./snippet1_unr2_opto3
perf stat -d ./snippet1_unr2_unopt
perf stat -d ./snippet1_unr4_opto3
perf stat -d ./snippet1_unr4_unopt
perf stat -d ./snippet1_comp_opto3
perf stat -d ./snippet1_comp_unopt
perf stat -d ./snippet2_orig_opto3
perf stat -d ./snippet2_orig_unopt
perf stat -d ./snippet2_comp_opto3
perf stat -d ./snippet2_comp_unopt
perf stat -d ./snippet3_orig_opto3
perf stat -d ./snippet3_orig_unopt
perf stat -d ./snippet3_licm_opto3
perf stat -d ./snippet3_licm_unopt
perf stat -d ./snippet4_orig_opto3
perf stat -d ./snippet4_orig_unopt
perf stat -d ./snippet4_unsw_opto3
perf stat -d ./snippet4_unsw_unopt
perf stat -d ./snippet5_orig_opto3
perf stat -d ./snippet5_orig_unopt
perf stat -d ./snippet5_dist_opto3
perf stat -d ./snippet5_dist_unopt
perf stat -d ./snippet6_orig_opto3
perf stat -d ./snippet6_orig_unopt
perf stat -d ./snippet6_fuse_opto3
perf stat -d ./snippet6_fuse_unopt
perf stat -d ./snippet7_orig_opto3
perf stat -d ./snippet7_orig_unopt
perf stat -d ./snippet7_splt_opto3
perf stat -d ./snippet7_splt_unopt
perf stat -d ./snippet8_orig_opto3
perf stat -d ./snippet8_orig_unopt
perf stat -d ./snippet8_tile_opto3
perf stat -d ./snippet8_tile_unopt

echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0

