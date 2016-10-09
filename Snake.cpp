#include "snake.hpp"
#include <list>
#include <utility>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;
/////////////////BODYPART////////////////////////////
BodyPart::BodyPart(int size,Direction dir,int col,int row):bodySize(size),_row(row),_column(col),snakeHeadDirection(dir){
    isLast = false;
    body = new int*[bodySize];
    for(int row = 0; row<bodySize; row++){
        body[row] = new int[bodySize];
    }
    for (int row = 0; row<bodySize; row++){
        for(int col = 0; col<bodySize; col++){
            body[row][col] = 0;
        }
    }
}
BodyPart::BodyPart(int size,Direction dir,int col,int row,bool isLast):bodySize(size),_row(row),_column(col),snakeHeadDirection(dir),isLast(isLast){
    body = new int*[bodySize];
    for(int row = 0; row<bodySize; row++){
        body[row] = new int[bodySize];
    }
    for (int row = 0; row<bodySize; row++){
        for(int col = 0; col<bodySize; col++){
            body[row][col] = 0;
        }
    }
}
BodyPart::~BodyPart(){
    for (int row = 0; row<bodySize; row++){
        delete [] body[row];
    }
    delete[] body;
    //cout<<"Destruktør er kalt!"<<endl;
    //cout<<DirectionList.size()<<endl;
}
bool BodyPart::allFilled()const{
    for(int row = 0; row<bodySize;row++){
        for (int col = 0; col<bodySize;col++){
            if(body[row][col] == 0){
                return false;
            }
        }
    }
    return true;
}
bool BodyPart::allEmpty()const{
    for(int row = 0; row<bodySize;row++){
        for (int col = 0; col<bodySize;col++){
            if(body[row][col] == 1){
                return false;
            }
        }
    }
    return true;
}
void BodyPart::fillAll(Direction dir){
    for(int row = 0; row<bodySize;row++){
        DirectionList.push_front(dir);
        for (int col = 0; col<bodySize;col++){
            body[row][col] = 1;
        }
    }
}
bool BodyPart::isRowEmpty(int row)const{
    for(int col = 0; col<bodySize;col++){
        if (body[row][col]==1)
            return false;
    }
    return true;
}
bool BodyPart::isColEmpty(int col)const{
    for(int row = 0; row<bodySize;row++){
        if (body[row][col]==1)
            return false;
    }
    return true;
}
bool BodyPart::emptyRow(int row){
    for(int col=0; col<bodySize;col++){
        body[row][col] = 0;
    }
    if (allEmpty())
        return true;
    return false;
}
bool BodyPart::emptyCol(int col){
    for(int row=0; row<bodySize;row++){
        body[row][col] = 0;
    }
    if (allEmpty())
        return true;
    return false;
}
bool BodyPart::fillRow(int row,Direction dir){
    for(int col=0; col<bodySize;col++){
        if (col == 0 || dir!=snakeHeadDirection){
            DirectionList.push_back(dir);
        }
        body[row][col] = 1;
    }
    if (allFilled())
        return true;
    return false;
}
bool BodyPart::fillCol(int col,Direction dir){
    for(int row=0; row<bodySize;row++){
        if (row == 0 || dir!=snakeHeadDirection){
            DirectionList.push_back(dir);
        }
        body[row][col] = 1;
    }
    if (allFilled())
        return true;
    return false;
}
bool BodyPart::removeAPart(){
    int RowOrCol;
    switch (DirectionList.front()) {
        case UP:
            DirectionList.pop_front();
            RowOrCol = bodySize-1;
            while (this->isRowEmpty(RowOrCol))
                RowOrCol--;
            return this->emptyRow(RowOrCol);
            break;
        case DOWN:
            DirectionList.pop_front();
            RowOrCol = 0;
            while (this->isRowEmpty(RowOrCol))
                RowOrCol++;
            return this->emptyRow(RowOrCol);
            break;
        case LEFT:
            DirectionList.pop_front();
            RowOrCol = bodySize-1;
            while (this->isColEmpty(RowOrCol))
                RowOrCol--;
            return this->emptyCol(RowOrCol);
            break;
        case RIGHT:
            DirectionList.pop_front();
            RowOrCol = 0;
            while (this->isColEmpty(RowOrCol))
                RowOrCol++;
            return this->emptyCol(RowOrCol);
            break;
        default:
            cout<<"Feil i DirectionList"<<endl;
    }
}
bool BodyPart::addAPart(Direction dir){
    int RowOrCol;
    switch (dir) {
        case UP:
            RowOrCol = bodySize-1;
            while (!this->isRowEmpty(RowOrCol))
                RowOrCol--;
            return this->fillRow(RowOrCol,dir);
            break;
        case DOWN:
            RowOrCol = 0;
            while (!this->isRowEmpty(RowOrCol))
                RowOrCol++;
            return this->fillRow(RowOrCol,dir);
            break;
        case LEFT:
            RowOrCol = bodySize-1;
            while (!this->isColEmpty(RowOrCol)){
                RowOrCol--;
            }
            return this->fillCol(RowOrCol,dir);
            break;
        case RIGHT:
            RowOrCol = 0;
            while (!this->isColEmpty(RowOrCol)){
                RowOrCol++;
            }
            return this->fillCol(RowOrCol,dir);
            break;
            
    }
}
bool BodyPart::addAPart(Direction dir, Direction newDir){
    int RowOrCol;
    switch (dir) {
        case UP:
            RowOrCol = bodySize-1;
            while (!this->isRowEmpty(RowOrCol))
                RowOrCol--;
            return this->fillRow(RowOrCol,newDir);
            break;
        case DOWN:
            RowOrCol = 0;
            while (!this->isRowEmpty(RowOrCol))
                RowOrCol++;
            return this->fillRow(RowOrCol,newDir);
            break;
        case LEFT:
            RowOrCol = bodySize-1;
            while (!this->isColEmpty(RowOrCol)){
                RowOrCol--;
            }
            return this->fillCol(RowOrCol,newDir);
            break;
        case RIGHT:
            RowOrCol = 0;
            while (!this->isColEmpty(RowOrCol)){
                RowOrCol++;
            }
            return this->fillCol(RowOrCol,newDir);
            break;
            
    }
}
bool BodyPart::snakeIsHere(int row,int col)const{
    if (body[row][col]==1){
        return true;
    }
    return false;
}


