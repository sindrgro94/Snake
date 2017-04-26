//#pragma once
#ifndef Drawing_hpp
#define Drawing_hpp

#include "Board.hpp"
#include "Images.hpp"
#include "Info.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

void drawSnakeHead(sf::RenderWindow &window, Board board,Images sprites,sf::Color snakeHead_color);
void drawSnakeTail(sf::RenderWindow &window, Board board,Images sprites,sf::Color snakeTail_color);
void drawFood(sf::RenderWindow &window, Board board,Images sprites,sf::Color foodColor);
void drawWall(sf::RenderWindow &window, Images sprites,int windowWidth,int windowHeight, int edgeSize,int infoBar);
void drawInfoBar(sf::RenderWindow &window, Board board, Images sprites, int WINDOW_WIDTH, int WINDOW_HEIGHT, int EDGE_SIZE, int INFO_BAR, sf::Font font);
void drawText(sf::RenderWindow &window, int x, int y, string text, sf::Font font, int fontSize, sf::Color color);
sf::Texture getMenuBackground(sf::RenderWindow &window, Images sprites);
#endif
