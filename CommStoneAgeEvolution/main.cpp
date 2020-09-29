#include <iostream>
#include "..\olcConsoleGameEngine.h"
#include "class.h"
#include <vector>
#include <random>
#include <chrono>
#include <string>

using std::vector;
using std::mt19937;
using std::to_wstring; 
using std::string;
using std::pair;
using std::make_pair;

class olcStoneAgeEvo : public olcConsoleGameEngine
{
public:
    olcStoneAgeEvo()
    {
        m_sAppName = L"StoneAgeEvolution";
    }

    ~olcStoneAgeEvo()
    {
        delete[] m_stone;
        delete m_vCharacters;
    }
    npc symbolNpc;
    resources symbolResources;

private:
    int m_nStoneWidth;
    int m_nStoneHeight;
    int *m_stone;

    int m_nBorder;
    int m_nControl; 
    int m_nEvent;
    bool DKeyHold = false;

    vector<npc> *m_vCharacters;
    vector<resources> *m_vResources;

    enum
    {
        CELL_WOOD= 0x012,
        CELL_HUMAN_NPC = 0x38F,
    };

    virtual bool Populate(vector<npc> *m_vCharacters, vector<resources> *m_vResources)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        mt19937 random(seed);
        int c;

        // add new npc to vectors
        for ( int i = 0; i < 5 ; i++)
        {
            c = random() % 900 ;
            m_vCharacters->push_back(npc(c, 100, 100, 75));
        }

        for ( int i = 0; i < 5 ; i++)
        {
            c = random() % 900 ;
            m_vResources->push_back(resources(c, 100));
        }
        return true;
    }

    virtual void RefreshPosition(vector<npc> *m_vCharacters)
    {
        for ( auto i = m_vCharacters->begin(); i != m_vCharacters->end(); ++i)
        {
            m_stone[i->GetCoordinates()] = i->GetSymbol();
        }
    }

    virtual void RefreshPosition(vector<resources> *m_vResources)
    {
        for ( auto i = m_vResources->begin(); i != m_vResources->end(); ++i)
        {
            m_stone[i->GetCoordinates()] = i->GetSymbol();
        }
    }

    virtual void AttemptMove(vector<npc> *m_vCharacters)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        mt19937 random(seed);

        for ( auto i = m_vCharacters->begin(); i != m_vCharacters->end(); ++i)
        {
            switch(random() % 4)
            {
                case 0:
                    //check if npc can move and not collide with left
                    if ((m_stone[i->GetCoordinates() + LEFT] == 0x00) && (i->GetCoordinates() % m_nStoneWidth) != 0)
                    {
                        m_stone[i->GetCoordinates()] = 0x00;
                        i->Move(LEFT);
                    }
                    break;
            
                case 1:
                    //check if npc can move and not collide with right
                    if ((m_stone[i->GetCoordinates() + RIGHT] == 0x00) && (((i->GetCoordinates() + 1 ) % m_nStoneWidth) != 0))
                    {
                        m_stone[i->GetCoordinates()] = 0x00;
                        i->Move(RIGHT);
                    }
                    break;

                case 2:
                    //check if ncp can move and not collide with up
                    if (m_stone[i->GetCoordinates() + UP] == 0x00 && (i->GetCoordinates() >= m_nStoneWidth))
                    {
                        m_stone[i->GetCoordinates()] = 0x00;
                        i->Move(UP);
                    }
                    break;

                case 3:
                    //check if ncp can move and not collide with DOWN
                    if (m_stone[i->GetCoordinates() + DOWN] == 0x00 && (i->GetCoordinates() < 870))
                    {
                        m_stone[i->GetCoordinates()] = 0x00;
                        i->Move(DOWN);
                    }
                    break;

                default:
                    break;
            }
        }

    }

    virtual bool Gather(resources &toGather,npc &Gatherer)
    {
        // check resource weight, if enough decrease quantity and get resource weight to npc, apply resource to npc inventory
        if ( Gatherer.GetStrength() /*- toGather.GetWeight()*Gatherer.GetSpeed()*/ > 0)
        {
            if (toGather.GetQuantity() > Gatherer.GetSpeed())
            {
                toGather.RemoveQuantity(Gatherer.GetSpeed());
                Gatherer.SetStrength(toGather.GetWeight()*Gatherer.GetSpeed());
                Gatherer.inventory->push_back(make_pair(toGather.GetName(), toGather.GetWeight()*Gatherer.GetSpeed()));
                TestCode(toGather.GetQuantity(), 5);
                TestCode(Gatherer.GetStrength(), 6);
                return true;
            }
            else
            {
                Gatherer.SetStrength(0);
                Gatherer.inventory->push_back(make_pair(toGather.GetName(), toGather.GetWeight()*toGather.GetQuantity()));
                toGather.RemoveQuantity(toGather.GetQuantity());
                TestCode(toGather.GetQuantity(), 5);
                TestCode(Gatherer.GetStrength(), 6);
                return false;
            }
            return true;
        }
        else
        {
            // make npc go store the inventory into warehouse
            return true;
        }
    }

    //function npc do stuff - pick one to do.
    virtual void DecideToDo(vector<npc> m_vCharacters, vector<resources> m_vResources)
    {
        int quantityOfRes = m_vResources.size();
        //TestCode(quantityOfRes, 2);
        
        for (auto i = m_vCharacters.begin(); i != m_vCharacters.end(); ++i)
            //for(auto r = m_vResources.begin(); r != m_vResources.end(); ++r)
            {
                int r = 0;
                if(quantityOfRes >= 0)
                {
                    bool delResource = Gather(m_vResources.at(0+r), *i);
                    TestCode(777, 0);
                    if (!delResource)
                    {
                        //refresh position 
                        m_vResources.erase(m_vResources.begin()+r);
                        m_stone[(m_vResources.begin()+r)->GetCoordinates()] = 0x00;
                        TestCode(898, 1);
                    }
                    quantityOfRes--;
                    r++; 
                    TestCode(m_vResources.at(0+r).GetQuantity(), 2);
                }
            }
    }

    //test code to check if something works
    void TestCode(int testCode, int x)
    {
    DrawString(3+x + m_nBorder + m_nControl, 3+x + m_nBorder , to_wstring(testCode), FG_RED);
    }

