#include <iostream> //demonstrate abstract classes

using std::cout;

class Creature //abstract class
{
public:
    Creature(int health = 100);
    virtual void Greet() const = 0; //pure virtual member function
    virtual void DisplayHealth() const;
protected:
    int m_Health;
};

Creature::Creature(int health):
    m_Health(health)
{}

void Creature::DisplayHealth() const
{
    cout << "Health: " << m_Health << "\n";
}

class Orc : public Creature
{
public:
    Orc(int health = 100);
    virtual void Greet() const;
};

Orc::Orc(int health):
   Creature(health)
{}

void Orc::Greet() const
{
    cout << "The orc grunts hello.\n";
}

class OrcBoss : public Orc
{
public:
    OrcBoss(int health = 180);
    virtual void Greet() const;
};

OrcBoss::OrcBoss(int health):
    Orc(health)
{}

void OrcBoss::Greet() const
{
    cout << "The orc boss growls hello\n";
}

int main() 
{
    Creature* pCreature = new OrcBoss();
    pCreature->Greet();
    pCreature->DisplayHealth();

    return 0;
}