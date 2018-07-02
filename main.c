#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <time.h>
#include "SnakeList.h"
#include "Directions.h"
#include "Food.h"

int main(int argc, char *argv[]){
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    int score = 0;
    int width = 70;
    int height = 20;
    int delay = 40000;
    //timeout(500);
    WINDOW * win = newwin(height, width, 0, 0);

    nodelay(stdscr, TRUE);
    SnakeList *snake = createSnake(10,10);
    
    
    //set up random number generator
    time_t t;
    srand((unsigned) time(&t));

    //spawn original food amounts
    int foodLen = 3;
    Food *food = spawnFood(foodLen, width, height, snake);

    int key;
    clock_t start = clock();
    while(true) {
        if( (key = getch()) != ERR  ) {
            
            if(key ==  KEY_DOWN){
                changeSnakeDir(snake, DOWN);
            }
            else if ( key == KEY_UP ){
                changeSnakeDir(snake, UP);
            }
            else if(key == KEY_RIGHT ){
                changeSnakeDir(snake, RIGHT);
            }
            else if(key ==  KEY_LEFT ){
                changeSnakeDir(snake, LEFT);
            }
        
        }
        
        if( clock() >= start + delay ){
            wclear(win);
            moveSnake(snake, width, height);
            drawSnake(snake, win);
            drawFood(food, foodLen, win);
            
            wrefresh(win);
            
            start = clock() + delay;
        }
        
        if ( hitSelf(snake) ){
            
            break;
        }

        int x, y;
        if( hitFood(food, foodLen, snake, &x, &y) ){
            
            replaceFood(food, foodLen, x, y, width, height, snake);
            growSnake(snake);
            score++;
        }
        
    }

    freeSnake(snake);
    endwin();
    printf("GAME OVER. SCORE: %d\n", score);
    return 0;
}
