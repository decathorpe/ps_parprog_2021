CFLAGS=-std=gnu11 -Wall -Wextra -O3

all: presum_seq presum_par

presum_seq: presum_seq.c
	cc $(CFLAGS) presum_seq.c -o presum_seq

presum_par: presum_par.c
	cc $(CFLAGS) -fopenmp presum_par.c -o presum_par

.PHONY: clean
clean:
	rm -f presum_seq presum_par

