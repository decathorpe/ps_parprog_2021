CFLAGS=-std=gnu11 -Wall -Wextra -O3

all: a_orig a_par

a_orig: a_orig.c
	cc $(CFLAGS) a_orig.c -o a_orig

a_par: a_par.c
	cc $(CFLAGS) -fopenmp -lm a_par.c -o a_par

.PHONY: clean
clean:
	rm -f a_orig a_par

