#pragma once
#include<list>
#include <utility>
#include <queue>
using namespace std;
class Snake;
enum Direction {RIGHT,LEFT,UP,DOWN};

class BodyPart{
private:
    int _row,_column;
    int** body;
    int bodySize;
    list<Direction> DirectionList;
    Direction snakeHeadDirection;
    bool isLast;
public:
    friend Snake;
    BodyPart(int size,Direction dir,int col,int row);
    BodyPart(int size,Direction dir,int col,int row,bool isLast);
    ~BodyPart();
    bool allFilled()const;
    bool allEmpty()const;
    //filling with a direction:
    void fillAll(Direction dir);
    //returns true if the specific row/col is empty:
    bool isRowEmpty(int row)const;
    bool isColEmpty(int col)const;
    //returns true if allEmpty:
    bool emptyRow(int row);
    bool emptyCol(int col);
    //returns true if allFilled:
    bool fillRow(int row,Direction dir);
    bool fillCol(int col,Direction dir);
    //returns true if bodyPart is empty/full:
    bool removeAPart();
    bool addAPart(Direction dir);
    bool addAPart(Direction dir, Direction newDir);
    //getFunctions:
    int getRow()const{return _row;}
    int getColumn()const{return _column;}
    bool snakeIsHere(int row,int col)const;
};


class Snake{
private:
    //snake<width,height>
    BodyPart* snakeHead;
    list<BodyPart*> snakeTail;
    int snakeSize;
    int snakeLength;
    list<int> eatenFood;
    
public:
    Snake(int snakeSize);
    bool IllegalTurn(Direction dir);
    void moveSnake(list<Direction> &moveQueue);
    pair<BodyPart*,list<BodyPart*>> getSnake(){return make_pair(snakeHead,snakeTail);};
    void removeLastTail();
    void straightForwardMove();
    void turnAndMove(list<Direction> &moveQueue);
    BodyPart* prepareForTurn(Direction newDir);
    BodyPart* makeTurnBodyPart(Direction dir, Direction newDir);
    
    void printStuff()const;
};
class Board : public Snake{
private:
    //The board:
    int width,height;
public:
    Board(int boardWidth,int boardHeight,int snakeSize);
};

