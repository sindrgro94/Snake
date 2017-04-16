#include <SFML/Graphics.hpp>
#include "Info.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

Info::Info():difficulty(MEDIUM){
    ifstream input;
    input.open("/Users/SindreGrostad/Documents/cpp/Spill/Snake/Snake/Snake/highscore.txt");
    if(input.fail()){
        for( int i = 0; i<10; i++){
            highscoreEasy.push_back(make_pair("No highscore available", 0));
            highscoreMedium.push_back(make_pair("No highscore available", 0));
            highscoreHard.push_back(make_pair("No highscore available", 0));
        }
        cout<<"Failed loading highscore file"<<endl;
    }
    else{
        string line;
        string word;
        string name;
        int counter = 0;
        while(getline(input,line)){
            counter++;
            stringstream ss(line);
            name = "";
            bool first = true;
            bool score = false;
            while(ss>>word){
                if (word!="&" && !score){
                    if (first){
                        name += word;
                        first = false;
                    }
                    else{
                        name+=" " + word;
                    }
                }
                else if(word=="&"){
                    score = true;
                }
                else{
                    if (counter<=10){
                        highscoreEasy.push_back(make_pair(name, stoi(word)));
                    }
                    else if(counter<=20){
                        highscoreMedium.push_back(make_pair(name, stoi(word)));
                    }
                    else{
                        highscoreHard.push_back(make_pair(name, stoi(word)));
                    }
                    score = false;
                }
            }
        }
    }
    input.close();
}

void Info::saveHighscore(){
    ofstream output;
    output.open("/Users/SindreGrostad/Documents/cpp/Spill/Snake/Snake/Snake/highscore.txt");
    if (output.fail()){
        cout<<"Failed saving highscore file"<<endl;
        exit(1);
    }
    auto it = highscoreEasy.begin();
    output<<it->first<<" & "<<it->second;
    //cout<<it->first<<endl<<it->second<<endl;
    for(; it != highscoreEasy.end(); it++){
        output<<endl<<it->first<<" & "<<it->second;
        //cout<<it->first<<endl<<it->second<<endl;
    }
    for(it = highscoreMedium.begin(); it != highscoreMedium.end(); it++){
        output<<endl<<it->first<<" & "<<it->second;
        //cout<<it->first<<endl<<it->second<<endl;
    }
    for(it = highscoreHard.begin(); it != highscoreHard.end(); it++){
        output<<endl<<it->first<<" & "<<it->second;
        //cout<<it->first<<endl<<it->second<<endl;
    }
    output.close();
}

int Info::addToHighscore(string name, int score){
    int place = 1;
    switch (difficulty) {
        case HARD:
            for(auto it = highscoreHard.begin(); it!= highscoreHard.end(); it++){
                if(it->second<=score){
                    highscoreHard.insert(it, make_pair(name,score));
                    highscoreHard.pop_back();
                    return place;
                }
                place++;
            }

            break;
        case MEDIUM:
            for(auto it = highscoreMedium.begin(); it!= highscoreMedium.end(); it++){
                if(it->second<=score){
                    highscoreMedium.insert(it, make_pair(name,score));
                    highscoreMedium.pop_back();
                    return place;
                }
                place++;
            }
            break;
        default:
            for(auto it = highscoreEasy.begin(); it!= highscoreEasy.end(); it++){
                if(it->second<=score){
                    highscoreEasy.insert(it, make_pair(name,score));
                    highscoreMedium.pop_back();
                    return place;
                }
                place++;
            }
            break;
    }
    this->saveHighscore();
    return 0;
}

void Info::printHighscore(){
    int counter = 0;
    int lastscore = 0;
    int tied = 0;
    cout<<"Highscore level EASY:"<<endl;
    cout<<setw(7)<<left<<"Place"<<setw(31)<<left<<"Name"<<setw(6)<<"Score"<<endl;
    for(auto it = highscoreEasy.begin(); it!= highscoreEasy.end(); it++){
        if (lastscore>it->second || counter == 0){
            lastscore = it->second;
            counter+= 1 + tied;
            tied = 0;
        }
        else{
            tied++;
        }
        if (counter != 10)
        cout<<counter<<":     ";
        else
        cout<<counter<<":    ";
        cout<<setw(31)<<left<<it->first<<setw(6)<<it->second<<endl;
    }
    counter = 0;
    lastscore = 0;
    tied = 0;
    cout<<"Highscore level MEDIUM:"<<endl;
    cout<<setw(7)<<left<<"Place"<<setw(31)<<left<<"Name"<<setw(6)<<"Score"<<endl;
    for(auto it = highscoreMedium.begin(); it!= highscoreMedium.end(); it++){
        if (lastscore>it->second || counter == 0){
            lastscore = it->second;
            counter+= 1 + tied;
            tied = 0;
        }
        else{
            tied++;
        }
        if (counter != 10)
            cout<<counter<<":     ";
        else
            cout<<counter<<":    ";
        cout<<setw(31)<<left<<it->first<<setw(6)<<it->second<<endl;
    }
    counter = 0;
    lastscore = 0;
    tied = 0;
    cout<<"Highscore level HARD:"<<endl;
    cout<<setw(7)<<left<<"Place"<<setw(31)<<left<<"Name"<<setw(6)<<"Score"<<endl;
    for(auto it = highscoreHard.begin(); it!= highscoreHard.end(); it++){
        if (lastscore>it->second || counter == 0){
            lastscore = it->second;
            counter+= 1 + tied;
            tied = 0;
        }
        else{
            tied++;
        }
        if (counter != 10)
            cout<<counter<<":     ";
        else
            cout<<counter<<":    ";
        cout<<setw(31)<<left<<it->first<<setw(6)<<it->second<<endl;
    }
}

