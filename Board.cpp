#include "Board.hpp"
#include <list>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;

/////////////////BOARD////////////////////////////
Board::Board(int boardWidth,int boardHeight,int snakeSize, int infoBarSize, int edgeSize) :width(boardWidth),height(boardHeight),infoBarSize(infoBarSize),edgeSize(edgeSize),snakeSize(snakeSize){
    snake = new Snake(snakeSize, 1);
    this->placeFood(snakeSize,false);
}
void Board::reset(){
    delete snake;
    snake = new Snake(snakeSize,1);
    food.clear();
    this->placeFood(snakeSize, false);
}
/////////////////FOOD////////////////////////////
void Board::placeFood(int size, bool specialFood){
    Food* newFood;
    int x = rand()%width+edgeSize;
    int y = rand()%height+edgeSize;
    while (snake->foodCanNotBeHere(x,y,size) || x+size>width+edgeSize || y+size>height+edgeSize){
        x = rand()%width+edgeSize;
        y = rand()%height+edgeSize;
    }
    if (specialFood){
        SpecialFood specFood;
        int speed;
        int value;
        int foodNum = rand()%11;
        if(foodNum<=4){
            specFood = WORM;
            speed = 10;
            value = 5;
        }
        else if (foodNum<=6) {
            specFood = GREYMOUSE;
            speed = 20;
            value = 7;
        }
        else if (foodNum<=8) {
            specFood = WHITEMOUSE;
            speed = 20;
            value = 10;
        }
        else {
            specFood = FROG;
            speed = 35;
            value = 20;
        }
        int direction = rand()%4;
        Direction dir;
        switch (direction){
            case RIGHT:
                dir = RIGHT;
                x = 0;
                break;
            case LEFT:
                dir = LEFT;
                x = width;
                break;
            case UP:
                dir = UP;
                y = height;
                break;
            case DOWN:
                dir = DOWN;
                y = 0;
                break;
        }
        newFood = new MovingFood(x,y,value,size,speed,dir,specFood);
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

/////////////////SNAKE////////////////////////////
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
    //moveFood:
    list<Food*>::iterator foodIt;
    for(foodIt = food.begin(); foodIt != food.end(); foodIt++){
        if((*foodIt)->isSpecialFood()){
            (*foodIt)->moveFood();
            int x = (*foodIt)->getX();
            int y = (*foodIt)->getY();
            if (x<0 || x>width || y<0 || y>height){
                food.erase(foodIt);
            }
        }
        
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
    bool newFood = false;
    bool specialFoodExist = false;
    for(foodIt = food.begin(); foodIt != food.end(); foodIt++){
        if((*foodIt)->isSpecialFood()){
            specialFoodExist = true;
        }
        if (x < (*foodIt)->getX() + (*foodIt)->getFoodSize() &&
            x + snake->getSnakeSize() > (*foodIt)->getX() &&
            y < (*foodIt)->getY()+ (*foodIt)->getFoodSize() &&
            y + snake->getSnakeSize() > (*foodIt)->getY()){
            
            snake->changeEatenFood((*foodIt)->getFoodValue());
            snake->updateScore((*foodIt)->getFoodValue());
            food.erase(foodIt);
            if(!(*foodIt)->isSpecialFood()){
                newFood = true;
            }
            else{
                specialFoodExist = false;
            }
        }
    }
    if (newFood){
        this->placeFood(snake->getSnakeSize(), false);
    }
    if(!specialFoodExist){
        int newSpecialFood = rand()%100;
        if (newSpecialFood<100){//number represents percent chance for special food
            this->placeFood(snake->getSnakeSize(), true);
        }
    }
}
int Board::getSnakePoints(){
    return snake->getScore();
}
