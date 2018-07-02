/**
    @file Food.h
    @author Ben Fisher

    Header file that declares functions related to an array of Food items.
    Food is initially spawned as an array of a constant size.
    When an item is eaten by the snake, that food item is replaced by one
    at a new location.
*/
#include <stdlib.h>
#include <ncurses.h>
#include "SnakeList.h"

#ifndef FOOD
#define FOOD

/**
    Structure for storing a piece of food at a location.
*/
typedef struct FoodTag {
    int x;
    int y;
} Food;

/**
    Creates an array of food items spawned at random coordinates.
    Spawns foodNum food items inside the range of width and height.
    Makes sure not to spawn food on the snake or on other food items.
    
    @param foodNum number of food items to be spawned
    @param width width of range items can be spawned in
    @param height height of range items can be spawned in
    @param snake snake that items cannot be spawned on

    @return pointer to array of randomly spawned food items
    
*/
Food *spawnFood(int foodNum, int width, int height, SnakeList* snake);

/**
    Deletes the food item at (x,y) and replaces it with food at a new location.
    Makes sure newly spawned food item is within width and height, and not on snake.
    Makes sure new food item isn't spawned in the old location.

    @param food pointer to array of food items
    @param len length of food array
    @param x x coordinate of the item getting replaced
    @param y y coordinate of the item getting replaced
    @param width width of range items can be spawned in
    @param height height of range items can be spawned in
    @param snake snake that the new item cannot be spawned on

*/
void replaceFood(Food *food, int len, int x, int y, int width, int height, SnakeList* snake);

/**
    Frees the array pointed to by food.

    @param food food array being freed
*/
void freeFood(Food *food);

/**
    Draws the array of food items in the given window.

    @param food array of food
    @param len length of the food array
    @param win window food is being drawn in

*/
void drawFood(Food *food, int len, WINDOW *win);

/**
    Figures out if the snake has collided with any food.

    @param food food that the snake could collide with
    @param len length of the food array
    @param snake snake that could collide with food
    @param x pointer to variable that saves the x coordinate of the collided food
    @param y pointer to variable that saves the y coordinate of the collided food
    
    @return true if the snake is hitting the food
*/
bool hitFood(Food *food, int len, SnakeList *snake, int *x, int *y);

#endif /* FOOD */