protected:
    virtual bool OnUserCreate()
    {
        // game screen parameters
        m_nStoneWidth = 30;
        m_nStoneHeight = 30;
        m_stone = new int[m_nStoneWidth * m_nStoneHeight];
        m_vCharacters = new vector<npc>;
        m_vResources = new vector<resources>;

        m_nBorder = 10;
        m_nControl = 50;
        m_nEvent = 50;

        memset(m_stone, 0x00, m_nStoneWidth * m_nStoneHeight);

        // create basic npcs
        Populate(m_vCharacters, m_vResources);
        // populate and create world
        RefreshPosition(m_vResources);
        
        //Draw borders for Game Screen windows
        DrawLine(9, 9, 40, 9, PIXEL_SOLID, FG_WHITE);
        DrawLine(9, 40, 40, 40, PIXEL_SOLID, FG_WHITE);
        DrawLine(9, 9, 9, 40, PIXEL_SOLID, FG_WHITE);
        DrawLine(40, 9, 40, 40, PIXEL_SOLID, FG_WHITE);

        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime)
    {
        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
            OnUserDestroy();
        if (GetAsyncKeyState((unsigned short)'D') & 0x8000 && !DKeyHold)
        {
            AttemptMove(m_vCharacters);
            DKeyHold = true;
        }
        else
            DKeyHold = false;

        RefreshPosition(m_vCharacters);
        //make npc gather stuff if gather false the delete resource then refresh position
        if (GetAsyncKeyState((unsigned short)'E') & 0x8000)
        {
            DecideToDo(*m_vCharacters, *m_vResources);
        }
        if (GetAsyncKeyState((unsigned short)'Q') & 0x8000)
        {
            DecideToDo(*m_vCharacters, *m_vResources);
        }
        
        //clear game screen window
        Fill(m_nBorder, m_nBorder, m_nStoneWidth+10, m_nStoneHeight+10, L' ');
        // clear Player interface window
        Fill(m_nBorder + m_nControl, m_nBorder, m_nStoneWidth, m_nStoneHeight, L' ');
        // clear Event interface window


        //npc walks and do smth

        // Draw Game Screen Window
        for (int x = 0; x < m_nStoneWidth; x++)
            for( int y = 0 ; y < m_nStoneHeight ; y++)
                if(m_stone[y*m_nStoneWidth + x] == symbolNpc.GetSymbol() || m_stone[y*m_nStoneWidth + x] == symbolResources.GetSymbol() )
                    Draw(x + m_nBorder, y + m_nBorder, m_stone[y*m_nStoneWidth + x], FG_GREEN);
        // Draw Control Player Interface Window
        for (int x = 0; x < 1; x++)
            for( int y = 0 ; y < 2 ; y++)
            {
                DrawString(x + m_nBorder + m_nControl, y + m_nBorder , to_wstring(555), FG_RED);
                //if  (y == 3)
                //    DrawString(x + m_nBorder + m_nControl, y + m_nBorder , , FG_RED);
            }
        // Draw Event Interface Window
        for (int x = 0; x < 1; x++)
            for( int y = 0 ; y < 2 ; y++)
                DrawString(x + m_nBorder + m_nControl/2, y + m_nBorder + m_nEvent , L"Event", FG_BLUE);
        return true;
        
    }

    virtual bool OnUserDestroy()
    {
        delete[] m_bufScreen;
        delete[] m_stone;
		SetConsoleActiveScreenBuffer(m_hOriginalConsole);
		m_cvGameFinished.notify_one();
        m_stone = nullptr;
        return true;
    }

    enum MOVE
    {
        UP = -30,
        LEFT = -1,
        RIGHT = 1,
        DOWN = 30,
    };
};

int main()
{

olcStoneAgeEvo game;
game.ConstructConsole(100, 100, 8, 8);
game.Start();

return 0;

}

