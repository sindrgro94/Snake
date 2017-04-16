//#pragma once
#ifndef Menu_hpp
#define Menu_hpp
#include "SFML/Graphics.hpp"
#include <vector>
#include "Info.hpp"
using namespace std;
#define MAX_NUMBER_OF_ITEMS 7
#define ROWS 4
class Menu{
private:
    Info* info;
    sf::Text difficulty[3];
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    int fontSize = 120;
    vector<sf::FloatRect> boundaries;
    vector<sf::FloatRect> difficultyBoundaries;
public:
    Menu(double width, double height,sf::Font &font, Info* info);
    ~Menu();
    
    void setColor();
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int getPressedItem(){return selectedItemIndex;}
    int getPressedItem2();
};

#endif