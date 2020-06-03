#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;
using std::shuffle;
using std::mt19937;
using std::vector;
using std::string;

char getGuess(string used);

string checkGuess(string The_WORD, string soFar, char guess);

int checkWrong(string THE_WORD, char guess, int wrong);

void checkWord(string THE_WORD, string soFar);

int main()

{

const int MAX_WRONG = 8;

vector<string> words;

words.push_back("GUESS");
words.push_back("HANGMAN");
words.push_back("DIFFICULT");

mt19937 rng(static_cast<unsigned int>(time(0)));

shuffle(words.begin(), words.end(), rng);

const string THE_WORD = words[0];

int wrong = 0;

string soFar(THE_WORD.size(), '-');
string used = "";

cout << "Welcome to Hangman. Good luck.\n";

    while((soFar != THE_WORD) && (wrong < MAX_WRONG))
    {

        cout << "You have " << (MAX_WRONG - wrong);
        cout << "\nIncorrect guesses left.\n";
        
        cout << "You have used the following letters: \n" << used << endl;
        cout << "So far the word is: " << soFar << endl;

        char guess = getGuess(used);
        used += guess;
        soFar = checkGuess(THE_WORD, soFar, guess);
        wrong = checkWrong(THE_WORD, guess, wrong);
        
    }

checkWord(THE_WORD, soFar);

return 0;

}

char getGuess(string used)
{
    char guess;

    cout << "\nEnter your guess: " ; 

    cin >> guess;

    guess = toupper(guess);

    while(used.find(guess) != string::npos)
    {
        cout << "\nYou have already guessed " << guess << endl;
        cout << "\nEnter your guess: ";

        cin >> guess;

        guess = toupper(guess);

    }

return guess;

}

string checkGuess(string THE_WORD, string soFar, char guess)
{

if(THE_WORD.find(guess) != string::npos)
    {

        cout << "\nThats right!" << guess << " is in the word.\n";
        for( int i = 0; i < THE_WORD.length(); ++i)
        {
            if(THE_WORD[i] == guess)
            {

            soFar[i] = guess;

            }

        }
    }
    
return soFar; 
}


int checkWrong(string THE_WORD, char guess, int wrong)
{

    if(THE_WORD.find(guess) == string::npos)
    {
        cout << "Incorect guess. Guess again.\n";
        ++wrong;
    }

return wrong;

}

void checkWord(string THE_WORD, string soFar)
{

    if(soFar == THE_WORD)
    {

        cout << "\nCongratulations, you guessed it." << soFar << " was the word.\n";

    }
    else
    {

        cout << " You are hanged by mob.\n";

    }

}