CFLAGS=-std=gnu11 -Wall -Wextra

all: smart stupid

stupid: hadamard_stupid.c
	cc $(CFLAGS) hadamard_stupid.c -o hadamard_stupid
	cc $(CFLAGS) -O2 hadamard_stupid.c -o hadamard_stupid-O2
	cc $(CFLAGS) -O3 hadamard_stupid.c -o hadamard_stupid-O3

smart: hadamard_smart.c
	cc $(CFLAGS) hadamard_smart.c -o hadamard_smart
	cc $(CFLAGS) -O2 hadamard_smart.c -o hadamard_smart-O2
	cc $(CFLAGS) -O3 hadamard_smart.c -o hadamard_smart-O3

.PHONY: clean

clean:
	rm -f hadamard_smart hadamard_smart-O* hadamard_stupid hadamard_stupid-O*

