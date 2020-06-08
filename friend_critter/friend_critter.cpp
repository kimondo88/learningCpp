#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::ostream;

class Critter
{
    friend void Peek(const Critter& aCritter); // friend global function of Critter class
    friend ostream& operator<<(ostream& os, const Critter& aCritter);
public:
    Critter(const string& name="");
private:
    string m_Name;
};

Critter::Critter(const string& name):
    m_Name(name)
{}

void Peek(const Critter& aCritter);

ostream& operator <<(ostream& os, const Critter& aCritter);

int main()
{
    Critter crit("poochie");
    cout << "Calling peek() to access crit private data memeber m_Name: \n";
    Peek(crit);

    cout << "\nSending crit object to cout with the << operator:\n";
    cout << crit;

    return 0;
}

//global friend function which can acces all of a critter object members.

void Peek(const Critter& aCritter)
{
    cout << aCritter.m_Name << endl;
}

ostream& operator <<(ostream& os, const Critter& aCritter)
{
    os << "Critter Object - ";
    os << "m_name: " << aCritter.m_Name;
    return os;
}

