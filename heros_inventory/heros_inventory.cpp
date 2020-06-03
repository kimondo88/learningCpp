#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int showInv(int numItems, string inventory[])
{

cout << "Your items: \n";

    for(int i = 0; i < numItems ; ++i)
    {
        cout << inventory[i] << endl;
        
    }

return 0;

}

int main()

{

const int MAX_ITEMS = 10;
string inventory[MAX_ITEMS];
int numItems = 0;


inventory[numItems++] = "Sword";
inventory[numItems++] = "Armor";
inventory[numItems++] = "Shield";

showInv(numItems, inventory);

cout << "\nYOu trade your sword for battleaxe.";

inventory[0] = "Battle axe";

showInv(numItems, inventory);

cout << "\nThe Item name '" << inventory[0] << " has ";
cout << inventory[0].size() << "letters in it \n";
cout << "\nYou find a healing potion";

    if(numItems < MAX_ITEMS)
    {

    inventory[numItems++] = "He3aling potion";

    }
    else 
    {

        cout << "You have too many items and can't carry another.";
        
    }

showInv(numItems, inventory);

return 0;

}

