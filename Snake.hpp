#pragma once
#include "BodyPart.hpp"
#include "Food.hpp"
#include <list>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;

class Snake{
private:
    //snake<width,height>
    BodyPart* snakeHead;
    list<BodyPart*> snakeTail;
    int _snakeSize;
    int _snakeLength;
    int _eatenFood;
    
public:
    Snake(int snakeSize);
    bool IllegalTurn(Direction dir);
    pair<BodyPart*,list<BodyPart*>> getSnake(){return make_pair(snakeHead,snakeTail);};
    void removeLastTail();
    void straightForwardMove();
    void turnAndMove(list<Direction> &moveQueue);
    //getFunctions:
    int getSnakeHeadX(){return snakeHead->getX();}
    int getSnakeHeadY(){return snakeHead->getY();}
    Direction getSnakeHeadDirection();
    pair<int,int> getSnakeHeadCoord();
    list<pair<int,int>> getSnakeTailCoord();
    list<pair<int,int>> getSnakeTailCoordAndDir(list<pair<Direction,Direction>> &dir);
    int getSnakeSize(){return _snakeSize;}
    int getEatenFood(){return _eatenFood;}
    //ChangeFunctions:
    void changeEatenFood(int value){_eatenFood += value;}
    void changeSnakeLength(int value){_snakeLength += value;}
    ////////
    bool didSnakeCollide(int boardWidth,int boardHeight);
    bool foodCanNotBeHere(int x,int y,int foodSize);
    void printSnakeStuff()const;
};
void printStuff(Food* food);

