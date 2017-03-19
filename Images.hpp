//#pragma once
#ifndef Images_hpp
#define Images_hpp
#include "SFML/Graphics.hpp"
class Images{
private:
    sf::Texture snakeHeadImage;
    sf::Texture snakeTailImage;
    sf::Texture endTailImage;
    sf::Texture normalFoodImage;
    sf::Texture specialFoodImage;
    sf::Texture wallImage;
    
    sf::Sprite snakeHead;
    sf::Sprite snakeTail;
    sf::Sprite endTail;
    sf::Sprite normalFood;
    sf::Sprite specialFood;
    sf::Sprite wall;
    
    bool haveSnakeHead = true;
    bool haveSnakeTail = true;
    bool haveEndTail = true;
    bool haveNormalFood = true;
    bool haveSpecialFood = true;
    bool haveWall = true;
public:
    Images();
    
    sf::Sprite getSnakeHead(){return snakeHead;}
    sf::Sprite getSnakeTail(){return snakeTail;}
    sf::Sprite getEndTail(){return endTail;}
    sf::Sprite getNormalFood(){return normalFood;}
    sf::Sprite getSpecialFood(){return specialFood;}
    sf::Sprite getWall(){return wall;}
    
    bool getHaveSnakeHead(){return haveSnakeHead;}
    bool getHaveSnakeTail(){return haveSnakeTail;}
    bool getHaveEndTail(){return haveEndTail;}
    bool getHaveNormalFood(){return haveNormalFood;}
    bool getHaveSpecialFood(){return haveSpecialFood;}
    bool getHaveWall(){return haveWall;}

};
#endif