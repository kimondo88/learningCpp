#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::vector;
using std::string;
using std::endl;

void display(const vector<string>& inventory);

int main()
{

vector<string> inventory;

inventory.push_back("sword");
inventory.push_back("armor");
inventory.push_back("shield");

display(inventory);

return 0;

}

void display(const vector<string>& vec)
{

cout << "your Items:\n";

    for(vector<string>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter)
    {

        cout << *iter << endl;
        
    }

}