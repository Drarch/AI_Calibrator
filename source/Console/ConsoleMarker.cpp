#include "ConsoleMarker.h"

void ConsoleMarker::FillRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color)
{
    HANDLE hConsole = ConsoleTextHelper::GetConsole();
    DWORD cCharsWritten;

    // SetConsoleTextAttribute(hConsole, Color);
    for (short i = 0; i < Height; ++i)
    {
        COORD LineBegin = {LeftTop.X, LeftTop.Y+i};
        FillConsoleOutputAttribute(hConsole, (WORD)Color, Height, LineBegin, &cCharsWritten);
        FillConsoleOutputCharacter(hConsole, (TCHAR)'-', Height, LineBegin, &cCharsWritten);
    }

    // SetConsoleTextAttribute(hConsole, Consts::TextColor::WHITE);
}


void ConsoleMarker::FillRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color)
{
    COORD LeftTop = { LeftTopX, LeftTopY };

    ConsoleMarker::FillRectangle(LeftTop, Width, Height, Color);
}