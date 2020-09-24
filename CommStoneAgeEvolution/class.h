class npc 
{
public: 
    npc(int m_nCoordinates = 1, int m_nHealth = 100)
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
    
    virtual void Move(int MOVE)
    {
        m_nCoordinates += MOVE;
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
    resources(int m_nCoordinates, int m_nQuantity = 100, float m_nWeight = 1.0f)
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