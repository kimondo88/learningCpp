#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

int main()

{

string username;
string password;

bool success;

cout << "\tGAmeDesigner's Network\n";

do 

{

cout << "\nUsername: ";
cin >> username;

cout << "\nPassword: ";
cin >> password;

    if(username == "S.Meier" && password == "civilization")

    {
        cout << "\nHey, Sid.";
        success = true;
    }

    else if (username == "S.Miyamoto" && password == "mariobros")
    {
        cout << "\nWhat's up shigeru?";
        success = true;
    }

    else if(username == "W.Wright" && password == "thesims")
    {
        cout << "'How goes it, will.";
        success = true;
    }

    else if (username == "guest" || password == "guest")
    {
        cout << "\nWelcome guest.";
        success = true;
    }

    else
    {
        cout << "\nYour login failed.";
        success = false;
    }

} while(!success);

return 0;

}
