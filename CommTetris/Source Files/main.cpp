#include <iostream>

using std::wstring;

wstring tetromino[7];

int main()
{
    //create assets
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    tetromino[1].append(L"..L.");
    tetromino[1].append(L".LL.");
    tetromino[1].append(L".L..");
    tetromino[1].append(L"....");

    return 0;
}