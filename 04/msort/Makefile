CFLAGS=-std=gnu11 -Wall -Wextra -O2 -g

all: msort_seq msort_par

msort_seq: msort_seq.c
	cc $(CFLAGS) msort_seq.c -o msort_seq

msort_par: msort_par.c
	cc $(CFLAGS) -fopenmp msort_par.c -o msort_par

.PHONY: clean
clean:
	rm -f msort_seq msort_par

