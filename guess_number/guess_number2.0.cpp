#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::floor;
int main()

{

srand(static_cast<unsigned int>(time(0))); //seeding number
int secretNumber;

int tries = 0;
int max = 100;
int min = 1; 
int guess = 0;
cout << "\nWelcome to guess my Number.\n\n ";
cout << "Enter a number between 1 and 100: ";
cin >> secretNumber;
do

{

++tries;

if(tries > 0)
{
   guess = (max + min ) / 2 ;  
   guess = floor(guess);
}
//else if(tries == 8)
//{
//    break;
//}
    if(secretNumber < guess)
    {

    cout << "Too high! "<< guess << "\n\n";
    max = guess; 

    }

    else if(secretNumber > guess)
    {

    cout << "Too low! " << guess << "\n\n";
    min = guess;
    }

    else
    {

    cout << "That's it you guessed." << guess << "\n\n";
    cout << "Tries: " << tries << endl; 
    
    }


}while(guess != secretNumber);


return 0;

}


