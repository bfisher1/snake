#CC = gcc
#CFLAGS = -Wall -std=c99 -static -lncurses -ltinfo
#test : test.o
#test.o : test.c

CC = gcc
CFLAGS = -Wall -std=c99 -g

Snake : SnakeList.o main.o
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

SnakeList.o : SnakeList.c SnakeList.h

main.o : main.c SnakeList.h