void Info::drawHighscore(sf::RenderWindow &window, sf::Font font, int width, int height){
    bool inHighscore = true;
    while(window.isOpen() && inHighscore){
        sf::Event event;
        window.clear();
        int col = width/6-10;
        int row = height/14;
        int HighscoreSize = 150;
        int categorySize = 100;
        int headerSize = 80;
        int listSize = 60;
        drawText2(window, width/2, row,"Highscore",font,HighscoreSize, sf::Color::Red,true);
        string line;
        int counter = 0;
        int lastscore = 0;
        int tied = 0;
        for(int l = EASY; l<=HARD; l++){
            line = "";
            counter = 0;
            lastscore = 0;
            tied = 0;
            switch (l){
                case EASY:
                    drawText2(window, col, row*3,"Easy",font,categorySize, sf::Color::Red,true);
                    for(auto it = highscoreEasy.begin(); it!= highscoreEasy.end(); it++){
                        if (lastscore>it->second || counter == 0){
                            lastscore = it->second;
                            counter+= 1 + tied;
                            tied = 0;
                        }
                        else{
                            tied++;
                        }
                        line = to_string(counter);
                        line += ". ";
                        line += it->first;
                        drawText2(window, col/4, row*(3+counter+tied),line,font,listSize, sf::Color::White,false);
                        line = to_string(it->second);
                        line += " p.";
                        drawText2(window, col/4+1.5*col, row*(3+counter+tied),line,font,listSize, sf::Color::White,false);
                    }
                    break;
                case MEDIUM:
                    drawText2(window, col*3, row*3,"Medium",font,categorySize, sf::Color::Red,true);
                    for(auto it = highscoreMedium.begin(); it!= highscoreMedium.end(); it++){
                        if (lastscore>it->second || counter == 0){
                            lastscore = it->second;
                            counter+= 1 + tied;
                            tied = 0;
                        }
                        else{
                            tied++;
                        }
                        line = to_string(counter);
                        line += ". ";
                        line += it->first;
                        drawText2(window, 2*col+col/4, row*(3+counter+tied),line,font,listSize, sf::Color::White,false);
                        line = to_string(it->second);
                        line += " p.";
                        drawText2(window, 2*col+col/4+1.5*col, row*(3+counter+tied),line,font,listSize, sf::Color::White,false);
                    }
                    break;
                case HARD:
                    drawText2(window, col*5, row*3,"Hard",font,categorySize, sf::Color::Red,true);
                    for(auto it = highscoreHard.begin(); it!= highscoreHard.end(); it++){
                        if (lastscore>it->second || counter == 0){
                            lastscore = it->second;
                            counter+= 1 + tied;
                            tied = 0;
                        }
                        else{
                            tied++;
                        }
                        line = to_string(counter);
                        line += ". ";
                        line += it->first;
                        drawText2(window, 4*col+col/4, row*(3+counter+tied),line,font,listSize, sf::Color::White,false);
                        line = to_string(it->second);
                        line += " p.";
                        drawText2(window, 4*col+col/4+1.5*col, row*(3+counter+tied),line,font,listSize, sf::Color::White,false);
                    }

                    break;
                default:
                    cout<<"Error in drawing Highscore"<<endl;
            }
            for(int i = 0; i<15;i++){
                drawText2(window, 2*col+32, row*4+row/1.5*i,"I",font,listSize, sf::Color::Red,false);
                drawText2(window, 4*col+32, row*4+row/1.5*i,"I",font,listSize, sf::Color::Red,false);
            }
        }
        window.display();
        while(window.pollEvent(event)){
            switch (event.type) {
                    case sf::Event::KeyReleased:
                        inHighscore = false;
                        break;
            }
            
        }
    }

}
void drawText2(sf::RenderWindow &window, int x, int y, string text, sf::Font font, int fontSize, sf::Color color, bool center){
    sf::Text t(text, font, fontSize);
    t.setColor(color);
    if (center){
        sf::FloatRect textRect = t.getLocalBounds();
        t.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    }
    t.setPosition(x, y);
    window.draw(t);
}

void Info::print(){
    cout<<"EASY:"<<endl;
    for(auto it = highscoreEasy.begin(); it != highscoreEasy.end(); it++){
        cout<<it->first<<" - " << it->second<<endl;
    }
    cout<<"MEDIUM:"<<endl;
    for(auto it = highscoreMedium.begin(); it != highscoreMedium.end(); it++){
        cout<<it->first<<" - " << it->second<<endl;
    }
    cout<<"HARD:"<<endl;
    for(auto it = highscoreHard.begin(); it != highscoreHard.end(); it++){
        cout<<it->first<<" - " << it->second<<endl;
    }
}