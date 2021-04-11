CFLAGS=-std=gnu11 -Wall -Wextra -g

all: mcpi_atomic mcpi_critical mcpi_reduction

mcpi_atomic: mcpi_atomic.c
	cc $(CFLAGS) -fopenmp mcpi_atomic.c -o mcpi_atomic
	cc $(CFLAGS) -fopenmp -O2 mcpi_atomic.c -o mcpi_atomic-O2

mcpi_critical: mcpi_critical.c
	cc $(CFLAGS) -fopenmp mcpi_critical.c -o mcpi_critical
	cc $(CFLAGS) -fopenmp -O2 mcpi_critical.c -o mcpi_critical-O2

mcpi_reduction: mcpi_reduction.c
	cc $(CFLAGS) -fopenmp mcpi_reduction.c -o mcpi_reduction
	cc $(CFLAGS) -fopenmp -O2 mcpi_reduction.c -o mcpi_reduction-O2

.PHONY: clean

clean:
	rm -f mcpi_atomic mcpi_critical mcpi_reduction mcpi_atomic-O2 mcpi_critical-O2 mcpi_reduction-O2

