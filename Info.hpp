//#pragma once
#ifndef Info_hpp
#define Info_hpp
#include <vector>
#include <utility>
enum Level{EASY,MEDIUM,HARD};
using namespace std;
class Info{
private:
    vector< pair<string, int> > highscoreEasy;
    vector< pair<string, int> > highscoreMedium;
    vector< pair<string, int> > highscoreHard;
    Level difficulty;
public:
    Info();
    
    void saveHighscore();
    int addToHighscore(string name, int score);
    void printHighscore();
    void drawHighscore(sf::RenderWindow &window, sf::Font font, int width, int height);
    void print();
    Level getDifficulty(){return difficulty;}
    void setDifficulty(Level diff){difficulty = diff;}
};
void drawText2(sf::RenderWindow &window, int x, int y, string text, sf::Font font, int fontSize, sf::Color color, bool center);
#endif