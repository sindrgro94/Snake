
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
// lagt til selv:
#include "Snake.hpp"
#include "Board.hpp"
#include "BodyPart.hpp"
#include "Food.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <queue>
using namespace std;
const sf::Color number_colors[9] = {
    sf::Color::White,
    sf::Color::Blue,
    sf::Color(0, 128, 0),
    sf::Color::Red,
    sf::Color(0, 0, 128),
    sf::Color(128, 0, 0),
    sf::Color(0, 128, 128),
    sf::Color::Black,
    sf::Color(128, 128, 128)
};
const sf::Color snakeHead_color = sf::Color::Red;
const sf::Color snakeTail_color = sf::Color::Green;
const sf::Color board_color = sf::Color::Black;
const sf::Color foodColor = sf::Color::Blue;
const int tile_size = 52;
const int WINDOW_WIDTH = 800*2;
const int WINDOW_HEIGHT = 600*2;
const int SNAKE_SIZE = 50;


int main(){
    srand(time(nullptr));
    Board board(WINDOW_WIDTH,WINDOW_HEIGHT,SNAKE_SIZE);
    //////// Create the main window/////////////////
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window",sf::Style::Default);
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 40);
    text.setColor(sf::Color::White);
    /////////Loading images:////////////////////
    //SnakeHead:
    sf::Texture snakeHeadImage;
    sf::Sprite snakeHead;
    bool haveSnakeHead = true;
    if(!snakeHeadImage.loadFromFile("snakeHeadTest.png")){
        cout<<"Could not load snake head image."<<endl;
        haveSnakeHead = false;
    }
    snakeHead.setTexture(snakeHeadImage);
    ////////Defining variables:////////////////
    sf::Clock clock;
    sf::Time time;
    list<Direction> moveQueue;
    int cornerColumn,cornerRow;
    
    //start the game loop:
    while (window.isOpen()){
        // Process events
        sf::Event event;
        while (window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code){
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::Down:
                            moveQueue.push_back(DOWN);
                            break;
                        case sf::Keyboard::Up:
                            moveQueue.push_back(UP);
                            break;
                        case sf::Keyboard::Left:
                            moveQueue.push_back(LEFT);
                            break;
                        case sf::Keyboard::Right:
                            moveQueue.push_back(RIGHT);
                            break;
                    }
            }
        }
        time = clock.getElapsedTime();
        if(time.asMilliseconds()>=120){
            clock.restart();
            ///////////////Clear screen///////////////
            window.clear();
            board.moveSnake(moveQueue);
            ///////////////Drawing the snake:///////////////
            //pair<BodyPart*,list<BodyPart*>> snake = board.getSnake();
            sf::RectangleShape part(sf::Vector2f(SNAKE_SIZE,SNAKE_SIZE));
            ///////////////Draw the head:///////////////
            pair<int,int> snakeHeadCoord = board.getSnakeHeadCoord();
            if(!haveSnakeHead){
                part.setFillColor(snakeHead_color);
                part.setPosition(snakeHeadCoord.second,snakeHeadCoord.first);
                window.draw(part);
            }
            else{
                
            }
            
           
            
            ///////////////Draw the tail:///////////////
            list<pair<int,int> > coordinates;
            list<pair<int,int> >::iterator coordinatesIt;
            part.setFillColor(snakeTail_color);
            coordinates = board.getSnakeTailCoord();
            for(coordinatesIt = coordinates.begin(); coordinatesIt!=coordinates.end(); coordinatesIt++){
                part.setPosition(coordinatesIt->first, coordinatesIt->second);
                window.draw(part);
            }
            ///////////////Draw the food WARNING!! SIZE IS STANDARD AT THE MOMENT!!
            coordinates = board.getFoodCoord();
            part.setFillColor(foodColor);
            for(coordinatesIt = coordinates.begin(); coordinatesIt!=coordinates.end(); coordinatesIt++){
                part.setPosition(coordinatesIt->first, coordinatesIt->second);
                window.draw(part);
            }

            // Draw the string
            window.draw(text);
            window.draw(snakeHead);
        
            // Update the window
            window.display();
        }
        if (board.didSnakeCollide(WINDOW_WIDTH, WINDOW_HEIGHT))
            window.close();
    }
    
    return EXIT_SUCCESS;
}
