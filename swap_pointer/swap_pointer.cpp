#include <iostream>

using std::cout;

void badSwap(int x, int y);

void goodSwap(int* const pX, int* const pY);

int main()
{

int myScore = 150;

int yourScore = 1000;

cout << "Original values\n";

cout << "myScore: " << myScore << "\n";

cout << "yourScore: " << yourScore << "\n\n";

cout << "calling badSwap()\n";

badSwap(myScore, yourScore);

cout << "myScore: " << myScore << "\n";

cout << "yourScore: " << yourScore << "\n\n";

cout << "calling goodSwap()\n";

goodSwap(&myScore, &yourScore);

cout << "myScore: " << myScore << "\n";

cout << "yourScore: " << yourScore << "\n\n";

return 0;

}

void badSwap(int x, int y)
{

    int temp = x;

    x = y;

    y = temp;

}


void goodSwap(int* const pX, int* const pY)
{

    int temp = *pX;

    *pX = *pY;

    *pY = temp;

}