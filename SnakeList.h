/**
    @file SnakeList.h
    @author Ben Fisher

    Header file that declares funnctions associated with the SnakeList struct.
    SnakeList contains a list of snake cells and forms the snake.
    A SnakeList starts as one cell, can have cells added to it, move in a direction,
    and be drawn. It can determine if the snake hits itself.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include "Directions.h"

#ifndef SNAKELIST
#define SNAKELIST

/**
    Cell inside snake, stores its location and a pointer to the next cell.
*/
typedef struct SnakeCellTag {
    int x;
    int y;
    struct SnakeCellTag *next;
} SnakeCell;

/**
    List of snake cells, keeps a reference to the head of the snake and to the snake's
    direction.
*/
typedef struct {
    SnakeCell *head;
    Direction heading;
} SnakeList;

/**
    Iterator for a SnakeList, allowing outside programs to easily iterate through it without
    knowing how SnakeList works.
*/
typedef struct {
    SnakeCell *current;
} SnakeIterator;

/**
    Allocates memory for a SnakeList. Creates a snake with a length of one cell at (x,y).

    @param x x coordinate of the snake being made
    @param y y coordinate of the snake being made
*/
SnakeList *createSnake(int x, int y);

/**
    Calculates the length of the snake.
    
    @param snake the snake being measured

    @return length of the snake
*/
int snakeLen(SnakeList *snake);

/**
    Adds a cell to the snake at (x,y).

    @param snake the snake having a cell added to it
    @param x x coordinate of the new cell
    @param y y coordinate of the new cell
*/
void addCell(SnakeList *snake, int x, int y);

/**
    Frees the snake from memory by freeing each node.

    @param snake the snake beng freed
*/
void freeSnake(SnakeList *snake);

/**
    Draws a snake to the given window.

    @param snake the snake being drawn
    @param win the window the snake is being drawn on
*/
void drawSnake(SnakeList *snake, WINDOW * win);

/**
    Moves the snake within an area defined by width and height.
    Width and height are passed because the game uses pacman boundaries.

    @param snake the snake being moved
    @param width the width of the game field
    @param height the height of the game field
*/
void moveSnake(SnakeList *snake, int width, int height);

/**
    Determines if the snake's head is colliding with any other cells.

    @param snake the snake being checked

    @return true if the snake is colliding with itself, false if not
*/
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