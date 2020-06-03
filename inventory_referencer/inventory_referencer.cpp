#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::vector;
using std::string;
using std::endl;

string& refToElement(vector<string>& inventory, int i);

int main()
{

vector<string> inventory;

inventory.push_back("sword");

inventory.push_back("armor");

inventory.push_back("shield");

cout << "sending the returned reference count: \n";

cout << refToElement(inventory, 0) << "\n\n";

cout << "Assigning the returned reference to another reference.\n";

string& rStr = refToElement(inventory, 1);

cout << "Sending the new reference to cout: \n";

cout << rStr << "\n\n";

cout << "Assigning the returned reference to string object.\n";

string str = refToElement(inventory, 2);

cout << "Sending the new string object to cout: \n";

cout << str << "\n\n";

cout << "Altering an object through a returned reference.\n";

rStr = "Healing potion";

cout << "Sending the altered object to cout:\n";

cout << inventory[1] << endl;

return 0;

}

string& refToElement(vector<string>& vec, int i)
{

return vec[i];

}
