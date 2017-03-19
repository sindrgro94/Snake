//#pragma once
#ifndef Menu_hpp
#define Menu_hpp
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 4
class Menu{
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    int fontSize = 120;
public:
    Menu(double width, double height,sf::Font &font);
    ~Menu();
    
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int getPressedItem(){return selectedItemIndex;}
};

#endif