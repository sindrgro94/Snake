
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
#include "Board.hpp"
#include "Drawing.hpp"
#include "Menu.hpp"
#include "Info.hpp"
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
const int SNAKE_SIZE = 50;
const int EDGE_SIZE = 50;
const int INFO_BAR = 140;
int main(){
    srand(time(nullptr));
    vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    const int WINDOW_WIDTH = modes[0].width; //2560 on Sindres Mac
    const int WINDOW_HEIGHT = modes[0].height; //1600 on Sindres Mac

    Board board(WINDOW_WIDTH-(2*EDGE_SIZE),WINDOW_HEIGHT-(2*EDGE_SIZE+INFO_BAR),SNAKE_SIZE,INFO_BAR,EDGE_SIZE);
    //////// Create the main window/////////////////
    // Create a window with the same pixel depth as the desktop
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,desktop.bitsPerPixel), "Sindres Snake-spill",sf::Style::Fullscreen);
    sf::Font font;
    if (!font.loadFromFile("angrybirds-regular.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 40);
    text.setColor(sf::Color::White);
    ////////Defining variables:////////////////
    Menu menu(WINDOW_WIDTH,WINDOW_HEIGHT,font);
    Info settings;
    settings.printHighscore();
    Images sprites;
    sf::Clock clock;
    sf::Time time;
    list<Direction> moveQueue;
    int cornerColumn,cornerRow;
    bool inMainMenu = true;
    string userName;
    //start the game loop:
    while (window.isOpen()){
        ////////Menu:////////////////
        inMainMenu = true;
        while (window.isOpen() && inMainMenu) {
            sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::KeyReleased:
                        switch (event.key.code) {
                            case sf::Keyboard::Up:
                                menu.MoveUp();
                                break;
                            case sf::Keyboard::Down:
                                menu.MoveDown();
                                break;
                            case sf::Keyboard::Return:
                                switch (menu.getPressedItem()) {
                                    case 0:
                                        inMainMenu = false;
                                        break;
                                    case 1:
                                        //options
                                        break;
                                    case 2:
                                        settings.drawHighscore(window, font, WINDOW_WIDTH, WINDOW_HEIGHT);
                                        break;
                                    case 3:
                                        window.close();
                                        break;
                                    default:
                                        break;
                                }
                            default:
                                break;
                        }
                        break;
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::TextEntered:
                        if (event.text.unicode == 8 && userName.size() != 0){
                            userName.pop_back();
                        }
                        else if(event.text.unicode < 128){
                            userName.push_back(static_cast<char>(event.text.unicode));
                        }
                        break;
                    default:
                        break;
                }
            }
            window.clear();
            text.setString(userName);
            text.setPosition(100, 100);
            window.draw(text);
            menu.draw(window);
            window.display();
        }
        
        ////////Game running:////////////////
        while(!board.didSnakeCollide(WINDOW_WIDTH, WINDOW_HEIGHT, INFO_BAR, EDGE_SIZE) && window.isOpen()){
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
            if(time.asMilliseconds()>=150){
                clock.restart();
                ///////////////Clear screen///////////////
                window.clear();
                board.moveSnake(moveQueue);
                ///////////////Drawing the snake:///////////////
                drawSnakeHead(window,board, sprites, snakeHead_color);
                drawSnakeTail(window,board,sprites,snakeTail_color);
                drawFood(window, board, sprites,foodColor);
                drawWall(window, sprites, WINDOW_WIDTH, WINDOW_HEIGHT, EDGE_SIZE, INFO_BAR);
                drawInfoBar(window, board, sprites, WINDOW_WIDTH, WINDOW_HEIGHT, EDGE_SIZE, INFO_BAR, font);
                // Draw the string
                //window.draw(text);
                             

                
                // Update the window
                window.display();
            }

        }
    }
    
    return EXIT_SUCCESS;
}
