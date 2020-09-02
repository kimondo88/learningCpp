#include <iostream>
#include "..\olcConsoleGameEngine.h"
#include <stack>
using std::pair;
using std::stack;
using std::make_pair;

class olc_Maze : public olcConsoleGameEngine
{
public:
    olc_Maze()
    {
        m_sAppName = L"MAZE";
    }

private:
    int m_nMazeWidth;
    int m_nMazeHeight;
    int *m_maze;

    enum
    {
        CELL_PATH_N = 0x01,
        CELL_PATH_E = 0x02,
        CELL_PATH_S = 0x04,
        CELL_PATH_W = 0x08,
        CELL_VISITED = 0x10,
    };

    int m_nVisitedCells;

    stack<pair<int, int>> m_stack;
    int m_nPathWidth;

protected:
    virtual bool OnUserCreate()
    {
        // maze parameters
        m_nMazeWidth = 40;
        m_nMazeHeight = 25;

        m_maze = new int[m_nMazeWidth * m_nMazeHeight];

        memset(m_maze, 0x00, m_nMazeWidth * m_nMazeHeight);

        m_stack.push(make_pair(0, 0));
        m_maze[0] = CELL_VISITED;
        m_nVisitedCells = 1;

        m_nPathWidth = 3;

        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime)
    {
        // maze algorithm.
        if (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight)
        {
            //step 1: Create set of unvisited neighbours

            // north neighbour
            
        }

        // draw stuff

        // clear screen
        Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ');

        // draw maze
        for (int x = 0; x < m_nMazeWidth; x++)
        {
            for ( int y = 0; y < m_nMazeHeight; y++)
            {
                for ( int py = 0; py < m_nPathWidth; py++)
                    for ( int px = 0; px < m_nPathWidth; px++)
                    {
                        if (m_maze[y * m_nMazeWidth + x] & CELL_VISITED)
                            Draw(x* (m_nPathWidth + 1) +px, y* (m_nPathWidth + 1) +py, PIXEL_SOLID, FG_WHITE);
                        else
                            Draw(x* (m_nPathWidth + 1) +px, y* (m_nPathWidth + 1) +py, PIXEL_SOLID, FG_BLUE);
                    }
                for ( int p = 0; p < m_nPathWidth; p++)
                {
                    if (m_maze[y * m_nMazeWidth + x] & CELL_PATH_S)
                        Draw(x* (m_nPathWidth + 1) + p, y* (m_nPathWidth + 1) + m_nPathWidth);
                    if (m_maze[y * m_nMazeWidth + x] & CELL_PATH_E)
                        Draw(x* (m_nPathWidth + 1) + m_nPathWidth, y* (m_nPathWidth + 1) + p);
                }
            }
        }
        return true;
    }
};

int main()
{
    //using olcCode engine derived app.
    olc_Maze game;
    game.ConstructConsole(160, 100, 8, 8);
    game.Start();
    

    return 0;

}