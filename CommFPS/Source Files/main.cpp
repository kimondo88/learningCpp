#include <iostream>
#include <Windows.h>
#include <chrono>
#include <vector>
#include <algorithm>

#pragma comment(lib, "User32.lib")

//using std::cout;
using std::wstring;
using std::chrono::system_clock;
using std::vector;
using std::pair;
using std::make_pair;
using std::sort;

int nScreenWidth = 120;
int nScreenHeight = 40;

float fPlayerX = 8.0f;
float fPlayerY = 8.0f;
float fPlayerA = 0.0f;

int nMapHeight = 16;
int nMapWidth = 16;

int weaponWidth = 10;
int weaponHeight = 5;

float fFOV = 3.14159f / 4.0f;
float fDepth = 16.0f;

int main()
{
    //Create Screen Buffer
    wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 
    NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    wstring map;
    map += L"################";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#.........#....#";
    map += L"#.........#....#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#......#########";
    map += L"#..............#";
    map += L"#..............#";
    map += L"################";

    wstring weapon;
    weapon += L"...WKKW...";
    weapon += L"..N0xclOW.";
    weapon += L".WOc:;';OW";
    weapon += L"WXOkd:;:dK";
    weapon += L"WKOO00Okx0";






    auto tp1 = system_clock::now();
    auto tp2 = system_clock::now();


    //gameloop
    while(true)
    {
        tp2 = system_clock::now();
        std::chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();

        //Controls
        //Handle CCW Rotation.
        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
            fPlayerA -= (0.8f) * fElapsedTime; 
        if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
            fPlayerA += (0.8f) * fElapsedTime;
        if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
        {
            fPlayerX += sinf(fPlayerA) * 5.0f * fElapsedTime;
            fPlayerY += cosf(fPlayerA) * 5.0f * fElapsedTime;
            if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#')
            {
                fPlayerX -= sinf(fPlayerA) * 5.0f * fElapsedTime;
                fPlayerY -= cosf(fPlayerA) * 5.0f * fElapsedTime;
            }
        }
        if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
        {
            fPlayerX -= sinf(fPlayerA) * 5.0f * fElapsedTime;
            fPlayerY -= cosf(fPlayerA) * 5.0f * fElapsedTime;
            if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#')
            {
                fPlayerX += sinf(fPlayerA) * 5.0f * fElapsedTime;
                fPlayerY += cosf(fPlayerA) * 5.0f * fElapsedTime;
            }
        }

        for(int x = 0; x < nScreenWidth; ++x)
        {
            // for each column calculate the projected ray angle into world space
            float fRayAngle = ( fPlayerA - fFOV / 2.0f) + 
            ((float)x / (float)nScreenWidth) * fFOV;

            float fDistanceToWall = 0.0f;
            bool bHitWall = false;
            bool bBoundary = false;

            float fEyeX = sinf(fRayAngle); // unit vector for ray in player space
            float fEyeY = cosf(fRayAngle);

            while(!bHitWall && fDistanceToWall < fDepth )
            {
                fDistanceToWall += 0.1f;

                int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
                int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

                // test if ray is out of bounds

                if(nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
                {
                    bHitWall = true; // set distance to maximum depth
                    fDistanceToWall = fDepth;
                }
                else
                {
                    // ray is inbound so test to see if the ray cell is a wall block
                    if(map[nTestY * nMapWidth + nTestX] == '#')
                    {
                        bHitWall = true;

                        vector<pair<float, float>> p; // distance to perfect corner, dot.

                        for (int tx = 0; tx < 2; tx++)
                            for (int ty = 0; ty < 2; ty++)
                            {
                                float vy = (float)nTestY + ty - fPlayerY;
                                float vx = (float)nTestX + tx - fPlayerX;
                                float d = sqrt(vx*vx + vy*vy);
                                float dot = (fEyeX * vx / d) + (fEyeY * vy /d);
                                p.push_back(make_pair(d, dot));
                            }
                        
                        //sort pairs from closest to farthest
                        sort(p.begin(), p.end(), [](const pair<float, float> &left, const pair<float, float> &right) {return left.first < right.first;});

                        float fBound = 0.01;
                        if (acos(p.at(0).second) < fBound) bBoundary = true;
                        if (acos(p.at(1).second) < fBound) bBoundary = true;

                    }
                }
                
            }

            // calculate distance to ceiling and floor
            int nCeiling = (float)(nScreenHeight / 2.0 ) - nScreenHeight / ((float)fDistanceToWall);
            int nFloor = nScreenHeight - nCeiling;

            short nShade = ' ';
            if (fDistanceToWall <= fDepth / 4.0f)        nShade = 0x2588; // very close
            else if (fDistanceToWall < fDepth / 3.0f)    nShade = 0x2593;
            else if (fDistanceToWall < fDepth / 2.0f)    nShade = 0x2592;
            else if (fDistanceToWall < fDepth )          nShade = 0x2591;
            else                                         nShade = ' '; // too far away.

            if(bBoundary)   nShade = ' ';
            
            for(int y = 0; y < nScreenHeight; y++)
            {
                if (y <= nCeiling)
                    screen[y*nScreenWidth+x] = ' ';
                else if (y > nCeiling && y <= nFloor)
                {
                    screen[y*nScreenWidth+x] = nShade;
                }
                else
                {
                    float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
                    if (b < 0.25)        nShade = '#';
                    else if (b < 0.5)    nShade = 'x';
                    else if (b < 0.75)   nShade = '.';
                    else if (b < 0.9)    nShade = '-';
                    else                 nShade = ' ';
                    screen[y*nScreenWidth+x] = nShade;
                }
                
            }
        

        }

    //display stats
    swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", fPlayerX, fPlayerY, fPlayerA, 1.0f/ fElapsedTime );

    //display map
    for (int nx = 0; nx < nMapWidth; nx++)
        for (int ny = 0; ny < nMapWidth; ny++)
        {
            screen[(ny + 1)*nScreenWidth + nx] = map[ny*nMapWidth + (nMapWidth- nx - 1)];
        }

    screen[((int)fPlayerY + 1)*nScreenWidth + (int)nMapWidth - (int)fPlayerX] = 'P';

    // display weapon
    for (int ny = 0; ny < 5; ny++)
        for (int nx = 0; nx < 10 ; nx++)
        {
            if(weapon[ny*weaponWidth+nx] != '.')
               screen[(ny+35)*nScreenWidth + nx+60] = weapon[ny*weaponWidth+nx];
        }


    screen[nScreenWidth * nScreenHeight -1] = '\0';
    WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 },
    &dwBytesWritten);
    }

    return 0;

}

//0*7+0
//0*7+1
//2*7+0