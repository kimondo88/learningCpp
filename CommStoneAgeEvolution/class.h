class npc 
{
public: 
    npc(int m_nCoordinates = 1, int m_nHealth = 100)
    {
        //this -> m_nCoordinates = m_nCoordinates;
        //this -> m_nHealth = m_nHealth;
    };

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
    
protected:
    int m_nCoordinates;
    int m_nHealth;
    enum
    {
        symbol = 0x58,
    };
};

class resources
{
public:
    resources(int m_nCoordinates, int m_nQuantity = 100, float m_nWeight = 1.0f);
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
        return m_nWeight;
    }

protected:
    int m_nCoordinates;
    int m_nQuantity;
    float m_nWeight;

    enum 
    {
        symbol = 0x40,
    };
};