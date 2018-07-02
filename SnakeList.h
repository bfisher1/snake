#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include "Directions.h"

#ifndef SNAKELIST
#define SNAKELIST

typedef struct SnakeCellTag {
    int x;
    int y;
    struct SnakeCellTag *next;
} SnakeCell;

typedef struct {
    SnakeCell *head;
    Direction heading;
} SnakeList;

typedef struct {
    SnakeCell *current;
} SnakeIterator;

SnakeList *createSnake(int x, int y);

int snakeLen(SnakeList *snake);

void addCell(SnakeList *snake, int x, int y);

void freeSnake(SnakeList *snake);

void drawSnake(SnakeList *snake, WINDOW * win);

void moveSnake(SnakeList *snake, int width, int height);

bool hitSelf(SnakeList *snake);

/**
    Changes the snakes heading to the new direction if it can go the new way.
    For instance, the snake can change direction from up to left or right,
    but not from up to down.
*/  
void changeSnakeDir(SnakeList *snake, Direction newDirection);

/**
    Creates a new iterator for the cells of the given snake.

    @param snake that the iterator iterates through

    @return snake iterator

*/
SnakeIterator *createSnakeIterator(SnakeList *snake);

/**
    Determines if the iterator has a next element.

    @param iterator the snake's iterator

    @return true if there is a next cell, false if not
*/
bool hasNext(SnakeIterator *iterator);

/**
    Returns the next element being iterated through.

    @param iterator the snake's iterator

    @return next cell in the snake
*/
SnakeCell *next(SnakeIterator *iterator);

/**
    Frees the snake iterator from memory.

    @param iterator the iterator being freed
*/
void freeSnakeIterator(SnakeIterator *iterator);

/**
    Grows the snake from the head in the direction it is moving.

    @param snake snake being grown
**/
void growSnake(SnakeList *snake);

#endif /* SNAKELIST */