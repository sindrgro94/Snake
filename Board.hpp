#pragma once
#include "Snake.hpp"
#include <list>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;
class Board{
private:
    int width,height;
    Snake* snake;
    list<Food*> food;
public:
    Board(int boardWidth,int boardHeight,int snakeSize);
    //Food:
    void placeFood(int value, int size, int speed,bool specialFood);
    list<pair<int,int>> getFoodCoord();
    list<Food*> getAllFood(){return food;}
    //Snake:
    
    //GetFunctions:
    //pair<BodyPart*,list<BodyPart*>>getSnake(){return snake->getSnake();}
    pair<int,int> getSnakeHeadCoord(){return snake->getSnakeHeadCoord();}
    list<pair<int,int>> getSnakeTailCoord(){return snake->getSnakeTailCoord();}
    Direction getSnakeHeadDirection(){return snake->getSnakeHeadDirection();}
    ///
    bool didSnakeCollide(int width,int height){return snake->didSnakeCollide(width, height);}
    void moveSnake(list<Direction> &moveQueue);
    void didSnakeEat();
    
    
};
