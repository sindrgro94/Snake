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
            highscore.push_back(make_pair("No highscore available", 0));
        }
        cout<<"Failed loading highscore file"<<endl;
    }
    else{
        string line;
        string word;
        string name;
        while(getline(input,line)){
            stringstream ss(line);
            name = "";
            bool score = false;
            while(ss>>word){
                if (word!="&" && !score){
                    name+=word +" ";
                }
                else if(word=="&"){
                    score = true;
                }
                else{
                    highscore.push_back(make_pair(name, stoi(word)));
                    score = false;
                }
            }
        }
    }
    input.close();
}

void Info::saveHighscore(){
    ofstream output;
    output.open("/Users/SindreGrostad/Documents/cpp/Spill/Snake/Snake/Snake/highscore_backup.txt");
    if (output.fail()){
        cout<<"Failed saving highscore file"<<endl;
        exit(1);
    }
    string line;
    auto it = highscore.begin();
    output<<it->first<<"& "<<it->second;
    for(; it != highscore.end(); it++){
        output<<endl<<it->first<<"& "<<it->second;
    }
}

int Info::addToHighscore(string name, int score){
    int place = 1;
    for(auto it = highscore.begin(); it!= highscore.end(); it++){
        if(it->second<=score){
            highscore.insert(it, make_pair(name,score));
            highscore.pop_back();
            return place;
        }
        place++;
    }
    return 0;
}

void Info::printHighscore(){
    int counter = 0;
    int lastscore = 0;
    int tied = 0;
    cout<<setw(7)<<left<<"Place"<<setw(31)<<left<<"Name"<<setw(6)<<"Score"<<endl;
    for(auto it = highscore.begin(); it!= highscore.end(); it++){
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