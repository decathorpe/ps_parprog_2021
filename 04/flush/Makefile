CFLAGS=-std=gnu11 -Wall -Wextra -O2 -fopenmp -g

all: flush flushed

flush: flush.c
	cc $(CFLAGS) flush.c -o flush

flushed: flushed.c
	cc $(CFLAGS) flushed.c -o flushed

.PHONY: clean
clean:
	rm -f flush flushed

