#include <iostream>

using std::cout;
using std::endl;
using std::cin;

class Critter
{
public:
    Critter(int hunger = 0, int boredom = 0);
    void Talk();
    void Eat(int food = 4);
    void Play(int fun = 4);
    void RevealMood();
    void GetHint();

private:
    int m_Hunger;
    int m_Boredom;
    enum hint{LITTLE = 5, HUNGRY = 10, STARVED = 15};     

    int GetMood() const;
    void GetHunger();
    void GetBored();
    void PassTime(int time = 1);
};

Critter::Critter(int hunger, int boredom):
    m_Hunger(hunger),
    m_Boredom(boredom)
{}

inline int Critter::GetMood() const
{
    return (m_Hunger + m_Boredom);
}

void Critter::GetHint()
{
    GetHunger();
    GetBored();
}

void Critter::PassTime(int time)
{
    m_Hunger += time;
    m_Boredom += time;
}

void Critter::Talk()
{
    cout << "I am a critter and i feel ";
    int mood = GetMood();

    if(mood > 15)
    {
        cout << "mad.\n";
    }
    else if(mood > 10)
    {
        cout << "frustrated.\n";
    }
    else if(mood > 5)
    {
        cout << "okay.\n";
    }
    else
    {
        cout << "happy.\n";
    }

    PassTime();
}

void Critter::Eat(int food)
{
    cout << "Omonomonom.\n";
    m_Hunger -= food;

    if(m_Hunger < 0)
    {
        m_Hunger = 0;
    }

    PassTime();
}

void Critter::Play(int fun)
{
    cout << "Wheeeeee!\n";
    m_Boredom -= fun;

    if(m_Boredom < 0)
    {
        m_Boredom = 0;
    }

    PassTime();
}

void Critter::RevealMood()
{
    cout << "Hunger is: " << m_Hunger << ".\n";
    cout << "Boredom is: " << m_Boredom << ".\n\n";
    PassTime();
}

void Critter::GetHunger()
{
    if(m_Hunger > STARVED)
    {
    cout << "I am a hungry a lot, need a food NOW.\n";
    }
    else if(m_Hunger > HUNGRY)
    {
    cout << "I am starving dude, NEED A FOOD NOW.\n";
    }
    else if(m_Hunger > LITTLE)
    {
    cout << "I am a little hungry, need a food.\n";
    }
    else
    {
        cout << "I am satiated with food.\n";
    }
}

void Critter::GetBored()
{
    if(m_Boredom > STARVED)
    {
    cout << "I am BORED TO DEATH, PLAY WITH ME NOW.\n";
    }
    else if(m_Boredom > HUNGRY)
    {
    cout << "I am monstrously bored, play with me NOW.\n";
    }
    else if(m_Boredom > LITTLE)
    {
    cout << "I am little bored, play with me.\n";
    }
    else
    {
    cout << "I am satiated with play.\n";
    }
}

int main()
{
    Critter crit;
    crit.Talk();

    int choice;
    do
    {
        cout << "\nCritter Caretaker\n\n";
        cout << "0 - Quit\n";
        cout << "1 - Listen to your critter\n";
        cout << "2 - Feed your critter\n";
        cout << "3 - Play with your critter\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 0:
                cout << "Goodbye.\n";
                break;
            case 1:
                crit.Talk();
                crit.GetHint();
                break;
            case 2:
                crit.Eat();
                break;
            case 3:
                crit.Play();
                break;
            default:
                cout <<"\nSorry but your: " << choice << "is not a valid choice.\n";
                crit.RevealMood();
        }
    }while(choice != 0);

    return 0;
}