#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::wstring;

class npc 
{
public: 
    npc(int m_nCoordinates = 1, int m_nHealth = 100, int m_fStrength = 100, int m_nSpeed = 2)
    {
        if (m_nCoordinates > 899)
            m_nCoordinates = 899;
        else if (m_nCoordinates < 0)
            m_nCoordinates = 0;
        else
            this -> m_nCoordinates = m_nCoordinates;

        if(m_nHealth < 0)
            m_nHealth = 100;
        else 
            this -> m_nHealth = m_nHealth;

        if(m_fStrength < 0)
            m_fStrength = 100;
        else 
            this -> m_fStrength = m_fStrength;

        this -> m_nSpeed = m_nSpeed;

        inventory = new vector<pair<wstring, int>>;

    }

    virtual int GetSymbol()
    {
        return symbol;
    }

    virtual int GetCoordinates()
    {
        return m_nCoordinates;
    }

    virtual int GetHealth()
    {
        return m_nHealth;
    }
    
    virtual int GetStrength()
    {
        return m_fStrength;
    }

    virtual int GetSpeed()
    {
        return m_nSpeed;
    }

    virtual void Move(int MOVE)
    {
        m_nCoordinates += MOVE;
    }

    virtual void SetStrength(int x)
    {
        if (m_fStrength >= x)
            m_fStrength -= x;
        else
            m_fStrength = 0;
    }

    vector<pair<wstring, int>> *inventory;


protected:
    int m_nCoordinates;
    int m_nHealth;
    int m_nSpeed;
    int m_fStrength;

    enum
    {
        symbol = 0x58,
    };

};

class resources 
{
public:
    resources(int m_nCoordinates = 0, int m_nQuantity = 100, int m_fWeight = 1, wstring m_sName = L"Tree")
    {
         if (m_nCoordinates > 899)
            m_nCoordinates = 899;
        else if (m_nCoordinates < 0)
            m_nCoordinates = 0;
        else
            this -> m_nCoordinates = m_nCoordinates;

        if(m_nQuantity < 0 || m_nQuantity > 300)
            m_nQuantity = 100;
        else 
            this -> m_nQuantity = m_nQuantity;

        this -> m_fWeight = m_fWeight;
        this -> m_sName = m_sName;
    }

    virtual wstring GetName()
    {
        return m_sName;
    }

    virtual int GetCoordinates()
    {
        return m_nCoordinates;
    }

    virtual int GetSymbol()
    {
        return symbol;
    }

    virtual int GetQuantity()
    {
        return m_nQuantity;
    }

    virtual int GetWeight()
    {
        return m_fWeight;
    }

    virtual bool RemoveQuantity(int quantity)
    {
        if (m_nQuantity >= quantity)
        {
            m_nQuantity -= quantity;
            return true;
        }
        else 
            return false;
    }

protected:
    int m_nCoordinates;
    int m_nQuantity;
    int m_fWeight;

    wstring m_sName;

    enum 
    {
        symbol = 0x40,
    };
};