#include <iostream>
#include "Images.hpp"

using namespace std;
Images::Images(){
    /////////Loading images:////////////////////
    
    //SnakeHead:
    if(!snakeHeadImage.loadFromFile("snakeHead.png")){
        cout<<"Could not load snake head image."<<endl;
        haveSnakeHead = false;
    }
    snakeHead.setTexture(snakeHeadImage);
    //SnakeTail:
    if(!snakeTailImage.loadFromFile("snakeTailTest.png")){
        cout<<"Could not load snake tail image"<<endl;
        haveSnakeTail = false;
    }
    snakeTail.setTexture(snakeTailImage);
    //EndTail:
    if(!endTailImage.loadFromFile("endTailTest.png")){
        cout<<"Could not load end tail image"<<endl;
        haveEndTail = false;
    }
    endTail.setTexture(endTailImage);
    //NormalFood:
    if(!normalFoodImage.loadFromFile("normalFoodTest.png")){
        cout<<"Could not load normal food image"<<endl;
        haveNormalFood = false;
    }
    normalFood.setTexture(normalFoodImage);
    //SpecialFood:
    if(!specialFoodImage.loadFromFile("specialFoodTest.png")){
        cout<<"Could not load special food image"<<endl;
        haveSpecialFood = false;
    }
    specialFood.setTexture(specialFoodImage);
    //Wall:
    if(!wallImage.loadFromFile("wall.png")){
        cout<<"Could not load wall image"<<endl;
        haveWall = false;
    }
    wall.setTexture(wallImage);

}