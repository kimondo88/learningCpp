#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::cin;
using std::shuffle;
using std::mt19937;
int showScores(vector<int> scores)
{
vector<int>::const_iterator iter;
cout << "\nHighScores:\n";
    for(iter = scores.begin(); iter!=scores.end();++iter)
    {

        cout << *iter << endl;

    }

return 0;

}

int main()

{

vector<int>::const_iterator iter;
cout << "Creating list of scores.";

vector<int> scores;

scores.push_back(1500);
scores.push_back(3500);
scores.push_back(7500);

cout << "\nHigh Scores:\n";
showScores(scores);

int score;

cout << "\nEnter a highscore to find: ";

cin >> score;

iter = find(scores.begin(), scores.end(), score);

    if(iter != scores.end())
    {
        cout << "Score found.\n";

        
    }
    else
    {

        cout << "Score not found.\n";

    }

cout << "\nRandomizing scores.";

srand(static_cast<unsigned int>(time(0)));
mt19937 rng(static_cast<unsigned int>(time(0)));
shuffle(scores.begin(), scores.end(), rng);

showScores(scores);

cout << "\nSorting scores";

sort(scores.begin(), scores.end());
showScores(scores);

return 0;

}
