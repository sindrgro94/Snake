#pragma once
#include "Board.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

void drawSnakeHead(sf::RenderWindow &window,bool havePicture, Board board, sf::Sprite snakeHead,sf::Color snakeHead_color);
void drawSnakeTail(sf::RenderWindow &window,bool haveSnakeTail,bool haveEndTail,Board board,sf::Sprite snakeTail,sf::Sprite endTail,sf::Color snakeTail_color);