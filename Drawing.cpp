#include "Drawing.hpp"
#include <SFML/Graphics.hpp>
#include <utility>
using namespace std;

void drawSnakeHead(sf::RenderWindow &window,bool havePicture, Board board, sf::Sprite snakeHead,sf::Color snakeHead_color){
    int snakeSize = board.getSnakeSize();
    sf::RectangleShape part(sf::Vector2f(snakeSize,snakeSize));
    pair<int,int> snakeHeadCoord = board.getSnakeHeadCoord();
    if(!havePicture){
        part.setFillColor(snakeHead_color);
        part.setPosition(snakeHeadCoord.first,snakeHeadCoord.second);
        window.draw(part);
    }
    else{
        snakeHead.setTextureRect(sf::IntRect(0,board.getSnakeHeadDirection()*snakeSize,snakeSize,snakeSize));
        snakeHead.setPosition(snakeHeadCoord.first, snakeHeadCoord.second);
        window.draw(snakeHead);
    }

}
void drawSnakeTail(sf::RenderWindow &window,bool haveSnakeTail,bool haveEndTail,Board board,sf::Sprite snakeTail,sf::Sprite endTail,sf::Color snakeTail_color){
    
    int snakeSize = board.getSnakeSize();
    list<pair<int,int> > coordinates;
    list<pair<Direction,Direction>> dir;
    coordinates = board.getSnakeTailCoordAndDir(dir);
    list<pair<int,int> >::iterator coordinatesIt;
    if (!haveSnakeTail) {
        sf::RectangleShape part(sf::Vector2f(snakeSize,snakeSize));
        part.setFillColor(snakeTail_color);
        for(coordinatesIt = coordinates.begin(); coordinatesIt!=coordinates.end(); coordinatesIt++){
            part.setPosition(coordinatesIt->first, coordinatesIt->second);
            window.draw(part);
        }
    }
    else{
        list<pair<Direction,Direction>>::iterator dirIt;
        coordinatesIt = coordinates.begin();
        for(dirIt = dir.begin(); dirIt!=dir.end(); dirIt++){
            snakeTail.setPosition(coordinatesIt->first,coordinatesIt->second);
            if (dirIt->first == dirIt->second){
                snakeTail.setTextureRect(sf::IntRect(0,dirIt->first*snakeSize,snakeSize,snakeSize));
            }
            else{
                if (dirIt->first<2){
                    snakeTail.setTextureRect(sf::IntRect((dirIt->second-1)*snakeSize,dirIt->first*snakeSize,snakeSize,snakeSize));
                }
                else{
                  snakeTail.setTextureRect(sf::IntRect((dirIt->second+1)*snakeSize,dirIt->first*snakeSize,snakeSize,snakeSize));
                }
            }
            
            //If we are at the last tail:
            endTail.setPosition(coordinatesIt->first,coordinatesIt->second);
            //tempCoord = make_pair(coordinatesIt->first, coordinatesIt->second);
            if(++coordinatesIt == coordinates.end() && haveEndTail){
                if (dirIt->first == dirIt->second){
                    endTail.setTextureRect(sf::IntRect(0,dirIt->first*snakeSize,snakeSize,snakeSize));
                }
                else{
                    if (dirIt->first<2){
                        endTail.setTextureRect(sf::IntRect((dirIt->second-1)*snakeSize,dirIt->first*snakeSize,snakeSize,snakeSize));
                    }
                    else{
                        endTail.setTextureRect(sf::IntRect((dirIt->second+1)*snakeSize,dirIt->first*snakeSize,snakeSize,snakeSize));
                    }
                }
                window.draw(endTail);
            }
            else{
                window.draw(snakeTail);
            }
            
        }
        
        
    }
}
void drawFood(sf::RenderWindow &window,bool haveNormalFood,bool haveSpecialFood, Board board, sf::Sprite normalFood, sf::Sprite specialFood,sf::Color foodColor){
    //////WARNING! CAN ONLY PRINT FOOD IN SIZE SNAKESIZE
    int snakeSize = board.getSnakeSize();
    sf::RectangleShape part(sf::Vector2f(snakeSize,snakeSize));
    part.setFillColor(foodColor);
    
    list<pair<int,int> > coordinates;
    list<pair<int,int> >::iterator coordinatesIt;
    
    pair<list<NormalFood>,list<SpecialFood>> foodTypes;
    list<NormalFood>::iterator foodTypeNIt;
    list<SpecialFood>::iterator foodTypeSIt;
    
    foodTypes = board.getFoodTypes();//<normal,special>
    // Stationary food:
    coordinates = board.getFoodCoord(false);//false for isSpecialFood()
    for(coordinatesIt = coordinates.begin(),foodTypeNIt = foodTypes.first.begin(); coordinatesIt!=coordinates.end(); coordinatesIt++,foodTypeNIt++){
        if(haveNormalFood){
            normalFood.setTextureRect(sf::IntRect(0,(*foodTypeNIt) * snakeSize,snakeSize,snakeSize));
            normalFood.setPosition(coordinatesIt->first, coordinatesIt->second);
            window.draw(normalFood);

        }
        else{
            part.setPosition(coordinatesIt->first, coordinatesIt->second);
            window.draw(part);
        }
    }
    
    //moving Food:
    coordinates = board.getFoodCoord(true);//true for isSpecialFood()
    list<Direction> FoodDir = board.getFoodDir();
    list<Direction>::iterator FoodDirIt;
    for(coordinatesIt = coordinates.begin(),foodTypeSIt = foodTypes.second.begin(),FoodDirIt = FoodDir.begin(); coordinatesIt!=coordinates.end(); coordinatesIt++,foodTypeSIt++,FoodDirIt++){
        if(haveSpecialFood){
            specialFood.setTextureRect(sf::IntRect(0 * (*FoodDirIt),(*foodTypeSIt) * snakeSize,snakeSize,snakeSize));
            specialFood.setPosition(coordinatesIt->first, coordinatesIt->second);
            window.draw(specialFood);
        }
        else{
            part.setPosition(coordinatesIt->first, coordinatesIt->second);
            window.draw(part);
        }
    }
}