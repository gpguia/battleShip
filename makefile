OBJS=battleShip.o board.o
CC=gcc
PROGRAM=./battleShip
CFLAGS=-std=c99
INDIR=./inputs/


all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)
clean:
	rm -f $(PROGRAM) $(OBJS)

test: $(PROGRAM)
	$(PROGRAM) < $(INDIR)example1.txt