/////////////////SNAKE////////////////////////////
Snake::Snake(int snakeSize) : snakeSize(snakeSize),snakeLength(5){//Standard inital Values: length=5, direction=Right
    
    snakeHead = new BodyPart(snakeSize,RIGHT,100+snakeSize,100);
    int startWidth = 100;
    int startHeight = 100;
    snakeHead->fillAll(RIGHT);
    BodyPart* bodypart;
    for(int part = 0; part<snakeLength; part++){
        bodypart = new BodyPart(snakeSize,RIGHT,startWidth-part*snakeSize,startHeight);
        bodypart->fillAll(RIGHT);
        
        snakeTail.push_back(bodypart);
    }
    bodypart =new BodyPart(snakeSize,RIGHT,startWidth+snakeSize,startHeight);
    snakeTail.push_front(bodypart);
    //Making the head:
}
bool Snake::IllegalTurn(Direction dir){
    switch(dir){
        case UP:
            if(snakeHead->snakeHeadDirection==DOWN||snakeHead->snakeHeadDirection==UP)
                return true;
            break;
        case DOWN:
            if(snakeHead->snakeHeadDirection==DOWN||snakeHead->snakeHeadDirection==UP)
                return true;
            break;
        case LEFT:
            if(snakeHead->snakeHeadDirection==LEFT||snakeHead->snakeHeadDirection==RIGHT)
                return true;
            break;
        case RIGHT:
            if(snakeHead->snakeHeadDirection==LEFT||snakeHead->snakeHeadDirection==RIGHT)
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
    if (eatenFood.front() == snakeSize)
        eatenFood.pop_front();
    if (eatenFood.empty()){
        this->removeLastTail();
    }
    else{
        eatenFood.front()++;
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
    bool removeBodyPart;
    removeBodyPart = snakeTail.back()->removeAPart();
    if (removeBodyPart){
        delete snakeTail.back();
        snakeTail.pop_back();
    }
    
}
void Snake::straightForwardMove(){
    int MakeANewTail;
    //change the position of the head and replace with tail:
    MakeANewTail = snakeTail.front()->addAPart(snakeHead->snakeHeadDirection);
    switch(snakeHead->snakeHeadDirection){
        case UP:
            snakeHead->_row--;
            break;
        case DOWN:
            snakeHead->_row++;
            break;
        case LEFT:
            snakeHead->_column--;
            break;
        case RIGHT:
            snakeHead->_column++;
            break;
    }
    if (MakeANewTail){
        snakeTail.push_front(new BodyPart(snakeSize,snakeHead->snakeHeadDirection,snakeHead->_column,snakeHead->_row));
    }
    
}
void Snake::turnAndMove(list<Direction> &moveQueue){
    //delete tail:
    for(int i = 0; i<snakeSize; i++){
        this->removeLastTail();
    }
    /////
    BodyPart* turnBody;
    this->printStuff();
    turnBody = this->prepareForTurn(moveQueue.front());
    snakeTail.push_front(turnBody);
    this->printStuff();
    switch(moveQueue.front()){
        case UP:
            snakeHead->_row -= snakeSize;
            snakeHead->snakeHeadDirection = UP;
            break;
        case DOWN:
            snakeHead->_row += snakeSize;
            snakeHead->snakeHeadDirection = DOWN;
            break;
        case LEFT:
            snakeHead->_column -= snakeSize;
            snakeHead->snakeHeadDirection = LEFT;
            break;
        case RIGHT:
            snakeHead->_column += snakeSize;
            snakeHead->snakeHeadDirection = RIGHT;
            break;
    }
    turnBody = new BodyPart(snakeSize,moveQueue.front(),snakeHead->_column,snakeHead->_row);
    snakeTail.push_front(turnBody);
    moveQueue.pop_front();
}
BodyPart* Snake::prepareForTurn(Direction newDir){
    BodyPart* turnBodyPart;
    switch (snakeHead->snakeHeadDirection){
        case UP:
            while (snakeTail.front()->addAPart(UP,newDir)){}
            turnBodyPart = this->makeTurnBodyPart(UP,newDir);
            break;
        case DOWN:
            while (snakeTail.front()->addAPart(DOWN,newDir)){}
            turnBodyPart = this->makeTurnBodyPart(DOWN,newDir);
            break;
        case LEFT:
            while (snakeTail.front()->addAPart(LEFT,newDir)){}
            turnBodyPart = this->makeTurnBodyPart(LEFT,newDir);
            break;
        case RIGHT:
            while (snakeTail.front()->addAPart(RIGHT,newDir)){}
            turnBodyPart = this->makeTurnBodyPart(RIGHT,newDir);
            break;
    }
    this->printStuff();
    return turnBodyPart;
}
BodyPart* Snake::makeTurnBodyPart(Direction dir, Direction newDir){
    BodyPart* turnBodyPart;
    int numToFill;
    switch(dir){
        case UP:
            turnBodyPart = new BodyPart(snakeSize,newDir,snakeHead->_column,snakeHead->_row,true);
            numToFill = snakeHead->_row-turnBodyPart->_row;
            for (int row = 0; row<numToFill; row++){
                turnBodyPart->addAPart(UP,newDir);
            }
            break;
        case DOWN:
            turnBodyPart = new BodyPart(snakeSize,newDir,snakeTail.front()->_column,snakeTail.front()->_row+snakeSize,true);
            numToFill = turnBodyPart->_row-snakeHead->_row;
            for (int row = 0; row<numToFill; row++){
                turnBodyPart->addAPart(DOWN,newDir);
            }
            break;
        case LEFT:
            turnBodyPart = new BodyPart(snakeSize,newDir,snakeTail.front()->_column-snakeSize,snakeTail.front()->_row,true);
            numToFill = snakeHead->_column-turnBodyPart->_column;
            for (int col = 0; col<numToFill; col++){
                turnBodyPart->addAPart(LEFT,newDir);
            }
            break;
        case RIGHT:
            turnBodyPart = new BodyPart(snakeSize,newDir,snakeTail.front()->_column+snakeSize,snakeTail.front()->_row,true);
            numToFill = turnBodyPart->_column-snakeHead->_column;
            for (int col = 0; col<numToFill; col++){
                turnBodyPart->addAPart(RIGHT,newDir);
            }
            break;
    }
    return turnBodyPart;
}

void Snake::printStuff()const{
    for(int row = 0; row<snakeSize; row++){
        for(int col = 0; col<snakeSize; col++){
            cout<<snakeTail.front()->body[row][col]<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    /*list<BodyPart*>::const_iterator it;
     cout<<"snakeHead:"<<endl;
     cout<<snakeHead->_row<<" "<<snakeHead->_column<<endl;
     for (int row = 0; row<snakeSize; row++){
     for(int col = 0; col<snakeSize; col++){
     cout<<snakeHead->body[row][col]<<" ";
     }
     cout<<endl;
     }
     cout<<endl<<endl;
     int i  = 1;
     for (it = snakeTail.begin();it!=snakeTail.end();it++){
     cout<<(*it)->_row<<" "<<(*it)->_column<<endl;
     for (int row = 0; row<snakeSize; row++){
     for(int col = 0; col<snakeSize; col++){
     cout<<(*it)->body[row][col]<<" ";
     }
     cout<<endl;
     }
     cout<<endl<<endl;
     i++;
     }*/
}
/////////////////BOARD////////////////////////////
Board::Board(int boardWidth,int boardHeight,int snakeSize) :width(boardWidth),height(boardHeight),Snake(snakeSize){}
