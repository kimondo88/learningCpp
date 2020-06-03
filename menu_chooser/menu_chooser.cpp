#include <iostream>

using std::cout;
using std::cin;

int main()

{

cout << "Difficulty levels\n\n";
cout << "1 - Easy\n";
cout << "2 - Normal\n";
cout << "3 - Hard\n\n";

int choice;

cout << "Choice: ";

cin >> choice;

    switch(choice)

    {

    case 1:    

    cout << "You picked Easy.\n";
    break;

    case 2:

    cout << "You picked Normal.\n";
    break;

    case 3:

    cout << "You picked Hard.\n";
    break;

    default:

    cout << "Invalid choice.\n";
    break;

    }

return 0;

}