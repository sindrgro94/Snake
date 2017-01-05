#include "Food.hpp"
#include <list>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;

/////////////////FOOD////////////////////////////

void MovingFood::moveFood(){
    switch (dir){
        case RIGHT:
            setXPosition(_speed);
            break;
        case LEFT:
            setXPosition(-_speed);
            break;
        case UP:
            setYPosition(-_speed);
            break;
        case DOWN:
            setYPosition(_speed);
            break;
    }
}