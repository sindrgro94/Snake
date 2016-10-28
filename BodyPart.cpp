#include "BodyPart.hpp"
#include <list>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;

/////////////////BODYPART////////////////////////////
BodyPart::BodyPart(pair<Direction,Direction> dir,int y,int x,bool isLast):_y(y),_x(x),_isLast(isLast),_dir(dir){}
