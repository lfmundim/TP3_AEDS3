CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -Werror -std=c99 -pedantic -pthread
OBJ = main.o grid.o makeplan.o
DEPS = grid.h makeplan.h
VFLAGS = -v --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes
EXEC = ./exec 4
TIMED_RUN = time ./exec 4

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
