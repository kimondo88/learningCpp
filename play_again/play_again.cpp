#include <iostream>

using std::cout;
using std::cin;

int main()

{

char again;


do 
{

cout << "\n**Played an exciting game**";
cout << "\nDo you wanna to play again (y/n): ";

cin >> again;

}while (again == 'y');

cout << "\nOkay. Bye.";

return 0;

}