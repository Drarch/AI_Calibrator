#include "ConsoleMarker.h"


void ConsoleMarker::DrawCharacter(COORD Position, TCHAR Character, Consts::TextColor Color)
{
    HANDLE hConsole = ConsoleTextHelper::GetConsole();
    DWORD count;
    WORD dColor = Color;
    WriteConsoleOutputAttribute(hConsole, &dColor, 1, Position, &count);
    WriteConsoleOutputCharacter(hConsole, &Character, 1, Position, &count);
}

void ConsoleMarker::DrawCharacter(short X, short Y, TCHAR Character, Consts::TextColor Color)
{
    COORD Position = { X, Y };
    DrawCharacter(Position, Character, Color);
}

void ConsoleMarker::DrawTextLine(COORD Start, short Length, LineDirection Direction, Consts::TextColor Color)
{
    HANDLE hConsole = ConsoleTextHelper::GetConsole();
    DWORD cCharsWritten;

    switch(Direction)
    {
        case LineDirection::Horizontal:
            FillConsoleOutputAttribute(hConsole, (WORD)Color, Length, Start, &cCharsWritten);
            FillConsoleOutputCharacter(hConsole, (TCHAR)'-', Length, Start, &cCharsWritten);
            break;
        case LineDirection::Vertical:
            for (int i = 0; i < Length; i++)
            {
                DrawCharacter(Start, '|', Color);
                
                Start.Y++;
            }
            break;
    };
}

void ConsoleMarker::DrawTextLine(short StartX, short StartY, short Length, LineDirection Direction, Consts::TextColor Color)
{
    COORD Start = { StartX, StartY };
    DrawTextLine(Start, Length, Direction, Color);
}


void ConsoleMarker::DrawTextElbowLine(COORD Start, COORD End, LineDirection Direction, Consts::TextColor Color)
{
    COORD Dim = { (SHORT)abs(Start.X - End.X) + 1, (SHORT)abs(Start.Y - End.Y) + 1 };
    
    // std::cout << "Debug: " << Dim.X << " " << Dim.Y;
    if (Start.X > End.X) Start.X = End.X;
    if (Start.Y > End.Y) Start.Y = End.Y;

    if (Dim.X > 1 && Dim.Y == 1)
    {

        DrawTextLine(Start, Dim.X, LineDirection::Horizontal, Color);
        return;
    }
    else if (Dim.X == 1 && Dim.Y > 1)
    {

        DrawTextLine(Start, Dim.Y, LineDirection::Vertical, Color);
        return;
    }
    else if (Dim.X == 1 && Dim.Y == 1)
    {
        DrawCharacter(Start, '+', Color);
        return;
    }

    switch(Direction)
    {
        case LineDirection::Horizontal:
            DrawTextLine(Start, Dim.X, LineDirection::Horizontal, Color);
            DrawTextLine({End.X, Start.Y}, Dim.Y, LineDirection::Vertical, Color);
            DrawCharacter({End.X, Start.Y}, '+', Color);
            break;
        case LineDirection::Vertical:
            DrawTextLine(Start, Dim.Y, LineDirection::Vertical, Color);
            DrawTextLine({Start.X, End.Y}, Dim.X, LineDirection::Horizontal, Color);
            DrawCharacter({Start.X, End.Y}, '+', Color);
            break;
    }
}

void ConsoleMarker::DrawTextElbowLine(short StartX, short StartY, short EndX, short EndY, LineDirection Direction, Consts::TextColor Color)
{
    COORD Start = { StartX, StartY };
    COORD End = { EndX , EndY };
    DrawTextElbowLine(Start, End, Direction, Color);
}


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