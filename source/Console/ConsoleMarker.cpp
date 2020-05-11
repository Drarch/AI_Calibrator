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
    COORD Min = { min(Start.X, End.X), min(Start.Y, End.Y) };

    if (Dim.X > 1 && Dim.Y == 1)
    {
        DrawTextLine({Min.X, Start.Y}, Dim.X, LineDirection::Horizontal, Color);
    }
    else if (Dim.X == 1 && Dim.Y > 1)
    {
        DrawTextLine({Start.X, Min.Y}, Dim.Y, LineDirection::Vertical, Color);
    }
    else if (Dim.X == 1 && Dim.Y == 1)
    {
        DrawCharacter(Start, '+', Color);
    }
    else
    {
        switch(Direction)
        {
            case LineDirection::Horizontal:
                DrawTextLine({Min.X, Start.Y}, Dim.X, LineDirection::Horizontal, Color);
                DrawTextLine({End.X, Min.Y}, Dim.Y, LineDirection::Vertical, Color);
                DrawCharacter({End.X, Start.Y}, '+', Color);
                break;
            case LineDirection::Vertical:
                DrawTextLine({Start.X, Min.Y}, Dim.Y, LineDirection::Vertical, Color);
                DrawTextLine({Min.X, End.Y}, Dim.X, LineDirection::Horizontal, Color);
                DrawCharacter({Start.X, End.Y}, '+', Color);
                break;
        }
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



void ConsoleMarker::DebugTextElbowLine()
{
    /* Control - Lebgth */
    ConsoleMarker::DrawTextLine(0, 0, 5, LineDirection::Horizontal);
    ConsoleMarker::DrawTextLine(0, 0, 5, LineDirection::Vertical);

    /* Side by side - Horizontal */
    ConsoleMarker::DrawTextElbowLine(10, 3, 13, 6, LineDirection::Horizontal, Consts::TextColor::YELLOW); // LG PD ┐
    ConsoleMarker::DrawTextElbowLine(14, 6, 17, 3, LineDirection::Horizontal, Consts::TextColor::RED);    // LD PG ┘ 
    ConsoleMarker::DrawTextElbowLine(21, 6, 18, 3, LineDirection::Horizontal, Consts::TextColor::GREEN);  // PD LG └
    ConsoleMarker::DrawTextElbowLine(25, 3, 22, 6, LineDirection::Horizontal, Consts::TextColor::BLUE);   // PG LD ┌

    /* Side by side - Vertical */
    ConsoleMarker::DrawTextElbowLine(13, 11, 10, 8, LineDirection::Vertical, Consts::TextColor::YELLOW);  // PD LG ┐
    ConsoleMarker::DrawTextElbowLine(17, 8, 14, 11, LineDirection::Vertical, Consts::TextColor::RED);     // PG LD ┘
    ConsoleMarker::DrawTextElbowLine(18, 8, 21, 11, LineDirection::Vertical, Consts::TextColor::GREEN);   // LG PD └
    ConsoleMarker::DrawTextElbowLine(22, 11, 25, 8, LineDirection::Vertical, Consts::TextColor::BLUE);    // LD PG ┌
    
    /* Straigh Line */
    ConsoleMarker::DrawTextElbowLine(10, 1, 35, 1, LineDirection::Vertical, Consts::TextColor::RED);
    ConsoleMarker::DrawTextElbowLine(35, 2, 10, 2, LineDirection::Vertical, Consts::TextColor::LIGHT_RED);

    ConsoleMarker::DrawTextElbowLine(8, 3, 8, 15, LineDirection::Horizontal, Consts::TextColor::GREEN);
    ConsoleMarker::DrawTextElbowLine(9, 15, 9, 3, LineDirection::Horizontal, Consts::TextColor::LIGHT_GREEN);

    /* Point */
    ConsoleMarker::DrawTextElbowLine(8, 1, 8, 1, LineDirection::Horizontal, Consts::TextColor::BLUE);
    ConsoleMarker::DrawTextElbowLine(9, 2, 9, 2, LineDirection::Vertical, Consts::TextColor::LIGHT_BLUE);
}