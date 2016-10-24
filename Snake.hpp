#pragma once
#include<list>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;
class Snake;
enum Direction {RIGHT,LEFT,UP,DOWN};

class Food{
private:
    int _x,_y;
    int _value;
    int _size;
    int _speed;
    bool _specialFood;
public:
    Food(int x, int y, int value, int size, int speed,bool specialFood);
    ~Food(){cout<<"Destruktør kalt"<<endl;}
    //getFunctions:
    int getY(){return _y;}
    int getX(){return _x;}
    int getFoodSize(){return _size;}
    int getFoodValue(){return _value;}
    bool isSpecialFood(){return _specialFood;}
    
};

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
    pair<int,int> getSnakeHeadCoord();
    list<pair<int,int>> getSnakeTailCoord();
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
class Board : public Snake{
private:
    //The board:
    int width,height;
    list<Food*> food;
public:
    Board(int boardWidth,int boardHeight,int snakeSize);
    //Food:
    void placeFood(int value, int size, int speed,bool specialFood);
    list<pair<int,int>> getFoodCoord();
    list<Food*> getAllFood(){return food;}
    //Snake:
    void moveSnake(list<Direction> &moveQueue);
    void didSnakeEat();
    
    
};
void printStuff(Food* food);

