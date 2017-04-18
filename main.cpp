
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
const int EASY_SPEED = 180;
const int MEDIUM_SPEED = 130;
const int HARD_SPEED = 90;
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
    ////////Defining variables:////////////////
    Info settings;
    Menu menu(WINDOW_WIDTH,WINDOW_HEIGHT,font, &settings);
    Images sprites;
    sf::Clock clock;
    sf::Time time;
    list<Direction> moveQueue;
    int cornerColumn,cornerRow;
    bool inMainMenu = true;
    //start the game loop:
    while (window.isOpen()){
        ////////Menu:////////////////
        inMainMenu = true;
        sf::Sprite menuBackground = getMenuBackground(window, sprites);
        while (window.isOpen() && inMainMenu) {
            sf::Event event;
            while (window.pollEvent(event) && window.isOpen()) {
                switch (event.type) {
                    case sf::Event::KeyReleased:
                        switch (event.key.code) {
                            case sf::Keyboard::Escape:
                                window.close();
                            /*
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
                                }*/
                            default:
                                break;
                        }
                        break;
                    case sf::Event::MouseMoved:
                        menu.setColor();
                        break;
                    case sf::Event::MouseButtonReleased:
                            switch (menu.getPressedItem2()){
                                case 0:
                                    inMainMenu = false;
                                    break;
                                case 1:
                                    //nothing
                                    break;
                                case 2:
                                    settings.drawHighscore(window, font, WINDOW_WIDTH, WINDOW_HEIGHT);
                                    break;
                                case 3:
                                    window.close();
                                    break;
                                case 4:
                                    settings.setDifficulty(EASY);
                                    break;
                                case 5:
                                    settings.setDifficulty(MEDIUM);
                                    break;
                                case 6:
                                    settings.setDifficulty(HARD);
                                    break;
                                default:
                                    break;
                            }
                        break;
                    case sf::Event::Closed:
                        window.close();
                        break;
                    default:
                        break;
                }
            }
            window.clear();
            menu.draw(window);
            window.draw(menuBackground);
            window.display();
        }
        ////////Input name:////////////////
        int textSize = 60;
        bool nameSaved = false;
        sf::Text info("Write your name:",font,textSize);
        info.setColor(sf::Color::Red);
        info.setPosition(WINDOW_WIDTH/6, WINDOW_HEIGHT/2);
        sf::FloatRect infoBoundary = info.getGlobalBounds();
        
        sf::Text name("",font,textSize);
        sf::String userName;
        name.setPosition(infoBoundary.left + infoBoundary.width + 40, infoBoundary.top-infoBoundary.height/4);
        
        sf::Text startText("Start game",font,textSize*1.5);
        sf::FloatRect startB = startText.getGlobalBounds();
        startText.setPosition(infoBoundary.left + (infoBoundary.width+startB.width)/2,infoBoundary.top + 3*infoBoundary.height);
        startB = startText.getGlobalBounds();
        sf::FloatRect startSize(startText.getGlobalBounds());
        while(!nameSaved && window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event) && window.isOpen()){
                switch (event.type){
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyReleased:
                        switch (event.key.code){
                            case sf::Keyboard::Return:
                                if (userName.getSize()>0)
                                    nameSaved = true;
                                break;
                            case sf::Keyboard::Escape:
                                window.close();
                            case sf::Keyboard::BackSpace:
                                userName.clear();
                            default:
                                break;
                        }
                    case sf::Event::MouseButtonReleased:
                        if (startSize.contains(event.mouseButton.x,event.mouseButton.y) && userName.getSize()>0){
                            nameSaved = true;
                        }
                        break;
                    default:
                        break;
                }
                if (event.type == sf::Event::TextEntered && userName.getSize()<18 && event.text.unicode != 10){
                    userName.insert(userName.getSize(),event.text.unicode);
                }
            }
            window.clear();
            window.draw(info);
            name.setString(userName);
            window.draw(name);
            if (startSize.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition()))){
                startText.setColor(sf::Color::Red);
            }
            else{
                startText.setColor(sf::Color::White);
            }
            drawSnakeHead(window,board, sprites, snakeHead_color);
            drawSnakeTail(window,board,sprites,snakeTail_color);
            drawWall(window, sprites, WINDOW_WIDTH, WINDOW_HEIGHT, EDGE_SIZE, INFO_BAR);
            drawInfoBar(window, board, sprites, WINDOW_WIDTH, WINDOW_HEIGHT, EDGE_SIZE, INFO_BAR, font);
            
            window.draw(startText);
            window.display();
        }
        board.setPlayerName(userName);
        ////////Game running:////////////////
        int gameSpeed;
        switch (settings.getDifficulty()) {
            case EASY:
                gameSpeed = EASY_SPEED;
                break;
            case MEDIUM:
                gameSpeed = MEDIUM_SPEED;
                break;
            default:
                gameSpeed = HARD_SPEED;
                break;
        }
        while(!board.didSnakeCollide(WINDOW_WIDTH, WINDOW_HEIGHT, INFO_BAR, EDGE_SIZE) && window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event) && window.isOpen()){
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
            if(time.asMilliseconds()>=gameSpeed){
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
 
                // Update the window
                window.display();
            }

        }
        int place = settings.addToHighscore(board.getPlayerName(), board.getSnakePoints());
        string message;
        switch(place){
            case 0:
                message = "Unfortunately, you did not make it to the highscore list.";
                break;
            case 1:
                message = "Congratulations, you beat the highscore!";
                break;
            default:
                message = "Congratuations, you made it to the highscore list!";
                break;
        }
        
        clock.restart();
        time = clock.getElapsedTime();
        drawText2(window, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, message, font, 100, sf::Color::Red, true);
        window.display();
        while (time.asSeconds()<4) {
            time = clock.getElapsedTime();
        }
        board.reset();
        settings.drawHighscore(window, font, WINDOW_WIDTH, WINDOW_HEIGHT);
    }
    
    return EXIT_SUCCESS;
}
