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
void drawWall(sf::RenderWindow &window,bool haveWall,sf::Sprite wall,int windowWidth,int windowHeight, int edgeSize, int infoBar){
    if(haveWall){
        //TOP:
        wall.setTextureRect(sf::IntRect(0, 4*edgeSize,edgeSize,edgeSize));
        for (int pos = 0; pos<=windowWidth/edgeSize;pos++){
            wall.setPosition(pos*edgeSize,0);
            window.draw(wall);
        }
        //BUTTOM:
        wall.setTextureRect(sf::IntRect(0,3*edgeSize,edgeSize,edgeSize));
        for (int pos = 0; pos<=windowWidth/edgeSize;pos++){
            wall.setPosition(pos*edgeSize,windowHeight-infoBar-edgeSize);
            window.draw(wall);
        }
        //LEFT:
        wall.setTextureRect(sf::IntRect(0,edgeSize,edgeSize,edgeSize));
        for (int pos = (windowHeight-edgeSize-infoBar)/edgeSize; pos>0;pos--){
            wall.setPosition(0,pos*edgeSize);
            window.draw(wall);
        }
        //RIGHT:
        wall.setTextureRect(sf::IntRect(0,2*edgeSize,edgeSize,edgeSize));
        for (int pos = (windowHeight-edgeSize-infoBar)/edgeSize; pos>0;pos--){
            wall.setPosition(windowWidth-edgeSize, pos*edgeSize);
            window.draw(wall);
        }
        //Corners:
        wall.setTextureRect(sf::IntRect(0,0,edgeSize,edgeSize));
        wall.setPosition(0,0);// upper left
        window.draw(wall);
        wall.setPosition(windowWidth-edgeSize,0); //lower left
        window.draw(wall);
        wall.setPosition(0, windowHeight-infoBar-edgeSize); // upper right
        window.draw(wall);
        wall.setPosition(windowWidth-edgeSize+4, windowHeight-infoBar-edgeSize); // lower right
        window.draw(wall);
    }
    else{
        sf::RectangleShape part(sf::Vector2f(windowWidth,edgeSize));
        part.setFillColor(sf::Color::White);
        part.setPosition(0,windowHeight-infoBar-edgeSize);
        window.draw(part);
        part.setPosition(0, 0);
        window.draw(part);
        part.setSize(sf::Vector2f(edgeSize,windowHeight));
        part.setPosition(0,0);
        window.draw(part);
        part.setPosition(windowWidth-edgeSize, 0);
        window.draw(part);
    }
}
void drawInfoBar(sf::RenderWindow &window, bool haveNormalFood, bool haveSpecialFood, Board board, sf::Sprite normalFood, sf::Sprite specialFood, int WINDOW_WIDTH, int WINDOW_HEIGHT, int EDGE_SIZE, int INFO_BAR, sf::Font font){
    
    int categorySize = 400;
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH,INFO_BAR));
    background.setFillColor(sf::Color(100,100,100));
    background.setPosition(0,WINDOW_HEIGHT-INFO_BAR);
    window.draw(background);
    
}