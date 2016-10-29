#include "Snake.hpp"
#include <list>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;

/////////////////SNAKE////////////////////////////
Snake::Snake(int snakeSize) : _snakeSize(snakeSize),_snakeLength(5),_eatenFood(0){
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
Direction Snake::getSnakeHeadDirection(){
    return (snakeHead->getDir()).first;
}
pair<int,int> Snake::getSnakeHeadCoord(){
    return make_pair(snakeHead->getX(), snakeHead->getY());
}
list<pair<int,int>> Snake::getSnakeTailCoord(){
    list<BodyPart*>::iterator snakeTailIt;
    list<pair<int,int>> retCoord;
    for(snakeTailIt = snakeTail.begin(); snakeTailIt!=snakeTail.end(); snakeTailIt++){
        retCoord.push_back(make_pair((*snakeTailIt)->getX(), (*snakeTailIt)->getY()));
    }
    return retCoord;
}
list<pair<int,int>> Snake::getSnakeTailCoordAndDir(list<pair<Direction,Direction>> &dir){
    list<BodyPart*>::iterator snakeTailIt;
    for(snakeTailIt = snakeTail.begin(); snakeTailIt!=snakeTail.end(); snakeTailIt++){
        dir.push_back((*snakeTailIt)->getDir());
    }
    list<pair<int,int>> retCoord;
    for(snakeTailIt = snakeTail.begin(); snakeTailIt!=snakeTail.end(); snakeTailIt++){
        retCoord.push_back(make_pair((*snakeTailIt)->getX(), (*snakeTailIt)->getY()));
    }
    return retCoord;
}
bool Snake::didSnakeCollide(int boardWidth,int boardHeight){
    int snakeHeadX = snakeHead->getX();
    int snakeHeadY = snakeHead->getY();
    if (snakeHeadX<0 || snakeHeadX+_snakeSize>boardWidth || snakeHeadY<0 ||snakeHeadY+_snakeSize>boardHeight)
        return true;
    list<pair<int,int>> snakeCoord = this->getSnakeTailCoord();
    list<pair<int,int>>::iterator coordIt;
    for(coordIt = snakeCoord.begin(); coordIt != snakeCoord.end(); coordIt++){
        if(snakeHeadX < coordIt->first+_snakeSize &&
           snakeHeadX+_snakeSize > coordIt->first &&
           snakeHeadY < coordIt->second+_snakeSize &&
           snakeHeadY +_snakeSize > coordIt->second)
            return true;
    }
    return false;
}
bool Snake::foodCanNotBeHere(int x,int y, int foodSize){//Have to check for other food as well!!
    if(x < snakeHead->getX()+_snakeSize &&
       x+foodSize > snakeHead->getX() &&
       y < snakeHead->getY()+_snakeSize &&
       y +foodSize > snakeHead->getY())
        return true;

    list<pair<int,int>> snakeCoord = this->getSnakeTailCoord();
    list<pair<int,int>>::iterator coordIt;
    for(coordIt = snakeCoord.begin(); coordIt != snakeCoord.end(); coordIt++){
        if(x < coordIt->first+_snakeSize &&
           x+foodSize > coordIt->first &&
           y < coordIt->second+_snakeSize &&
           y +foodSize > coordIt->second)
            return true;
    }
    return false;

}


void Snake::printSnakeStuff()const{
    }
void printStuff(Food* food){
    cout<<"x-koordinat: "<<food->getX()<<", y-koordinat: "<<food->getY()<<endl;
}

