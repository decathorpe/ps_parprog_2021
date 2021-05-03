CFLAGS=-std=gnu11 -Wall -Wextra -O3

all: nqueens_seq nqueens_par

nqueens_seq: nqueens_seq.c
	cc $(CFLAGS) nqueens_seq.c -o nqueens_seq

nqueens_par: nqueens_par.c
	cc $(CFLAGS) -fopenmp nqueens_par.c -o nqueens_par

.PHONY: clean
clean:
	rm -f nqueens_seq nqueens_par

