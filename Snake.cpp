#include "snake.hpp"
#include <list>
#include <utility>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;
/////////////////BODYPART////////////////////////////
BodyPart::BodyPart(pair<Direction,Direction> dir,int y,int x,bool isLast):_y(y),_x(x),_isLast(isLast),_dir(dir){}
/////////////////SNAKE////////////////////////////
Snake::Snake(int snakeSize) : _snakeSize(snakeSize),_snakeLength(5){
    //Standard inital Values: length=5, direction=Right
    int startY = 100;
    int startX = 100;
    snakeHead = new BodyPart(make_pair(RIGHT,RIGHT),startY,startX+snakeSize,false);
    BodyPart* bodypart;
    for(int part = 0; part<_snakeLength; part++){
        bodypart = new BodyPart(make_pair(RIGHT,RIGHT),startY,startX-part*snakeSize,false);
        snakeTail.push_back(bodypart);
    }
    snakeTail.back()->setLast();
}
bool Snake::IllegalTurn(Direction dir){
    switch(dir){
        case UP:
            if(snakeHead->getDir().first==DOWN||snakeHead->getDir().first==UP)
                return true;
            break;
        case DOWN:
            if(snakeHead->getDir().first==DOWN||snakeHead->getDir().first==UP)
                return true;
            break;
        case LEFT:
            if(snakeHead->getDir().first==LEFT||snakeHead->getDir().first==RIGHT)
                return true;
            break;
        case RIGHT:
            if(snakeHead->getDir().first==LEFT||snakeHead->getDir().first==RIGHT)
                return true;
            break;
    }
    return false;
}
void Snake::moveSnake(list<Direction> &moveQueue){
    //checks if the turn is illegal:
    if (!moveQueue.empty() && this->IllegalTurn(moveQueue.front())){
        moveQueue.pop_front();
        this->moveSnake(moveQueue);
        return;
    }
    //check if the snake should get longer or not:
    if (_eatenFood){
        _eatenFood = false;
        _snakeLength++;
    }
    else{
        this->removeLastTail();
    }
    //takes the different situations if we are moving forward or turning:
    if (moveQueue.empty()){//No Turning here:
        this->straightForwardMove();
    }
    else{//Here we make the turn:
        this->turnAndMove(moveQueue);
    }
}
void Snake::removeLastTail(){
    snakeTail.pop_back();
    snakeTail.back()->setLast();
    
}
void Snake::straightForwardMove(){
    switch(snakeHead->getDir().first){
        case UP:
            snakeTail.push_front(new BodyPart(make_pair(UP,UP),snakeHead->getY(),snakeHead->getX(),false));
            snakeHead->changeY(-_snakeSize);
            break;
        case DOWN:
            snakeTail.push_front(new BodyPart(make_pair(DOWN,DOWN),snakeHead->getY(),snakeHead->getX(),false));
            snakeHead->changeY(_snakeSize);
            break;
        case LEFT:
            snakeTail.push_front(new BodyPart(make_pair(LEFT,LEFT),snakeHead->getY(),snakeHead->getX(),false));
            snakeHead->changeX(-_snakeSize);
            break;
        case RIGHT:
            snakeTail.push_front(new BodyPart(make_pair(RIGHT,RIGHT),snakeHead->getY(),snakeHead->getX(),false));
            snakeHead->changeX(_snakeSize);
            break;
    }
}
void Snake::turnAndMove(list<Direction> &moveQueue){
    switch(moveQueue.front()){
        case UP:
            snakeTail.push_front(new BodyPart(make_pair(snakeHead->getDir().first,UP),snakeHead->getY(),snakeHead->getX(),false));
            snakeHead->changeY(-_snakeSize);
            snakeHead->changeDir(make_pair(UP,UP));
            break;
        case DOWN:
            snakeTail.push_front(new BodyPart(make_pair(snakeHead->getDir().first,DOWN),snakeHead->getY(),snakeHead->getX(),false));
            snakeHead->changeY(_snakeSize);
            snakeHead->changeDir(make_pair(DOWN,DOWN));
            break;
        case LEFT:
            snakeTail.push_front(new BodyPart(make_pair(snakeHead->getDir().first,LEFT),snakeHead->getY(),snakeHead->getX(),false));
            snakeHead->changeX(-_snakeSize);
            snakeHead->changeDir(make_pair(LEFT,LEFT));
            break;
        case RIGHT:
            snakeTail.push_front(new BodyPart(make_pair(snakeHead->getDir().first,RIGHT),snakeHead->getY(),snakeHead->getX(),false));
            snakeHead->changeX(_snakeSize);
            snakeHead->changeDir(make_pair(RIGHT,RIGHT));
            break;
    }
    moveQueue.pop_front();
}
pair<int,int> Snake::getSnakeHeadCoord(){
    return make_pair(snakeHead->getY(), snakeHead->getX());
}
list<pair<int,int>> Snake::getSnakeTailCoord(){
    list<BodyPart*>::iterator snakeTailIt;
    list<pair<int,int>> retCoord;
    for(snakeTailIt = snakeTail.begin(); snakeTailIt!=snakeTail.end(); snakeTailIt++){
        retCoord.push_back(make_pair((*snakeTailIt)->getY(), (*snakeTailIt)->getX()));
    }
    return retCoord;
}

void Snake::printSnakeStuff()const{
    cout<<snakeHead->getDir().first<<endl;
    }
/////////////////BOARD////////////////////////////
Board::Board(int boardWidth,int boardHeight,int snakeSize) :width(boardWidth),height(boardHeight),Snake(snakeSize){}

void printStuff(list<pair<int,int> > snakeTailCoords){
    list<pair<int,int> >::iterator snakeTailIt;
    for(snakeTailIt = snakeTailCoords.begin(); snakeTailIt!=snakeTailCoords.end(); snakeTailIt++){
        cout<<"x: "<<snakeTailIt->second<<", y: "<<snakeTailIt->first<<endl;
    }
}

