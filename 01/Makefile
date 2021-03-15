CFLAGS=-std=gnu11 -Wall -Werror -Wextra -fopenmp

all: slow medium fast

slow: slow.c
	cc $(CFLAGS) slow.c -o slow
	cc $(CFLAGS) -O2 slow.c -o slow-O2
	cc $(CFLAGS) -O3 slow.c -o slow-O3

medium: medium.c
	cc $(CFLAGS) medium.c -o medium
	cc $(CFLAGS) -O2 medium.c -o medium-O2
	cc $(CFLAGS) -O3 medium.c -o medium-O3

fast: fast.c
	cc $(CFLAGS) fast.c -o fast
	cc $(CFLAGS) -O2 fast.c -o fast-O2
	cc $(CFLAGS) -O3 fast.c -o fast-O3

.PHONY: clean
clean:
	rm -f slow slow-O* medium medium-O* fast fast-O*

