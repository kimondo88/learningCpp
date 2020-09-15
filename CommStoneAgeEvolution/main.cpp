#include <iostream>
#include "..\olcConsoleGameEngine.h"
#include <vector>
#include <random>
#include <chrono>

using std::vector;
using std::mt19937;

class olcStoneAgeEvo : public olcConsoleGameEngine
{
public:
    olcStoneAgeEvo()
    {
        m_sAppName = L"StoneAgeEvolution";
    }

private:
    int m_nStoneWidth;
    int m_nStoneHeight;
    int *m_stone;

    int m_nBorder;
    int m_nControl; 
    int m_nEvent;

    enum
    {
        CELL_TEST = 0x010,
        CELL_HUMAN_NPC = 0x38F,
    };

    virtual bool Populate()
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        mt19937 random(seed);
        m_stone[random() % 100] = CELL_TEST;

        return true;
    };

protected:
    virtual bool OnUserCreate()
    {
        // game screen parameters
        m_nStoneWidth = 30;
        m_nStoneHeight = 30;
        m_stone = new int[m_nStoneWidth * m_nStoneHeight];

        m_nBorder = 10;
        m_nControl = 50;
        m_nEvent = 50;

        memset(m_stone, 0x00, m_nStoneWidth * m_nStoneHeight);

        // create basic npcs
        Populate();
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
        //clear game screen window
        Fill(10, 10, m_nStoneWidth, m_nStoneHeight, L' ');
        // clear Player interface window

        // clear Event interface window


        //npc walks and do smth

        // Draw Game Screen Window
        for (int x = 0; x < m_nStoneWidth; x++)
            for( int y = 0 ; y < m_nStoneHeight ; y++)
                Draw(x + m_nBorder, y + m_nBorder, m_stone[y*m_nStoneWidth + x], FG_GREEN);
        // Draw Control Player Interface Window
        for (int x = 0; x < 1; x++)
            for( int y = 0 ; y < 2 ; y++)
            {
                DrawString(x + m_nBorder + m_nControl, y + m_nBorder , L"Welcome", FG_RED);
                //if  (y == 3)
                //    DrawString(x + m_nBorder + m_nControl, y + m_nBorder , , FG_RED);
            }
        // Draw Event Interface Window
        for (int x = 0; x < 1; x++)
            for( int y = 0 ; y < 2 ; y++)
                DrawString(x + m_nBorder + m_nControl/2, y + m_nBorder + m_nEvent , L"Event", FG_BLUE);
        return true;
    }
};

int main()
{

olcStoneAgeEvo game;
game.ConstructConsole(100, 100, 8, 8);
game.Start();

return 0;

}
