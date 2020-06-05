#include <iostream>

using std::cout;

class Critter //class definition
{
public:
    int m_Hunger; // data memeber
    void Greet(); //memeber function prototype
};

void Critter::Greet() // member function definition
{
    cout << "Hi. I'm a critter. My hunger level is " << m_Hunger << ".\n";
}

int main()
{
    Critter crit1;
    Critter crit2;

    crit1.m_Hunger = 9;
    cout << "Crit1 hunger level is " << crit1.m_Hunger << ".\n";

    crit2.m_Hunger = 3;
    cout << "Crit2 hunger level is " << crit2.m_Hunger << ".\n";

    crit1.Greet();
    crit2.Greet();

    return 0;
}