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

typedef struct SnakeListTag {
    SnakeCell *head;
    Direction heading;
} SnakeList;

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

#endif /* SNAKELIST */