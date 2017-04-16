#include "Drawing.hpp"
#include <SFML/Graphics.hpp>
#include <utility>
using namespace std;

void drawSnakeHead(sf::RenderWindow &window, Board board, Images sprites,sf::Color snakeHead_color){
    int snakeSize = board.getSnakeSize();
    sf::RectangleShape part(sf::Vector2f(snakeSize,snakeSize));
    pair<int,int> snakeHeadCoord = board.getSnakeHeadCoord();
    if(!sprites.getHaveSnakeHead()){
        part.setFillColor(snakeHead_color);
        part.setPosition(snakeHeadCoord.first,snakeHeadCoord.second);
        window.draw(part);
    }
    else{
        sf::Sprite snakeHead = sprites.getSnakeHead();
        snakeHead.setTextureRect(sf::IntRect(0,board.getSnakeHeadDirection()*snakeSize,snakeSize,snakeSize));
        snakeHead.setPosition(snakeHeadCoord.first, snakeHeadCoord.second);
        window.draw(snakeHead);
    }

}
void drawSnakeTail(sf::RenderWindow &window, Board board, Images sprites,sf::Color snakeTail_color){
    
    int snakeSize = board.getSnakeSize();
    list<pair<int,int> > coordinates;
    list<pair<Direction,Direction>> dir;
    coordinates = board.getSnakeTailCoordAndDir(dir);
    list<pair<int,int> >::iterator coordinatesIt;
    if (!sprites.getHaveSnakeTail()) {
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
            sf::Sprite snakeTail = sprites.getSnakeTail();
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
            sf::Sprite endTail = sprites.getEndTail();
            endTail.setPosition(coordinatesIt->first,coordinatesIt->second);
            //tempCoord = make_pair(coordinatesIt->first, coordinatesIt->second);
            if(++coordinatesIt == coordinates.end() && sprites.getHaveEndTail()){
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
void drawFood(sf::RenderWindow &window, Board board,Images sprites,sf::Color foodColor){
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
        if(sprites.getHaveNormalFood()){
            sf::Sprite normalFood = sprites.getNormalFood();
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
        if(sprites.getHaveSpecialFood()){
            sf::Sprite specialFood = sprites.getSpecialFood();
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
void drawWall(sf::RenderWindow &window, Images sprites,int windowWidth,int windowHeight, int edgeSize,int infoBar){
    if(sprites.getHaveWall()){
        sf::Sprite wall = sprites.getWall();
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
void drawInfoBar(sf::RenderWindow &window, Board board, Images sprites, int WINDOW_WIDTH, int WINDOW_HEIGHT, int EDGE_SIZE, int INFO_BAR, sf::Font font){
    
    int categorySize = 500;
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH,INFO_BAR));
    background.setFillColor(sf::Color(100,100,100));
    background.setPosition(0,WINDOW_HEIGHT-INFO_BAR);
    window.draw(background);
    // Regular FOOD:
    
    sf::Text text("Food Available:", font, 50);
    text.setColor(sf::Color::Red);
    text.setPosition(WINDOW_WIDTH-2*categorySize, WINDOW_HEIGHT-INFO_BAR+5);
    window.draw(text);
    int snakeSize = board.getSnakeSize();
    sf::Sprite normalFood = sprites.getNormalFood();
    switch (*board.getFoodTypes().first.begin()) {
        case BANANA:
            normalFood.setTextureRect(sf::IntRect(0,0 * snakeSize,snakeSize,snakeSize));
            text.setString("BANANA, 2p");
            break;
        case APPLE:
            normalFood.setTextureRect(sf::IntRect(0,1 * snakeSize,snakeSize,snakeSize));
            text.setString("APPLE, 2p");
            break;
        case ORANGE:
            normalFood.setTextureRect(sf::IntRect(0,2 * snakeSize,snakeSize,snakeSize));
            text.setString("ORANGE, 2p");
            break;
        case PEAR:
            normalFood.setTextureRect(sf::IntRect(0,3 * snakeSize,snakeSize,snakeSize));
            text.setString("PEAR, 2p");
            break;
    }
    normalFood.setPosition(WINDOW_WIDTH-2*categorySize,WINDOW_HEIGHT-INFO_BAR/2);
    window.draw(normalFood);
    text.setPosition(WINDOW_WIDTH-2*categorySize + snakeSize + 10, WINDOW_HEIGHT-INFO_BAR/2);
    window.draw(text);
    //MOVING FOOD:
    text.setString("Bonus Food Available:");
    text.setPosition(WINDOW_WIDTH-categorySize, WINDOW_HEIGHT-INFO_BAR+5);
    window.draw(text);
    sf::Sprite specialFood = sprites.getSpecialFood();
    switch (*board.getFoodTypes().second.begin()) {
        case WORM:
            specialFood.setTextureRect(sf::IntRect(0,0 * snakeSize,snakeSize,snakeSize));
            text.setString("WORM, 5p");
            break;
        case GREYMOUSE:
            specialFood.setTextureRect(sf::IntRect(0,1 * snakeSize,snakeSize,snakeSize));
            text.setString("Grey Mouse, 7p");
            break;
        case WHITEMOUSE:
            specialFood.setTextureRect(sf::IntRect(0,2 * snakeSize,snakeSize,snakeSize));
            text.setString("White Mouse, 10p");
            break;
        case FROG:
            specialFood.setTextureRect(sf::IntRect(0,3 * snakeSize,snakeSize,snakeSize));
            text.setString("Frog, 20p");
            break;
    }
    text.setPosition(WINDOW_WIDTH-categorySize+snakeSize+10, WINDOW_HEIGHT-INFO_BAR/2);
    window.draw(text);
    if(sprites.getHaveSpecialFood()){
        specialFood.setPosition(WINDOW_WIDTH-categorySize, WINDOW_HEIGHT-INFO_BAR/2);
        window.draw(specialFood);
    }
    // SCORE:
    text.setString("Score:");
    text.setPosition(WINDOW_WIDTH-3*categorySize, WINDOW_HEIGHT-INFO_BAR+5);
    window.draw(text);
    string score = "";
    score += to_string(board.getSnakePoints());
    score += " points";
    text.setString(score);
    text.setPosition(WINDOW_WIDTH-3*categorySize, WINDOW_HEIGHT-INFO_BAR/2);
    window.draw(text);
    //NAME:
    text.setString("Player name: " + board.getPlayerName());
    text.setCharacterSize(INFO_BAR/2);
    text.setPosition(20, WINDOW_HEIGHT-INFO_BAR/1.1);
    window.draw(text);
}
void drawText(sf::RenderWindow &window, int x, int y, string text, sf::Font font, int fontSize, sf::Color color){
    sf::Text t(text, font, fontSize);
    t.setColor(color);
    t.setPosition(x, y);
    window.draw(t);
}