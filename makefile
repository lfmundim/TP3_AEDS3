CC = gcc
CFLAGS = -g -O0 -Wall -std=c99 -pedantic -pthread
OBJ = main.o grid.o makeplan.o
DEPS = grid.h makeplan.h
VFLAGS = --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes
EXEC = ./exec < toys/toy1
TIMED_RUN = time ./exec < toys/toy1

all: exec

exec: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o exec

valgrind:
	valgrind $(VFLAGS) $(EXEC)

run:
	$(EXEC)

timed:
	$(TIMED_RUN)
