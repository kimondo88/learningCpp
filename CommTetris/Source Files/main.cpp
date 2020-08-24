#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

#pragma comment(lib, "User32.lib")

using std::wstring;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;
wstring tetromino[7];

int nFieldWidth = 12;
int nFieldHeight = 18;
int nScreenWidth = 120;
int nScreenHeight = 40;

unsigned char *pField = nullptr;

int Rotate(int px, int py, int r)
{
    switch(r % 4)
    {
        case 0: return py * 4 + px; // 0 degress
        case 1: return 12 + py - (px * 4); // 90 degrees
        case 2: return 15 - (py * 4) - px; // 180 degrees
        case 3: return 3 - py + ( px * 4); // 270 degrees
    }
    return 0;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY )
{
    for (int px = 0; px < 4; px++ )
        for ( int py = 0; py < 4 ; py++)
        {
            //get index into piece
            int pi = Rotate(px, py, nRotation);

            // get index into field
            int fi = ( nPosY + py) * nFieldWidth + (nPosX + px);\
            if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
            {
                if(nPosY + py >= 0 && nPosY + py < nFieldHeight)
                {
                    if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0)
                        return false; // fails in first hit
                }
            } 
        }

    return true;

}

int main()
{
    //create assets
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    tetromino[1].append(L"..X.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".X..");
    tetromino[1].append(L"....");

    tetromino[2].append(L"....");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L"....");

    tetromino[3].append(L".X..");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L"..X.");
    tetromino[3].append(L"....");

    tetromino[4].append(L"....");
    tetromino[4].append(L".XX.");
    tetromino[4].append(L".X..");
    tetromino[4].append(L".X..");

    tetromino[5].append(L"....");
    tetromino[5].append(L".XX.");
    tetromino[5].append(L"..X.");
    tetromino[5].append(L"..X.");

    tetromino[6].append(L"..X.");
    tetromino[6].append(L".XX.");
    tetromino[6].append(L"..X.");
    tetromino[6].append(L"....");

    pField = new unsigned char[nFieldWidth*nFieldHeight]; // creating game Field
    for (int x = 0; x < nFieldWidth; x++)
        for ( int y = 0; y < nFieldHeight; y++)
            pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight -1 ) ? 9 : 0;

    wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
    for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 
    NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    //game logic stuff

    bool bGameOver = false;

    int nCurrentPiece = 0;
    int nCurrentRotation = 0;
    int nCurrentX = nFieldWidth / 2;
    int nCurrentY = 0;
    bool bKey[4];

    //game loop
    while(!bGameOver)
    {
        sleep_for(milliseconds(50));

        // input ##############################
        for (int k = 0; k < 4; k++)                     //R L    D Z
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
        // Game Logic #########################
        if(bKey[1])
        {
            if(DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX -1, nCurrentY))
            {
                nCurrentX = nCurrentX - 1;
            }
        }
        if(bKey[0])
        {
            if(DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX +1, nCurrentY))
            {
                nCurrentX = nCurrentX + 1;
            }
        }
        if(bKey[2])
        {
            if(DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY+1))
            {
                nCurrentY = nCurrentY + 1;
            }
        }
        if(bKey[3])
        {
            if(DoesPieceFit(nCurrentPiece, nCurrentRotation+1, nCurrentX, nCurrentY+1))
            {
                nCurrentRotation = nCurrentRotation+1;
            }
        }

        // render output ######################


        //draw Field
        for ( int x = 0; x < nFieldWidth; x++)
            for ( int y = 0; y < nFieldHeight; y++)
                screen[(y+2)*nScreenWidth + ( x +2 )] = L" ABCDEFG=#"[pField[y*nFieldWidth+x]];

        //draw current piece
        for (int px = 0; px < 4; px++)
            for (int py = 0; py < 4; py++)
                if ( tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
                    screen[(nCurrentY + py +2)*nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece +65;
        // display frame
        //screen[nScreenWidth * nScreenHeight -1] = '\0';
        WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 },
        &dwBytesWritten);
    }

    return 0;
}