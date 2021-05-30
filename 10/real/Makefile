CC=gcc
CC_FLAGS=-O3 -g3 -lm

.PHONY: all
all: real

SRC=$(wildcard *.c)

real: $(SRC)
	@$(CC) $(CC_FLAGS) $(SRC) -o real

.PHONY: clean
clean:
	@rm real

.PHONY: run
run: all
	@echo "Sequential:"
	@./real
	@echo
