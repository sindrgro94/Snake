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
    int infoBarSize,edgeSize;
    Snake* snake;
    list<Food*> food;
public:
    Board(int boardWidth,int boardHeight,int snakeSize, int infoBarSize, int EdgeSize);
    //Food:
    void placeFood(int size, bool specialFood);
    list<pair<int,int>> getFoodCoord(bool specialFood);
    list<Direction> getFoodDir();
    pair<list<NormalFood>,list<SpecialFood> > getFoodTypes();
    
    //GetFunctions:
    pair<int,int> getSnakeHeadCoord(){return snake->getSnakeHeadCoord();}
    list<pair<int,int>> getSnakeTailCoordAndDir(list<pair<Direction,Direction>> &dir){return snake->getSnakeTailCoordAndDir(dir);}
    Direction getSnakeHeadDirection(){return snake->getSnakeHeadDirection();}
    int getSnakeSize(){return snake->getSnakeSize();}
    int getSnakePoints();
    ///
    bool didSnakeCollide(int width,int height, int infoBar, int edgeSize){return snake->didSnakeCollide(width, height, infoBar, edgeSize);}
    void moveSnake(list<Direction> &moveQueue);
    void didSnakeEat();
    
    
};
