#include "Board.hpp"
#include <list>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;

/////////////////BOARD////////////////////////////
Board::Board(int boardWidth,int boardHeight,int snakeSize) :width(boardWidth),height(boardHeight){
    snake = new Snake(snakeSize);
    this->placeFood(snakeSize,false);
}
void Board::placeFood(int size, bool specialFood){
    int x = rand()%width;
    int y = rand()%height;
    while (snake->foodCanNotBeHere(x,y,size) || x+size>width || y+size>height){
        x = rand()%width;
        y = rand()%height;
    }
    Food* newFood;
    if (specialFood){
        SpecialFood specFood;
        int speed;
        int value;
        int foodNum = rand()%11;
        if(foodNum<=4){
            specFood = WORM;
            speed = 1;
            value = 5;
        }
        else if (foodNum<=7) {
            specFood = GREYMOUSE;
            speed = 5;
            value = 7;
        }
        else if (foodNum<=9) {
            specFood = WHITEMOUSE;
            speed = 5;
            value = 10;
        }
        else {
            specFood = FROG;
            speed = 10;
            value = 20;
        }
        newFood = new MovingFood(x,y,value,size,speed,RIGHT,specFood);
    }
    else{
        NormalFood normalFood;
        int foodNum = rand()%4;
        switch(foodNum){
            case BANANA:
                normalFood = BANANA;
                break;
            case APPLE:
                normalFood = APPLE;
                break;
            case ORANGE:
                normalFood = ORANGE;
                break;
            case PEAR:
                normalFood = PEAR;
                break;
        }
        newFood = new StationaryFood(x,y,2,size,normalFood);//2 is value
    }
    food.push_front(newFood);//MUST BE FRONT!
}
list<pair<int,int>> Board::getFoodCoord(bool specialFood){
    list<Food*>::iterator foodIt;
    list<pair<int,int>> retCoord;
    for(foodIt = food.begin(); foodIt!=food.end(); foodIt++){
        if((*foodIt)->isSpecialFood()==specialFood)
            retCoord.push_back(make_pair((*foodIt)->getX(), (*foodIt)->getY()));
    }
    return retCoord;
}
list<Direction> Board::getFoodDir(){
    list<Food*>::iterator foodIt;
    list<Direction> foodDir;
    for(foodIt = food.begin(); foodIt!=food.end(); foodIt++){
        if((*foodIt)->isSpecialFood()==true)
            foodDir.push_back((*foodIt)->getDir());
    }
    return foodDir;
}
pair<list<NormalFood>,list<SpecialFood> > Board::getFoodTypes(){
    list<Food*>::iterator foodIt;
    list<SpecialFood> foodTypesS;
    list<NormalFood> foodTypesN;
    for(foodIt = food.begin(); foodIt!=food.end(); foodIt++){
        if((*foodIt)->isSpecialFood()){
            foodTypesS.push_back((*foodIt)->getFoodType().second);
        }
        else{
            foodTypesN.push_back((*foodIt)->getFoodType().first);
        }
    }
    return make_pair(foodTypesN, foodTypesS);
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
        this->placeFood(snake->getSnakeSize(), false);
    }
}

