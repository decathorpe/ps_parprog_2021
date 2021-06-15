CFLAGS=-std=gnu11 -Wall -Wextra -O3 -ffast-math

all: nbody pnbody

nbody: nbody.c
	cc $(CFLAGS) -lm -Wno-unknown-pragmas nbody.c -o nbody

pnbody: nbody.c
	cc $(CFLAGS) -lm -fopenmp nbody.c -o pnbody

.PHONY: clean
clean:
	rm -f nbody pnbody

