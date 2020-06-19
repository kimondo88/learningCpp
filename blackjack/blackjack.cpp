//writing black jack game -its learing code so mutliple classes in one file
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

using std::cout;
using std::cin;
using std::endl;
using std::mt19937;
using std::string;
using std::vector;
using std::ostream;
using std::shuffle;

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

class GenericPlayer : public Hand
{
friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
public:
    GenericPlayer(const string& name= "");
    virtual ~GenericPlayer();
    virtual bool IsHitting() const = 0; // whether the player wants to keep hitting
    bool IsBusted() const; // return whether the player is busted - total greater than 21.
    void Bust() const; //annoucnes player busts
protected:
    string m_Name;
};

GenericPlayer::GenericPlayer(const string& name):
    m_Name(name)
{}

GenericPlayer::~GenericPlayer()
{}

bool GenericPlayer::IsBusted() const
{
    return (GetTotal() > 21);
}

void GenericPlayer::Bust() const
{
    cout << m_Name << " busts.\n";
}

class Player : public GenericPlayer
{
public:
    Player(const string& name = "");
    virtual ~Player();
    virtual bool IsHitting() const; //announces wheter the player is hitting
    void Win() const; // announces player wins.
    void Lose() const;
    void Push() const;
};

Player::Player(const string& name):
    GenericPlayer(name)
{}

Player::~Player()
{}

bool Player::IsHitting() const
{
   cout << m_Name << ", do you wanna hit? (Y/N): ";
   char response;
   cin >> response;
   return (response == 'y' || response == 'Y');
   return true;
}

void Player::Win() const
{
    cout << m_Name << " wins.\n";
}

void Player::Lose() const
{
    cout << m_Name << " loses.\n";
}

void Player::Push() const
{
    cout << m_Name << " pushes.\n";
}

class House : public GenericPlayer
{
public:
    House(const string& name = "House");
    virtual ~House();
    virtual bool IsHitting() const;
    void FlipFirstCard();
};

House::House(const string& name):
    GenericPlayer(name)
{}

House::~House()
{}

bool House::IsHitting() const
{
    return (GetTotal() <= 16);
}

void House::FlipFirstCard()
{
    if(!(m_Cards.empty()))
    {
        m_Cards[0]->Flip();
    }
    else
    {
        cout << "No card to flip!\n";
    }
}

class Deck : public Hand
{
public:
    Deck();
    virtual ~Deck();
    void Populate(); //create standard deck of 52 cards.
    void Shuffle(); //shuffle cards.
    void Deal(Hand& aHand); // gives additional card to player.
    void AdditionalCards(GenericPlayer& aGenericPlayer);
};

Deck::Deck()
{
    m_Cards.reserve(52);
    Populate();
}

Deck::~Deck()
{}

void Deck::Populate()
{
    Clear();
    for(int s = Card::CLUBS; s <= Card::SPADES; ++s)
    {
        for(int r= Card::ACE; r <= Card::KING; ++r)
        {
            Add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
        }
    }
}

void Deck::Shuffle()
{
    mt19937 rng(static_cast<unsigned int>(time(0)));
    shuffle(m_Cards.begin(), m_Cards.end(), rng);
}

void Deck::Deal(Hand& aHand)
{
    if(!m_Cards.empty())
    {
        aHand.Add(m_Cards.back());
        m_Cards.pop_back();
    }
    else
    {
        cout << "Out of cards. Unable to deal.";
    } 
}

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer)
{
    cout << endl; // continue to deal cards as long a generic player isnt busted.
    while(!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
    {
        Deal(aGenericPlayer);
        cout << aGenericPlayer << endl;
    }
    if(aGenericPlayer.IsBusted())
    {
        aGenericPlayer.Bust();
    }
}

class Game
{
public:
    Game(const vector<string>& names);
    ~Game();
    void Play(); // plays the gaem of black jack.
private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;
};

Game::Game(const vector<string>& names)
{
    //create a vectpr players form vector names
    vector<string>::const_iterator pName;
    for(pName = names.begin(); pName != names.end(); ++pName)
    {
        m_Players.push_back(*pName);
    }
    m_Deck.Populate();
    m_Deck.Shuffle();
}

Game::~Game()
{}

void Game::Play()
{
    //deal initial 2 cards to everyone.
    vector<Player>::iterator pPlayer;
    for(int i=0; i < 2; ++i)
    {
        for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            m_Deck.Deal(*pPlayer);
        }
        m_Deck.Deal(m_House);
    }
    //hide house first card.
    m_House.FlipFirstCard();
    //display everyone hands.
    for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        cout << *pPlayer << endl;
    }
    cout << m_House << endl;
    //deal additional cards to players.
    for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        m_Deck.AdditionalCards(*pPlayer);
    }
    //reveal house first card.
    m_House.FlipFirstCard();
    cout << endl << m_House;
    //deal additional cards to house.
    m_Deck.AdditionalCards(m_House);
    if(m_House.IsBusted())
    {
        //everyone still playing wins.
        for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            if(!(pPlayer->IsBusted()))
            {
                pPlayer->Win();
            }
        }

    }
    else
    {
        for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            if(!(pPlayer->IsBusted()))
            {
                if(pPlayer->GetTotal() > m_House.GetTotal())
                {
                    pPlayer->Win();
                }
                else if(pPlayer->GetTotal() < m_House.GetTotal())
                {
                    pPlayer->Lose();
                }
                else
                {
                    pPlayer->Push();
                }
            }
        }
    }
// remove everyone cards.
    for(pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        pPlayer->Clear();
    }
    m_House.Clear();

}

//function protypes
ostream& operator<<(ostream& os, const Card& aCard);
ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);

int main()
{
    cout << "\t\tWelcome to blackjack!\n\n";
    int numPlayers = 0;
    while(numPlayers < 1 || numPlayers > 7)
    {
        cout << "How many players? (1 - 7): ";
        cin >> numPlayers;
    }    
    vector<string> names;
    string name;

    for(int i = 0; i < numPlayers ; ++i)
    {
        cout << "Please enter player name: ";
        cin >> name;
        names.push_back(name);
    }
    cout << endl;
    // the game loop.
    Game aGame(names);
    char again = 'y';

    while(again != 'n' && again !='N')
    {
        aGame.Play();
        cout << "Do you wanna play again (Y/N)";
        cin >> again;
    }

return 0;

}

ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = {"0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10",
    "J", "Q", "K"};
    const string SUITS[] = {"c", "d" , "h", "s"};
    if(aCard.m_IsFaceUp)
    {
        os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
    }
    else
    {
        os << "XX";
    }
    
    return os;
}

ostream