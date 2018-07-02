#include "Food.h"

/**

*/
int randInt(int min, int max){
    return rand() % (max - min) + min;
}

Food *spawnFood(int foodNum, int width, int height, SnakeList* snake){
    Food *food = (Food *) malloc( foodNum * foodNum );
    for ( int i = 0; i < foodNum; i++ ){
        food[i].x = randInt(0, width);
        food[i].y = randInt(0, height);
        bool needNewLocation;
        do {
            needNewLocation = false;
            for ( int j = 0; j < i; j++ ){
                if ( food[i].x == food[j].x && food[i].y == food[j].y ){
                    needNewLocation = true;
                    break;
                }
            }
            SnakeIterator *iterator = createSnakeIterator(snake);
            while ( hasNext(iterator) ){
                SnakeCell *cell = next(iterator);
                if( food[i].x == cell->x && food[i].y == cell->y ){
                    needNewLocation = true;
                    break;
                }
            }
            
            freeSnakeIterator(iterator);

            if( needNewLocation ){
                //choose new random location for food[i]
                food[i].x = randInt(0, width);
                food[i].y = randInt(0, height);
            }

        } while ( needNewLocation );
    }
    return food;
}

void replaceFood(Food *food, int len, int x, int y, int width, int height, SnakeList* snake){
    Food *end = food + len;
    for(Food *foodItem = food; foodItem < end; foodItem++){
        if(foodItem->x == x && foodItem->y == y){
            bool needNewLocation;
            do {
                foodItem->x = randInt(0, width);
                foodItem->y = randInt(0, height);
                needNewLocation = false;
                SnakeIterator *iterator = createSnakeIterator(snake);
                while ( hasNext(iterator) ){
                    SnakeCell *cell = next(iterator);
                    if( foodItem->x == cell->x && foodItem->y == cell->y ){
                        needNewLocation = true;
                        break;
                    }
                }
                
                freeSnakeIterator(iterator);

                if( needNewLocation ){
                    //choose new random location for food[i]
                    foodItem->x = randInt(0, width);
                    foodItem->y = randInt(0, height);
                }

            } while ( needNewLocation );
            break;
        }
    }
}

void freeFood(Food *food){
    free(food);
}

void drawFood(Food *food, int len, WINDOW *win){
    for(int i = 0; i < len; i++ ) {
        mvwaddch(win, food[i].y, food[i].x, '*');
    }
}

bool hitFood(Food *food, int len, SnakeList *snake, int *x, int *y){
    
    for ( int i = 0; i < len; i++ ) {
        if ( snake->head->x == food[i].x && snake->head->y == food[i].y ) {
            *x = food[i].x;
            *y = food[i].y;
            return true;
        }
    }
    
    return false;
}