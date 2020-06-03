#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::vector;

int showInv(vector<string> inventory)
{

cout << "Your items: \n";

    for(unsigned int i = 0; i < inventory.size() ; ++i)
    {
        cout << inventory[i] << endl;
        
    }

return 0;

}


int main()

{

vector<string> inventory;

inventory.push_back("Sword");
inventory.push_back("Armor");
inventory.push_back("Shield");

cout << "You have: " << inventory.size() << "items.\n";
showInv(inventory);

cout << "\nYou trade your sword for a battle axe.";

inventory[0] = "Battle axe";

showInv(inventory);

cout << "\nThe item name '" << inventory[0] << "' has ";
cout << inventory[0].size() << " letters in it.\n";

cout << "Your shield is destroyed in a fierce battle.";

inventory.pop_back();

showInv(inventory);
cout << "\nYou were robbed of all your possesion by thief.";
inventory.clear();
    if(inventory.empty())
    {

        cout << "\nYou have nothing.";
        
    }
    else
    {

        cout << "\nYou have at least one item.";
        
    }
    
return 0;
}