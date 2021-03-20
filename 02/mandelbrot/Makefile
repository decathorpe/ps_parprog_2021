CFLAGS=-std=gnu11 -Wall -Wextra -lm

all: sequential parallel

sequential: mandelbrot.c
	cc $(CFLAGS) mandelbrot.c -o mandelbrot
	cc $(CFLAGS) -O2 mandelbrot.c -o mandelbrot-O2
	cc $(CFLAGS) -O3 mandelbrot.c -o mandelbrot-O3

parallel: mandelbrot_omp.c
	cc $(CFLAGS) -fopenmp mandelbrot_omp.c -o mandelbrot-omp
	cc $(CFLAGS) -fopenmp -O2 mandelbrot_omp.c -o mandelbrot-omp-O2
	cc $(CFLAGS) -fopenmp -O3 mandelbrot_omp.c -o mandelbrot-omp-O3

.PHONY: clean
clean:
	rm -f mandelbrot mandelbrot-O* mandelbrot-omp mandelbrot-omp-O* mandelbrot.png

