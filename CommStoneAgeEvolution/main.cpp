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

private:
    int m_nStoneWidth;
    int m_nStoneHeight;
    int *m_stone;

    int m_nBorder;
    int m_nControl; 
    int m_nEvent;
    bool DKeyHold = false;

    vector<npc> *m_vCharacters;

    enum
    {
        CELL_WOOD= 0x012,
        CELL_HUMAN_NPC = 0x38F,
    };

    virtual bool Populate(vector<npc> *m_vCharacters)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        mt19937 random(seed);
        int c;

        // add new npc to vectors
        for ( int i = 0; i < 5 ; i++)
        {
            c = random() % 900 ;
            m_vCharacters->push_back(npc(c, 100));
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

protected:
    virtual bool OnUserCreate()
    {
        // game screen parameters
        m_nStoneWidth = 30;
        m_nStoneHeight = 30;
        m_stone = new int[m_nStoneWidth * m_nStoneHeight];
        m_vCharacters = new vector<npc>;

        m_nBorder = 10;
        m_nControl = 50;
        m_nEvent = 50;

        memset(m_stone, 0x00, m_nStoneWidth * m_nStoneHeight);

        // create basic npcs
        Populate(m_vCharacters);
        // populate and create world

        
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

        //clear game screen window
        Fill(m_nBorder, m_nBorder, m_nStoneWidth+10, m_nStoneHeight+10, L' ');
        // clear Player interface window

        // clear Event interface window


        //npc walks and do smth

        // Draw Game Screen Window
        for (int x = 0; x < m_nStoneWidth; x++)
            for( int y = 0 ; y < m_nStoneHeight ; y++)
                if(m_stone[y*m_nStoneWidth + x] == symbolNpc.GetSymbol())
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

