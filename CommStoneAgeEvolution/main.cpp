#include <iostream>
#include "..\olcConsoleGameEngine.h"
#include <vector>

using std::vector;

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

        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime)
    {
        //clear game screen window
        Fill(10, 10, m_nStoneWidth, m_nStoneHeight, L' ');
        // clear Player interface window

        // clear Event interface window

        // Draw Game Screen Window
        for (int x = 0; x < m_nStoneWidth; x++)
            for( int y = 0 ; y < m_nStoneHeight ; y++)
                Draw(x + m_nBorder, y + m_nBorder, PIXEL_SOLID, FG_GREEN);
        // Draw Control Player Interface Window
        for (int x = 0; x < 1; x++)
            for( int y = 0 ; y < 2 ; y++)
                DrawString(x + m_nBorder + m_nControl, y + m_nBorder , L"Welcome", FG_RED);
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

