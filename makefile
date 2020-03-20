OBJS=battleShip.o board.o ships.o
CC=gcc
PROGRAM=./battleShip
CFLAGS=-std=c99 -D_POSIX_C_SOURCE=199309L
INDIR=./inputs/


all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)
clean:
	rm -f $(PROGRAM) $(OBJS)

test: $(PROGRAM)
	$(PROGRAM) < $(INDIR)example1.txt
