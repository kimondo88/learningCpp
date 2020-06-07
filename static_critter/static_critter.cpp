//demonstrates static memeber and functions
#include <iostream>

using std::cout;
using std::endl;

class Critter
{
public: 
    static int s_Total; // static member definition, totla number of critters

    Critter(int hunger = 0);
    static int GetTotal();

private:
    int m_Hunger;
};

int Critter::s_Total = 0; // static member variable initialization

Critter::Critter(int hunger):
    m_Hunger(hunger)
{
    cout << "A critter has been born!" << endl;
    ++s_Total;
}

int Critter::GetTotal() // static mmeber function definition
{
    return s_Total;
}

int main()
{
    cout << "The total number of critters is: ";
    cout << Critter::s_Total << "\n\n";

    Critter crit1, crit2, crit3;

    cout << "\nThe total number of critter is: ";
    cout << Critter::GetTotal() << "\n\n";

    return 0;
}