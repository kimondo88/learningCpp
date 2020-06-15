//writing black jack game -its learing code so mutliple classes in one file
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using std::cout;
using std::cin;
using std::endl;
using std::mt19937;
using std::string;
using std::vector;
using std::ostream;

class Card
{
public:
    enum rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                JACK, QUEEN, KING};
    enum suit {CLUBS, DIAMONDS, HEARTS, SPADES};
    friend ostream& operator<<(ostream& os, const Card& aCard); // overloading << op so to send card object to stadnard output.
    Card(rank r = ACE, suit s = SPADES, bool ifu = true);
    int GetValue() const; // get value of a card 1-11
    void Flip(); // flips a card.
private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu):
    m_Rank(r), m_Suit(s), m_IsFaceUp(ifu)
{}

int Card::GetValue() const
{
    int value = 0; // if value face is down
    if(m_IsFaceUp)
    {
        value = m_Rank; // value is number showing on card
        if (value > 10)
        {
            value = 10;
        }
    }
    return value;
}

void Card::Flip()
{
    m_IsFaceUp = !(m_IsFaceUp);
}

class Hand
{
public:
    Hand();
    virtual ~Hand();
    void Add(Card* pCard); // adds card to hand
    void Clear(); // clear hand of all cards
    int GetTotal() const;
protected:
    vector<Card*> m_Cards;
};

Hand::Hand()
{
    m_Cards.reserve(7);
}

Hand::~Hand()
{
    Clear();
}

void Hand::Add(Card* pCard)
{
    m_Cards.push_back(pCard);
}

void Hand::Clear()
{
    vector<Card*>::iterator iter= m_Cards.begin(); // iterate trough vector, free memory.
    for(iter = m_Cards.begin(); iter !=m_Cards.end(); ++iter)
    {
        delete *iter;
        *iter = 0;
    }
    m_Cards.clear(); // clear vector of pointers.
}

int Hand::GetTotal() const
{
    if(m_Cards.empty())
    {
        return 0;
    }
    if(m_Cards[0] -> GetValue() == 0) // if first card is 0 then that card is face down
    {
        return 0;
    }
    int total = 0; //add up values trear ace like 1.
    vector<Card*>::const_iterator iter;
    for(iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        total += (*iter) -> GetValue();
    }

    bool containsAce = false;
    for(iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        if((*iter) -> GetValue() == Card::ACE)
        {
            containsAce = true;
        }
    }
    if(containsAce && total <= 11) // if hands contain ace and total is low enough treat ace like 11.
    {
        total +=10;
    }
    return total;
}

