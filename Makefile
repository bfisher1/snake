CC = gcc
CFLAGS = -Wall -std=c99 -g

Snake : SnakeList.o main.o Food.o
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

Food.o : Food.c Food.h

SnakeList.o : SnakeList.c SnakeList.h

main.o : main.c SnakeList.h Food.h
