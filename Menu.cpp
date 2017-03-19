
#include "Menu.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"

Menu::Menu(double width, double height,sf::Font &font): selectedItemIndex(0), font(font){
    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1) * 1 ));
    menu[0].setCharacterSize(fontSize);
    
    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Options");
    menu[1].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1) * 2 ));
    menu[1].setCharacterSize(fontSize);
    
    menu[2].setFont(font);
    menu[2].setColor(sf::Color::White);
    menu[2].setString("Highscore");
    menu[2].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1) * 3 ));
    menu[2].setCharacterSize(fontSize);
    
    menu[3].setFont(font);
    menu[3].setColor(sf::Color::White);
    menu[3].setString("Exit");
    menu[3].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1) * 4 ));
    menu[3].setCharacterSize(fontSize);

}

Menu::~Menu(){
    
}

void Menu::draw(sf::RenderWindow &window){
    for (int i = 0; i<MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp(){
    if(selectedItemIndex-1>=0){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}
void Menu::MoveDown(){
    if(selectedItemIndex+1 < MAX_NUMBER_OF_ITEMS){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}