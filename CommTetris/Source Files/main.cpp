#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <vector>

#pragma comment(lib, "User32.lib")

using std::wstring;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::vector;
using std::cout;

#include <stdio.h>

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
                    if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
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

    int nCurrentPiece = 1;
    int nCurrentRotation = 0;
    int nCurrentX = nFieldWidth / 2;
    int nCurrentY = 0;

    bool bKey[4];
    bool bRotateHold = false;

    int nSpeed = 20;
    int nSpeedCounter = 0;
    bool bForceDown = false;
    int nPieceCount = 10;
    int nScore = 0;
    vector<int> vLines;
    while(!bGameOver)     //game loop
    {
        sleep_for(milliseconds(50)); // game tick
        nSpeedCounter++;
        bForceDown = (nSpeedCounter == nSpeed);

        // input ##############################
        for (int k = 0; k < 4; k++)                     //R L    D Z
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
        // Game Logic #########################
        nCurrentX -= (bKey[1] && (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY))) ? 1 : 0;
        nCurrentX += (bKey[0] && (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY))) ? 1 : 0;
        nCurrentY += (bKey[2] && (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))) ? 1 : 0;
        if (bKey[3])
        {
            nCurrentRotation += (!bRotateHold && (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))) ? 1 : 0;
            bRotateHold = true;
        }
        else
            bRotateHold = false;
        
        if(bForceDown)
        {
            nSpeedCounter = 0;
            if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY+1))
                nCurrentY++; // it can so do it
            else
            {
                // lock the current piece in the field           
                for (int px = 0; px < 4; px++)
                    for (int py = 0; py < 4; py++)
                        if ( tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
                            pField[(nCurrentY + py )*nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;
                
                nPieceCount++;
                if (nPieceCount % 10 == 0)
                    if (nSpeed >= 10) nSpeed--;

                // check have we got lines
                for(int py = 0; py < 4 ; py++)
                    if (nCurrentY + py < nFieldHeight - 1)
                    {
                        bool bLine = true;
                        for (int px = 1; px < nFieldWidth ; px++)
                            bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;

                        if (bLine)
                        {
                            // remove line set to =
                            for (int px = 1; px < nFieldWidth; px++)
                                pField[(nCurrentY + py)* nFieldWidth + px] = 8;

                            vLines.push_back(nCurrentY + py);
                        }
                    }

                //score the player
                nScore += 25;
                if(!vLines.empty()) nScore += (1 << vLines.size()) * 100;

                // choose next piece
                nCurrentRotation = 0;
                nCurrentX = nFieldWidth / 2;
                nCurrentY = 0;
                nCurrentPiece = rand() % 7;

                //if piece does not fit
                bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
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
                if ( tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
                    screen[(nCurrentY + py +2)*nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece +65;

        //draw score
        swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"Score: %8d", nScore);


        if (!vLines.empty())
        {
            //Display Frame(to draw lines)
            WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 },
            &dwBytesWritten);
            sleep_for(milliseconds(400)); // delay

            for (auto &v : vLines)
                for (int px = 1; px < nFieldWidth - 1; px++)
                {
                    for (int py = v; py > 0 ; py--)
                        pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
                        pField[px] = 0;
                }

            vLines.clear();
        }

        // display frame
        //screen[nScreenWidth * nScreenHeight -1] = '\0';
        WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 },
        &dwBytesWritten);
    }

    CloseHandle(hConsole);

    cout << "\n\t\tGame Over!! Score:" << nScore << "\n\n";
    system("pause");
    return 0;
}