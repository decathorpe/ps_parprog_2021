CC=gcc
CC_FLAGS=-O3 -g3 -lm

.PHONY: all
all: real real_inst real_omp real_omp_inst

SHARED_SRC=c_timers.c print_results.c randdp.c wtime.c

real: $(SHARED_SRC) real.c
	@$(CC) $(CC_FLAGS) $(SHARED_SRC) real.c -o real

real_inst: $(SHARED_SRC) real.c
	@$(CC) $(CC_FLAGS) -pg $(SHARED_SRC) real.c -o real_inst

real_omp: $(SHARED_SRC) real_omp.c
	@$(CC) $(CC_FLAGS) -fopenmp $(SHARED_SRC) real_omp.c -o real_omp

real_omp_inst: $(SHARED_SRC) real_omp.c
	@$(CC) $(CC_FLAGS) -fopenmp -pg $(SHARED_SRC) real_omp.c -o real_omp_inst

.PHONY: clean
clean:
	@rm -f real real_inst real_omp real_omp_inst

.PHONY: run
run: all
	@echo "Sequential:"
	@./real
	@echo
