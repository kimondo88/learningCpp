#include <iostream>

using std::cout;
using std::cin; 

int main()

{

int score;

cout << "Enter the score: ";

cin >> score; 

if(score >= 1000)

{

cout << "You scored 1000 or more. Impressive!\n";

}

else if(score >= 500)

{

cout << "You scored 500 or more. Nice.\n";

}

else if(score >= 250)

{

cout << "You scored 250 or more. Decent.\n";    

}

else 

{

cout << "Ya bloody fuckoff. Get the sauce.\n";

}

return 0;

}
