#pragma once
#include "Enum.hpp"
#include <list>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;

class Food{
private:
    int _x,_y;
    int _value;
    int _size;
    bool specialFood;
public:
    Food(int x, int y, int value, int size, bool specialFood):_x(x),_y(y),_value(value),_size(size),specialFood(specialFood){};
    //getFunctions:
    int getY(){return _y;}
    int getX(){return _x;}
    int getFoodSize(){return _size;}
    int getFoodValue(){return _value;}
    bool isSpecialFood(){return specialFood;}
    virtual pair<NormalFood,SpecialFood> getFoodType();
    
};
class StationaryFood : public Food{
private:
    NormalFood foodType;
public:
    StationaryFood(int x, int y, int value, int size,NormalFood normalFood):foodType(normalFood),Food(x,y,value,size,false){};
    pair<NormalFood,SpecialFood> getFoodType(){return make_pair(foodType, WORM);}
};
class MovingFood : public Food{
private:
    int _speed;
    Direction dir;
    SpecialFood foodType;
public:
    MovingFood(int x, int y, int value, int size, int speed,Direction dir,SpecialFood specialFood):_speed(speed),dir(dir),foodType(specialFood),Food(x,y,value,size,true){};
    pair<NormalFood,SpecialFood> getFoodType(){return make_pair(BANANA, foodType);}
    
};