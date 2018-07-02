/**
    @file main.c
    @author Ben Fisher

    Main program run for snake that contains the game loop and flow of control.
    Snake is a game where you control the movement of a snake around an area.
    You move the snake towards food, which it grows when it eats. If the snake
    runs into itself, the game is over.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <time.h>
#include "SnakeList.h"
#include "Directions.h"
#include "Food.h"
/**
    Starting point of the program.

    @param argc number of command line arguments
    @param argv array of command line arguments

    @return exit status of the program
*/
int main(int argc, char *argv[]){
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    int score = 0;
    int width = 70;
    int height = 20;
    int delay = 40000;
    WINDOW * win = newwin(height + 1, width + 1, 0, 0);

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
        //read user key press
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
        //update snake position and drawings based on delay time
        if( clock() >= start + delay ){
            wclear(win);
            moveSnake(snake, width, height);
            //draw the score
            char scoreStr[10];
            sprintf(scoreStr, "%d", score);
            for(int i = 0; scoreStr[i]; i++){
                mvwaddch(win, 0, i, scoreStr[i]);
            }
            //draw snake and food
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
    return EXIT_SUCCESS;
}