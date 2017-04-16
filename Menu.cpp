
#include "Menu.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"

Menu::Menu(double width, double height,sf::Font &font, Info* info): selectedItemIndex(0), font(font),info(info){
    menu[0].setFont(font);
    menu[0].setColor(sf::Color::White);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width/2, height/(ROWS+1) * 1 ));
    menu[0].setCharacterSize(fontSize);
    
    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Difficulty:");
    menu[1].setPosition(sf::Vector2f(width/2, height/(ROWS+1) * 2 ));
    menu[1].setCharacterSize(fontSize);
    
    menu[2].setFont(font);
    menu[2].setColor(sf::Color::White);
    menu[2].setString("Highscore");
    menu[2].setPosition(sf::Vector2f(width/2, height/(ROWS+1) * 3 ));
    menu[2].setCharacterSize(fontSize);
    
    menu[3].setFont(font);
    menu[3].setColor(sf::Color::White);
    menu[3].setString("Exit");
    menu[3].setPosition(sf::Vector2f(width/2, height/(ROWS+1) * 4 ));
    menu[3].setCharacterSize(fontSize);
    
    int factor = 2;
    int h = 45;
    
    menu[4].setFont(font);
    menu[4].setColor(sf::Color::White);
    menu[4].setString("Easy");
    menu[4].setPosition(sf::Vector2f(width/1.5+120,height/(ROWS+1) * 2 + h));
    menu[4].setCharacterSize(fontSize/factor);
    
    menu[5].setFont(font);
    menu[5].setColor(sf::Color::Blue);
    menu[5].setString("Medium");
    menu[5].setPosition(sf::Vector2f(width/1.5+320,height/(ROWS+1) * 2 + h));
    menu[5].setCharacterSize(fontSize/factor);
    
    menu[6].setFont(font);
    menu[6].setColor(sf::Color::White);
    menu[6].setString("Hard");
    menu[6].setPosition(sf::Vector2f(width/1.5+620,height/(ROWS+1) * 2 + h));
    menu[6].setCharacterSize(fontSize/factor);


    for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
        boundaries.push_back(menu[i].getGlobalBounds());
    }
}

Menu::~Menu(){
    
}
void Menu::setColor(){
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
        if(boundaries[i].contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition()))&& i != 1){
            menu[i].setColor(sf::Color::Red);
        }
        else if(info->getDifficulty() + 4 == i){
            menu[i].setColor(sf::Color::Blue);
        }
        else{
            menu[i].setColor(sf::Color::White);
        }
    }
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
int Menu::getPressedItem2(){
    for(int i = 0; i<MAX_NUMBER_OF_ITEMS; i++){
       if(boundaries[i].contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition()))&& i != 1){
           return i;
       }
    }
    return -1;
}