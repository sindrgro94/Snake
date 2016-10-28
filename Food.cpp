#include "Food.hpp"
#include <list>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;

/////////////////FOOD////////////////////////////
Food::Food(int x, int y, int value, int size, int speed, bool specialFood):_x(x),_y(y),_value(value),_size(size),_speed(speed),_specialFood(specialFood){}

