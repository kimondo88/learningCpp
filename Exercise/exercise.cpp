#include <iostream>

using std::cout;
using std::cin;
using std::endl; 
int main() 

{

int firstScore, secondScore, thirdScore = 0; 

cout << "Please enter the first score: ";
cin >> firstScore; 

cout << "\nPlease enter the second score: ";
cin >> secondScore; 

cout << "\nPlease enter the third score: ";
cin >> thirdScore; 

float average = (firstScore + secondScore + thirdScore) / 3 ;

cout << "\nYour score average is: " << average << endl; 

return 0;

}