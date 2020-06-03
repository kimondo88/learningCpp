#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::vector;

int showInv(vector<string> inventory)
{
vector<string>::const_iterator iter;
cout << "Your items: \n";

    for(iter = inventory.begin(); iter!=inventory.end();++iter)
    {

        cout << *iter << endl;

    }

return 0;

}


int main()

{

vector<string> inventory;

inventory.push_back("Sword");
inventory.push_back("Armor");
inventory.push_back("Shield");

vector<string>::iterator myIterator;

showInv(inventory);

cout << "\nYou trade your sword for a battle axe.";

myIterator = inventory.begin();
*myIterator = "Battle axe";

showInv(inventory);

cout << "\nThe item name '" << *myIterator << "' has";
cout << (*myIterator).size() << " letters in it.\n";

cout << "\nThe item name '" << *myIterator << "' has";
cout << myIterator -> size() << " letters in it.\n";

cout << "Your recover crossbow from a slain enemy.";

inventory.insert(inventory.begin(), "crossbow");

showInv(inventory);

cout << "\nYour armor is destroyed in a fierce battle.";

inventory.erase((inventory.begin() + 2));

showInv(inventory);
   
return 0;

}