#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()

{

enum fields{WORD, HINT, NUM_FIELDS};

int points = 0; 
const int goodAnswer = 4;
const int hintAnswer = 1; 
const int NUM_WORDS = 5;

const string WORDS[NUM_WORDS][NUM_FIELDS] = {{"wall", "DO you feel like banging your head against something?"},
{"glasses", "These might help you see the answer."},
{"labored","Going slowly, is it?"},
{"persistend", "Keep doing it."},
{"jumble","Its what the game is about."}};

srand(static_cast<unsigned int>(time(0)));

int choice = (rand() % NUM_WORDS);

string theWord = WORDS[choice][WORD];
// word to guess

string theHint = WORDS[choice][HINT];
// hint for word

string jumble = theWord;
int length = jumble.size();

    for(int i = 0; i < length; ++i)
    {

    int index1 = (rand() % length);
    int index2 = (rand() % length);

    char temp = jumble[index1];

    cout << "\n" << temp;

    jumble[index1] = jumble[index2];
    cout << "\n" << jumble[index1];        

    jumble[index2] = temp; 
    }

cout << "\t\t\tWelcome to word jumble!\n\n";
cout << "Unscamble the letters to make a word.\n";
cout << "Enter 'hint' for a hint.\n";

cout << "Enter 'quit' to quit game. \n\n";
cout << "The jumble is: " << jumble;

string guess;

cout << "\n\nYour guess: ";

cin >> guess; 

    while((guess != theWord) && (guess != "quit"))
    {

        if(guess == "hint")
        {
        points -= hintAnswer; 
        cout << theHint;

        }
        else
        {
            
        cout << "Thats not it.";

        }

    cout << "\n\nYour guess: ";
        
    cin  >> guess;

    }

if(guess == theWord)
{
points += goodAnswer;
cout << "\nThats it you guessed it! You gained: " << points << " points.\n";

}

cout << "\nThanks for playing.\n";
return 0;

}