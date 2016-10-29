
#include "Board.hpp"
#include <list>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;

/////////////////BOARD////////////////////////////
Board::Board(int boardWidth,int boardHeight,int snakeSize) :width(boardWidth),height(boardHeight){
    snake = new Snake(snakeSize);
    this->placeFood(1,snakeSize,0,false);
}
void Board::placeFood(int value, int size, int speed,bool specialFood){
    int x = rand()%width;
    int y = rand()%height;
    while (snake->foodCanNotBeHere(x,y,size) || x+size>width || y+size>height){
        x = rand()%width;
        y = rand()%height;
    }
    Food* newFood;
    newFood = new Food(x,y,value,size,speed,specialFood);
    food.push_front(newFood);//MUST BE FRONT!
}
list<pair<int,int>> Board::getFoodCoord(){
    list<Food*>::iterator foodIt;
    list<pair<int,int>> retCoord;
    for(foodIt = food.begin(); foodIt!=food.end(); foodIt++){
        retCoord.push_back(make_pair((*foodIt)->getX(), (*foodIt)->getY()));
    }
    return retCoord;
}
void Board::moveSnake(list<Direction> &moveQueue){
    //checks if the turn is illegal:
    if (!moveQueue.empty() && snake->IllegalTurn(moveQueue.front())){
        moveQueue.pop_front();
        this->moveSnake(moveQueue);
        return;
    }
    //takes the different situations if we are moving forward or turning:
    if (moveQueue.empty()){//No Turning here:
        snake->straightForwardMove();
    }
    else{//Here we turn:
        snake->turnAndMove(moveQueue);
    }
    //check if we have eaten:
    this->didSnakeEat();
    //check if the snake should get longer or not:
    if (snake->getEatenFood()){
        snake->changeEatenFood(-1);
        snake->changeSnakeLength(1);
    }
    else{
        snake->removeLastTail();
    }
}

void Board::didSnakeEat(){
    list<Food*>::iterator foodIt;
    int x = snake->getSnakeHeadX();
    int y = snake->getSnakeHeadY();
    bool eaten = false;
    for(foodIt = food.begin(); foodIt != food.end(); foodIt++){
        if (x < (*foodIt)->getX() + (*foodIt)->getFoodSize() &&
            x + snake->getSnakeSize() > (*foodIt)->getX() &&
            y < (*foodIt)->getY()+ (*foodIt)->getFoodSize() &&
            y + snake->getSnakeSize() > (*foodIt)->getY()){
            snake->changeEatenFood((*foodIt)->getFoodValue());
            food.erase(foodIt);
            if(!(*foodIt)->isSpecialFood())
                eaten = true;
        }
    }
    if (eaten){
        this->placeFood(1,snake->getSnakeSize(),0,false);
    }
}

