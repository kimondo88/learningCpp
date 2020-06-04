#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::vector;
using std::string;
using std::endl;

string* ptrToElement(vector<string>* const pVec, int i);

int main()
{

vector<string> inventory;

inventory.push_back("sword");

inventory.push_back("armor");

inventory.push_back("shield");

cout << "sending the returned pointer count: \n";

cout << *(ptrToElement(&inventory, 0)) << "\n\n";

cout << "Assigning the returned pointer to another pointer.\n";

string* pStr = ptrToElement(&inventory, 1);

cout << "Sending the new pointer to cout: \n";

cout << *pStr << "\n\n";

cout << "Assigning the returned pointer to string object.\n";

string str = *(ptrToElement(&inventory, 2));

cout << "Sending the new string object to cout: \n";

cout << str << "\n\n";

cout << "Altering an object through a returned pointer.\n";

*pStr = "Healing potion";

cout << "Sending the altered object to cout:\n";

cout << inventory[1] << endl;

return 0;

}

string* ptrToElement(vector<string>* const pVec, int i)
{

return &((*pVec)[i]);

}
