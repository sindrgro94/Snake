//#pragma once
#ifndef BodyPart_hpp
#define BodyPart_hpp
#include "Food.hpp"
#include <list>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;
class BodyPart{
private:
    int _x,_y;
    pair<Direction,Direction> _dir;
    bool _isLast;
public:
    BodyPart(pair<Direction,Direction> dir,int y,int col,bool isLast);
    //getFunctions:
    int getY(){return _y;}
    int getX(){return _x;}
    pair<Direction,Direction> getDir(){return _dir;}
    bool isLast(){return _isLast;}
    //setFunctions:
    void setLast(){_isLast = true;}
    void changeY(int change){_y += change;}
    void changeX(int change){_x += change;}
    void changeDir(pair<Direction,Direction> dir){_dir = dir;}
    
};

#endif