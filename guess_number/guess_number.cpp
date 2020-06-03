#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

int main()

{

srand(static_cast<unsigned int>(time(0))); //seeding number
int secretNumber = rand() % 100 + 1;

int tries = 0;
int guess;

cout << "\nWelcome to guess my Number.\n\n ";

do

{

cout << "Enter a guess: ";
cin >> guess;

++tries; 

    if(guess > secretNumber)
    {

    cout << "Too high!\n\n";

    }

    else if(guess < secretNumber)
    {

    cout << "Too low!\n\n";

    }

    else
    {

    cout << "That's it you guessed\n\n";
    cout << "Tries: " << tries << endl; 
    
    }


}while(guess != secretNumber);


return 0;

}








































































