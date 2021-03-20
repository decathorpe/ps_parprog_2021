CFLAGS=-std=gnu11 -Wall -Wextra -g

all: sequential parallel

sequential: mcpi_seq.c
	cc $(CFLAGS) mcpi_seq.c -o mcpi_seq
	cc $(CFLAGS) -O2 mcpi_seq.c -o mcpi_seq-O2
	cc $(CFLAGS) -O3 mcpi_seq.c -o mcpi_seq-O3

parallel: mcpi_par.c
	cc $(CFLAGS) -lpthread mcpi_par.c -o mcpi_par
	cc $(CFLAGS) -lpthread -O2 mcpi_par.c -o mcpi_par-O2
	cc $(CFLAGS) -lpthread -O3 mcpi_par.c -o mcpi_par-O3

.PHONY: clean

clean:
	rm -f mcpi_seq mcpi_seq-O2 mcpi_seq-O3 mcpi_par mcpi_par-O2 mcpi_par-O3

