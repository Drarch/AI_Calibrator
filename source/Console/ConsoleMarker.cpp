#include "ConsoleMarker.h"

void ConsoleMarker::DrawRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color)
{
    FillRectangle(LeftTop, Width, Height, Color);
    FillRectangle({LeftTop.X+1, LeftTop.Y+1}, Width-2, Height-2, Consts::TextColor::BLACK);
}

void ConsoleMarker::DrawRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color)
{
    COORD LeftTop = { LeftTopX, LeftTopY };

    DrawRectangle(LeftTop, Width, Height, Color);
}


void ConsoleMarker::FillRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color)
{
    HANDLE hConsole = ConsoleTextHelper::GetConsole();
    DWORD cCharsWritten;

    for (short i = 0; i < Height; ++i)
    {
        COORD LineBegin = {LeftTop.X, LeftTop.Y+i};
        FillConsoleOutputAttribute(hConsole, (WORD)Color*16, Width, LineBegin, &cCharsWritten);
        FillConsoleOutputCharacter(hConsole, (TCHAR)' ', Width, LineBegin, &cCharsWritten);
    }
}

void ConsoleMarker::FillRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color)
{
    COORD LeftTop = { LeftTopX, LeftTopY };

    FillRectangle(LeftTop, Width, Height, Color);
}


void ConsoleMarker::DrawTextRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color)
{
    HANDLE hConsole = ConsoleTextHelper::GetConsole();
    DWORD cCharsWritten;

    for (short i = 0; i < Height; ++i)
    {
        COORD LineBegin = {LeftTop.X, LeftTop.Y+i};

        if(i == 0 || i == Height-1)
        {
            FillConsoleOutputAttribute(hConsole, (WORD)Color, Width, LineBegin, &cCharsWritten);
            FillConsoleOutputCharacter(hConsole, (TCHAR)'-', Width, LineBegin, &cCharsWritten);
        }
        else
        {
            FillConsoleOutputAttribute(hConsole, (WORD)Color, 1, LineBegin, &cCharsWritten);
            FillConsoleOutputCharacter(hConsole, (TCHAR)'|', 1, LineBegin, &cCharsWritten);

            LineBegin.X += Width-1;

            FillConsoleOutputAttribute(hConsole, (WORD)Color, 1, LineBegin, &cCharsWritten);
            FillConsoleOutputCharacter(hConsole, (TCHAR)'|', 1, LineBegin, &cCharsWritten);
        }

        COORD Corner = {LeftTop.X, LeftTop.Y};
        FillConsoleOutputCharacter(hConsole, (TCHAR)'+', 1, Corner, &cCharsWritten);
        Corner = {LeftTop.X, LeftTop.Y+Height-1};
        FillConsoleOutputCharacter(hConsole, (TCHAR)'+', 1, Corner, &cCharsWritten);
        Corner = {LeftTop.X+Width-1, LeftTop.Y};
        FillConsoleOutputCharacter(hConsole, (TCHAR)'+', 1, Corner, &cCharsWritten);
        Corner = {LeftTop.X+Width-1, LeftTop.Y+Height-1};
        FillConsoleOutputCharacter(hConsole, (TCHAR)'+', 1, Corner, &cCharsWritten);
    }
}

void ConsoleMarker::DrawTextRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color)
{
    COORD LeftTop = { LeftTopX, LeftTopY };

    DrawTextRectangle(LeftTop, Width, Height, Color);
}



void ConsoleMarker::FillTextRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color, TCHAR Character)
{
    HANDLE hConsole = ConsoleTextHelper::GetConsole();
    DWORD cCharsWritten;

    for (short i = 0; i < Height; ++i)
    {
        COORD LineBegin = {LeftTop.X, LeftTop.Y+i};
        FillConsoleOutputAttribute(hConsole, (WORD)Color, Width, LineBegin, &cCharsWritten);
        FillConsoleOutputCharacter(hConsole, Character, Width, LineBegin, &cCharsWritten);
    }
}

void ConsoleMarker::FillTextRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color, TCHAR Character)
{
    COORD LeftTop = { LeftTopX, LeftTopY };

    FillTextRectangle(LeftTop, Width, Height, Color, Character);
}