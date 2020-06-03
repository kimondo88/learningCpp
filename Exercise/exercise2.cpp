#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::endl;

int showList(vector<string> gameList)
{
vector<string>::const_iterator iter;
int i = 0;
    for(iter = gameList.begin(); iter != gameList.end(); ++iter)
    {
        cout << i+1 << ". " << *iter << endl;
        ++i;
    }

return 0;

}

int main()

{
vector<string>::const_iterator iter;
vector<string>::iterator myIterator;
vector<string> gameList;
gameList.reserve(10);

gameList.push_back("god of");
gameList.push_back("spiderman");

myIterator = gameList.begin();

showList(gameList);

string title = "";

cout << "\nAdd your title: ";
getline(cin, title);
cout << title;
iter = find(gameList.begin(), gameList.end(), title);
    if(iter != gameList.end())
    {

        cout << "\nElement is in the list already\n";
        
    }
    else
    {
        
        cout << "\nAdding element to list: \n";
        gameList.push_back(title); 

    }
    
showList(gameList);

int toDelete = 0;

cout << "\nDelete the item from the game list. Choose title nr: \n";
cin >> toDelete;
//getline(cin, toDelete);

if(toDelete > 0)
{
    myIterator += toDelete-1;
    if(myIterator == gameList.end())
    {

    cout << "\nTitle is not on the list." << endl;

    }
    else
    {

    cout << "\nDeleting the title nr: " << toDelete << endl;
    gameList.erase((myIterator));
    
    }
    
}    

showList(gameList);

return 0;

}