
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
    if(!snakeHeadImage.loadFromFile("snakeHead.png")){
        cout<<"Could not load snake head image."<<endl;
        haveSnakeHead = false;
    }
    snakeHead.setTexture(snakeHeadImage);
    //SnakeTail:
    sf::Texture snakeTailImage;
    sf::Sprite snakeTail;
    bool haveSnakeTail = true;
    if(!snakeTailImage.loadFromFile("snakeTailTest.png")){
        cout<<"Could not load snake tail image"<<endl;
        haveSnakeTail = false;
    }
    snakeTail.setTexture(snakeTailImage);
    //EndTail:
    sf::Texture endTailImage;
    sf::Sprite endTail;
    bool haveEndTail = true;
    if(!endTailImage.loadFromFile("endTailTest.png")){
        cout<<"Could not load end tail image"<<endl;
        haveEndTail = false;
    }
    endTail.setTexture(endTailImage);
    //NormalFood:
    sf::Texture normalFoodImage;
    sf::Sprite normalFood;
    bool haveNormalFood = true;
    if(!normalFoodImage.loadFromFile("normalFoodTest.png")){
        cout<<"Could not load normal food image"<<endl;
        haveNormalFood = false;
    }
    normalFood.setTexture(normalFoodImage);
    //SpecialFood:
    sf::Texture specialFoodImage;
    sf::Sprite specialFood;
    bool haveSpecialFood = true;
    if(!specialFoodImage.loadFromFile("specialFoodTest.png")){
        cout<<"Could not load special food image"<<endl;
        haveSpecialFood = false;
    }
    specialFood.setTexture(specialFoodImage);
    //Wall:
    sf::Texture wallImage;
    sf::Sprite wall;
    bool haveWall = true;
    if(!wallImage.loadFromFile("wall.png")){
        cout<<"Could not load wall image"<<endl;
        haveWall = false;
    }
    wall.setTexture(wallImage);
    
    ////////Defining variables:////////////////
    sf::Clock clock;
    sf::Time time;
    list<Direction> moveQueue;
    int cornerColumn,cornerRow;
    
    //start the game loop:
    while (window.isOpen()){
        
        ////////Game running:////////////////
        while(!board.didSnakeCollide(WINDOW_WIDTH, WINDOW_HEIGHT) && window.isOpen()){
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
            if(time.asMilliseconds()>=990){
                clock.restart();
                ///////////////Clear screen///////////////
                window.clear();
                board.moveSnake(moveQueue);
                ///////////////Drawing the snake:///////////////
                drawSnakeHead(window,haveSnakeHead, board, snakeHead, snakeHead_color);
                drawSnakeTail(window,haveSnakeTail,haveEndTail,board,snakeTail,endTail,snakeTail_color);
                drawFood(window,haveNormalFood,haveSpecialFood, board, normalFood, specialFood,foodColor);
                drawWall(window, haveWall, wall, WINDOW_WIDTH, WINDOW_HEIGHT, EDGE_SIZE, INFO_BAR);
                // Draw the string
                //window.draw(text);
                             

                
                // Update the window
                window.display();
            }

        }
        window.close();
    }
    
    return EXIT_SUCCESS;
}
