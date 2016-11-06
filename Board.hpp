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
    list<Food*> getAllFood(){return food;}//finn en annen løsning
    //Snake:
    
    //GetFunctions:
    //pair<BodyPart*,list<BodyPart*>>getSnake(){return snake->getSnake();}
    pair<int,int> getSnakeHeadCoord(){return snake->getSnakeHeadCoord();}
    list<pair<int,int>> getSnakeTailCoordAndDir(list<pair<Direction,Direction>> &dir){return snake->getSnakeTailCoordAndDir(dir);}
    Direction getSnakeHeadDirection(){return snake->getSnakeHeadDirection();}
    int getSnakeSize(){return snake->getSnakeSize();}
    ///
    bool didSnakeCollide(int width,int height){return snake->didSnakeCollide(width, height);}
    void moveSnake(list<Direction> &moveQueue);
    void didSnakeEat();
    
    
};
