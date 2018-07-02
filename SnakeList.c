/**
    @file SnakeList.c
    @author Ben Fisher

    Implementation file for functions defined in SnakeList.h.
    Functions in this file are related to the snake entity.
*/
#include "SnakeList.h"

SnakeList *createSnake(int x, int y){
    SnakeList *snake = (SnakeList *) malloc(sizeof(SnakeList));
    snake->head = (SnakeCell *) malloc(sizeof(SnakeCell));
    snake->head->x = x;
    snake->head->y = y;
    snake->head->next = NULL;
    snake->heading = DOWN;

    return snake;
}

int snakeLen(SnakeList *snake){
    int i = 0;
    for( SnakeCell *cell = snake->head; cell; cell = cell->next){
        i++;
    }
    return i;
}

void addCell(SnakeList *snake, int x, int y){
    SnakeCell *newFront = (SnakeCell *) malloc(sizeof(SnakeCell));
    newFront->x = x;
    newFront->y = y;
    newFront->next = snake->head;
    snake->head = newFront;
    return;
}

void freeSnake(SnakeList *snake){
    //free each cell
    SnakeCell *cell = snake->head;
    while(cell){
        SnakeCell *temp = cell->next;
        free(cell);
        cell = temp;
    }
    //free the snake list
    free(snake);
}

void drawSnake(SnakeList *snake, WINDOW * win) {
    for ( SnakeCell *cell = snake->head; cell; cell = cell->next ) {
        mvwaddch(win, cell->y, cell->x, '0');
    }
}
    
void moveSnake(SnakeList *snake, int width, int height){
    int dx = 0, dy = 0;
    Direction direction = snake->heading;
    
    switch(direction){
        case UP:
            dy = -1;
            break;
        case DOWN:
            dy = 1;
            break;
        case LEFT:
            dx = -1;
            break;
        case RIGHT:
            dx = 1;
            break;
        default:
            break;
    }

    int px = snake->head->x, py = snake->head->y;
    snake->head->x += dx;
    snake->head->y += dy;
    
    //Pacman boundaries
    int indent = 0;
    if(snake->head->x < 0 + indent){
        snake->head->x = width - indent;
    }
    else if(snake->head->x > width - indent){
        snake->head->x = 0 + indent;
    }
    else if(snake->head->y < 0 + indent){
        snake->head->y = height - indent;
    }
    else if(snake->head->y > height - indent){
        snake->head->y = 0 + indent;
    }

    for ( SnakeCell *cell = snake->head->next; cell; cell = cell->next ) {
        int tx = cell->x, ty = cell->y;
        cell->x = px;
        cell->y = py;
        px = tx, py = ty;
    }
}

bool hitSelf(SnakeList *snake) {
    SnakeCell *head = snake->head;
    for ( SnakeCell *cell = snake->head->next; cell; cell = cell->next ) {
        if ( head->x == cell->x && head->y == cell->y ){
            return true;
        }
    }
    return false;
}


void changeSnakeDir(SnakeList *snake, Direction newDirection){
    Direction direction = snake->heading;
    switch(direction){
        snake->heading = newDirection;
        
        case UP:
            if(newDirection != DOWN){
                snake->heading = newDirection;
            }
            break;
        case DOWN:
            if(newDirection != UP){
                snake->heading = newDirection;
            }
            break;
        case LEFT:
            if(newDirection != RIGHT){
                snake->heading = newDirection;
            }
            break;
        case RIGHT:
            if(newDirection != LEFT){
                snake->heading = newDirection;
            }
            break;
        default:
            break;
    }
}

SnakeIterator *createSnakeIterator(SnakeList *snake){
    SnakeIterator *iterator = (SnakeIterator *) malloc(sizeof(SnakeIterator));
    iterator->current = snake->head;
    return iterator;
}

bool hasNext(SnakeIterator *iterator){
    return iterator->current;
}

SnakeCell *next(SnakeIterator *iterator){
    SnakeCell *prev = iterator->current;
    iterator->current = iterator->current->next;
    return prev;
}

void freeSnakeIterator(SnakeIterator *iterator){
    free(iterator);
}

void growSnake(SnakeList *snake){
    Direction direction = snake->heading;
    switch(direction){
        case UP:
            addCell(snake, snake->head->x, snake->head->y - 1);
            break;
        case DOWN:
            addCell(snake, snake->head->x, snake->head->y + 1);
            break;
        case LEFT:
            addCell(snake, snake->head->x - 1, snake->head->y);
            break;
        case RIGHT:
            addCell(snake, snake->head->x + 1, snake->head->y);
            break;
        default:
            break;
    }   
}