#pragma once
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
    int _speed;
    bool _specialFood;
public:
    Food(int x, int y, int value, int size, int speed,bool specialFood);
    //getFunctions:
    int getY(){return _y;}
    int getX(){return _x;}
    int getFoodSize(){return _size;}
    int getFoodValue(){return _value;}
    bool isSpecialFood(){return _specialFood;}
    
};