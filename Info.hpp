#include <vector>
#include <utility>
enum Level{EASY,MEDIUM,HARD};
using namespace std;
class Info{
private:
    vector< pair<string, int> > highscore;
    Level difficulty;
public:
    Info();
    
    void saveHighscore();
    int addToHighscore(string name, int score);
    void printHighscore();
};