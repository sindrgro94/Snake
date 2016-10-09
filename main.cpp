
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
const int tile_size = 52;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SNAKE_SIZE = 10;


int main(){
    srand(time(nullptr));
    Board board(WINDOW_WIDTH,WINDOW_HEIGHT,SNAKE_SIZE);
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window",sf::Style::Default);
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 40);
    text.setColor(sf::Color::White);
    // Defining variables:
    sf::Clock clock;
    sf::Time time;
    list<Direction> moveQueue;
    int cornerColumn,cornerRow;
    
    //start the game loop:
    while (window.isOpen()){
        //controls the speed:
        clock.restart();
        time = clock.getElapsedTime();
        while(time.asMilliseconds()<30){
            time = clock.getElapsedTime();
        }
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
                            moveQueue.push_front(DOWN);
                            break;
                        case sf::Keyboard::Up:
                            moveQueue.push_front(UP);
                            break;
                        case sf::Keyboard::Left:
                            moveQueue.push_front(LEFT);
                            break;
                        case sf::Keyboard::Right:
                            moveQueue.push_front(RIGHT);
                            break;
                    }
            }
        }
        // Clear screen
        window.clear();
        board.moveSnake(moveQueue);
        // Drawing the snake:
        // (snake<snakeHead,snakeTail>)
        pair<BodyPart*,list<BodyPart*>> snake = board.getSnake();
        //printing the head:
        sf::RectangleShape rect(sf::Vector2f(1,1));
        rect.setFillColor(snakeHead_color);
        cornerColumn = snake.first->getColumn();
        cornerRow = snake.first->getRow();
        for(int row = 0; row<SNAKE_SIZE;row++){
            for (int col = 0; col<SNAKE_SIZE;col++){
                if (snake.first->snakeIsHere(row,col)){
                    rect.setPosition(cornerColumn+col,cornerRow+row);
                    window.draw(rect);
                }
            }
        }
        //printing the tail:
        list<BodyPart*>::iterator snakeTailIt;
        rect.setFillColor(snakeTail_color);
        for(snakeTailIt = snake.second.begin(); snakeTailIt!=snake.second.end();snakeTailIt++){
            cornerColumn = (*snakeTailIt)->getColumn();
            cornerRow = (*snakeTailIt)->getRow();
            for(int row = 0; row<SNAKE_SIZE;row++){
                for (int col = 0; col<SNAKE_SIZE;col++){
                    if ((*snakeTailIt)->snakeIsHere(row,col)){
                        rect.setPosition(cornerColumn+col, cornerRow+row);
                        window.draw(rect);
                    }
                }
            }
        }
        
        
        // Draw the string
        window.draw(text);
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
