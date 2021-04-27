CFLAGS=-std=gnu11 -Wall -Wextra -O2 -g

all: stencil_seq stencil_par

stencil_seq: stencil_seq.c
	cc $(CFLAGS) stencil_seq.c -o stencil_seq

stencil_par: stencil_par.c
	cc $(CFLAGS) -fopenmp stencil_par.c -o stencil_par

.PHONY: clean
clean:
	rm -f stencil_seq stencil_par

