#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

int numberCheck(string prompt = "Provide the number to check.\n");

int numberCheck(int number, string prompt = "Provide the number to check.\n");

int main()
{
    
numberCheck();
numberCheck("Dawaj liczbe.\n");
numberCheck(2);

return 0;

}

int numberCheck(string prompt)
{
int number;

cout << prompt;
cin >> number;

return number;

}

int numberCheck(int number, string prompt)
{

cout << prompt;

cin >> number;

return number;

}