#include <iostream>
#include "..\olcConsoleGameEngine.h"
#include <stack>
#include <vector>

using std::vector;
using std::pair;
using std::stack;
using std::make_pair;
using std::rand;

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
        auto offset = [&](int x, int y)
        {
            return (m_stack.top().second + y)* m_nMazeWidth + (m_stack.top().first +x) ;
        };

        // maze algorithm.
        if (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight)
        {
            //step 1: Create set of unvisited neighbours
            vector<int> neighbours;
            // North neighbour
            if(m_stack.top().second > 0 && (m_maze[offset(0, -1)] & CELL_VISITED == 0))
                    neighbours.push_back(0);
            // east neighbour
            if(m_stack.top().first < m_nMazeWidth - 1 && (m_maze[offset(1,0)] & CELL_VISITED == 0))
                    neighbours.push_back(1);
            // south neighbour
            if(m_stack.top().first > 0 && (m_maze[offset(0,1)] & CELL_VISITED == 0))
                    neighbours.push_back(2);
            // west neighbour
            if(m_stack.top().second > m_nMazeWidth - 1 && (m_maze[offset(-1,0)] & CELL_VISITED == 0))
                    neighbours.push_back(3);

            if (!neighbours.empty())
            {
                // choose avaialbe neighbour at random
                int next_cell_dir = neighbours[rand() % neighbours.size()];

                // create a path between nieghbour and current cell
                switch (next_cell_dir)
                {
                case 0: // North
                    m_maze[offset(0,0)] |= CELL_PATH_N;
                    m_maze[offset(0, -1)] |= CELL_PATH_S;
                    m_stack.push(make_pair((m_stack.top().first + 0), (m_stack.top().second - 1)));

                    break;
                case 1: // East
                    break;
                case 2: // South
                    break;
                case 3: // West
                    break;
                }

            }

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