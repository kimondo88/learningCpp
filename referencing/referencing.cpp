#include <iostream>
#include <string>

using std::cout;

int main()
{

int myScore = 1000;

int& mikesScore = myScore;

cout << "myScore is: " << myScore << "\n";

cout << "mikesScore is: " << mikesScore << "\n\n";

cout << "Adding 500 to myScore\n";

myScore += 500;

cout << "myScore is: " << myScore << "\n";

cout << "mikesScore is: " << mikesScore << "\n\n";

cout << "Adding 1000 to mikesScore\n"; 

mikesScore += 1000;

cout << "myScore is: " << myScore << "\n";

cout << "mikesScore is: " << mikesScore << "\n\n";

return 0;

}