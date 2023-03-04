CC = gcc
CFLAGS = -lncurses -lm
SOURCES = ./src/*.c

all: rogue run clean

rogue: 
		$(CC) $(SOURCES) $(CFLAGS) -o rogue

run:
		./rogue

clean:
		rm rogue
