#include <iostream>
#include <string>

using std::cout;
using std::string;

int radiation(int health);

int main()
{

int health = 80;

cout << "Your health is " << health << "\n\n";

health = radiation(health);

cout << "After radiation exposure your health is " << health << "\n\n";


health = radiation(health);

cout << "After radiation exposure your health is " << health << "\n\n";


health = radiation(health);

cout << "After radiation exposure your health is " << health << "\n\n";

return 0;

}

inline int radiation(int health)
{

return (health / 2);

}