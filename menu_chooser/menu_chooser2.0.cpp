#include <iostream>

using std::cout;
using std::cin;

int main()

{

cout << "Difficulty levels\n\n";
cout << "1 - Easy\n";
cout << "2 - Normal\n";
cout << "3 - Hard\n\n";

enum choice {EASY = 1, NORMAL, HARD};
int choice;

cout << "Choice: ";

cin >> choice;

    switch(choice)

    {

    case EASY:    

    cout << "You picked Easy.\n";
    break;

    case NORMAL:

    cout << "You picked Normal.\n";
    break;

    case HARD:

    cout << "You picked Hard.\n";
    break;

    default:

    cout << "Invalid choice.\n";
    break;

    }

return 0;

}