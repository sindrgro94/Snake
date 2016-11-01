#pragma once
#include "Board.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

void drawSnakeHead(sf::RenderWindow &window,bool havePicture, Board board, sf::Sprite snakeHead,sf::Color snakeHead_color);
void drawSnakeTail(sf::RenderWindow &window,bool haveSnakeTail,bool haveEndTail,Board board,sf::Sprite snakeTail,sf::Sprite endTail,sf::Color snakeTail_color);
void drawFood(sf::RenderWindow &window,bool haveNormalFood,bool haveSpecialFood, Board board, sf::Sprite normalFood, sf::Sprite specialFood,sf::Color foodColor);