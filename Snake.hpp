#pragma once
#include<list>
#include <utility>
#include <queue>
using namespace std;
class Snake;
enum Direction {RIGHT,LEFT,UP,DOWN};

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
    bool _eatenFood;
    
public:
    Snake(int snakeSize);
    bool IllegalTurn(Direction dir);
    void moveSnake(list<Direction> &moveQueue);
    pair<BodyPart*,list<BodyPart*>> getSnake(){return make_pair(snakeHead,snakeTail);};
    void removeLastTail();
    void straightForwardMove();
    void turnAndMove(list<Direction> &moveQueue);
    //getFunctions:
    pair<int,int> getSnakeHeadCoord();
    list<pair<int,int>> getSnakeTailCoord();
    
    void printSnakeStuff()const;
};
class Board : public Snake{
private:
    //The board:
    int width,height;
public:
    Board(int boardWidth,int boardHeight,int snakeSize);
};
void printStuff();

