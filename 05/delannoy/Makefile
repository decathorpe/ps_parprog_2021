CFLAGS=-std=gnu11 -Wall -Wextra -O2

all: delannoy_seq delannoy_par_imp delannoy_par_rec

delannoy_seq: delannoy_seq.c
	cc $(CFLAGS) delannoy_seq.c -o delannoy_seq

delannoy_par_imp: delannoy_par_imp.c
	cc $(CFLAGS) -fopenmp delannoy_par_imp.c -o delannoy_par_imp

delannoy_par_rec: delannoy_par_rec.c
	cc $(CFLAGS) -fopenmp delannoy_par_rec.c -o delannoy_par_rec

.PHONY: clean
clean:
	rm -f delannoy_seq delannoy_par_imp delannoy_par_rec

