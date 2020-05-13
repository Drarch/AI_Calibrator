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


void ConsoleMarker::DrawTextSLine(COORD Start, COORD End, LineDirection Direction, Consts::TextColor Color)
{
    COORD Dim = { (SHORT)abs(Start.X - End.X) + 1, (SHORT)abs(Start.Y - End.Y) + 1 };
    COORD Min = { min(Start.X, End.X), min(Start.Y, End.Y) };

    /* Dim < 3 same as DrawElbowLine() */
    if (Dim.X < 3 || Dim.Y < 3)
    {
        DrawTextElbowLine(Start, End, Direction, Color);
    }
    else
    {
        SHORT Middle = 1;

        switch(Direction)
        {
            case LineDirection::Horizontal:
                Middle = Min.X + (Dim.X / 2);
                DrawTextElbowLine(Start, {Middle, End.Y}, Direction, Color);
                DrawTextLine({min(Middle, End.X), End.Y}, abs(Middle - End.X) + 1, Direction, Color);
                DrawCharacter({Middle, End.Y}, '+', Color);
                break;
            case LineDirection::Vertical:
                Middle = Min.Y + (Dim.Y / 2);
                DrawTextElbowLine(Start, {End.X, Middle}, Direction, Color);
                DrawTextLine({End.X, min(Middle, End.Y)}, abs(Middle - End.Y) + 1, Direction, Color);
                DrawCharacter({End.X, Middle}, '+', Color);
                break;
        }
    }
}

void ConsoleMarker::DrawTextSLine(short StartX, short StartY, short EndX, short EndY, LineDirection Direction, Consts::TextColor Color)
{
    COORD Start = {StartX, StartY};
    COORD End = {EndX, EndY};
    DrawTextSLine(Start, End, Direction, Color);

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
    /* Control - Length */
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
    
    /* Straight Line */
    ConsoleMarker::DrawTextElbowLine(8, 3, 8, 11, LineDirection::Horizontal, Consts::TextColor::GREEN);
    ConsoleMarker::DrawTextElbowLine(9, 11, 9, 3, LineDirection::Horizontal, Consts::TextColor::LIGHT_GREEN);

    ConsoleMarker::DrawTextElbowLine(10, 1, 25, 1, LineDirection::Vertical, Consts::TextColor::RED);
    ConsoleMarker::DrawTextElbowLine(25, 2, 10, 2, LineDirection::Vertical, Consts::TextColor::LIGHT_RED);

    /* Point */
    ConsoleMarker::DrawTextElbowLine(8, 1, 8, 1, LineDirection::Horizontal, Consts::TextColor::BLUE);
    ConsoleMarker::DrawTextElbowLine(9, 2, 9, 2, LineDirection::Vertical, Consts::TextColor::LIGHT_BLUE);
}

void ConsoleMarker::DebugTextSLine()
{
    /* Control - Length */
    ConsoleMarker::DrawTextLine(0, 0, 5, LineDirection::Horizontal);
    ConsoleMarker::DrawTextLine(0, 0, 5, LineDirection::Vertical);


    /* Straight */
    ConsoleMarker::DrawTextSLine(5, 1, 15, 1, LineDirection::Horizontal, Consts::TextColor::GREEN);
    ConsoleMarker::DrawTextSLine(15, 2, 5, 2, LineDirection::Horizontal, Consts::TextColor::LIGHT_GREEN);
    
    ConsoleMarker::DrawTextSLine(5, 6, 5, 15, LineDirection::Vertical, Consts::TextColor::RED);
    ConsoleMarker::DrawTextSLine(6, 15, 6, 6, LineDirection::Vertical, Consts::TextColor::LIGHT_RED);


    /* Dimension 2 */
    ConsoleMarker::DrawTextSLine(7, 3, 15, 4, LineDirection::Horizontal, Consts::TextColor::GREEN);
    ConsoleMarker::DrawTextSLine(13, 4, 5, 3, LineDirection::Horizontal, Consts::TextColor::LIGHT_GREEN);

    ConsoleMarker::DrawTextSLine(7, 8, 8, 15, LineDirection::Vertical, Consts::TextColor::RED);
    ConsoleMarker::DrawTextSLine(8, 13, 7, 6, LineDirection::Vertical, Consts::TextColor::LIGHT_RED);


    /* Horizontal */
    ConsoleMarker::DrawTextLine(19, 0, 20, LineDirection::Vertical); // Control line
    ConsoleMarker::DrawTextLine(31, 0, 20, LineDirection::Vertical); // Control line
    ConsoleMarker::DrawTextLine(40, 0, 20, LineDirection::Vertical); // Control line

    /* Horizontal - Odd */
    ConsoleMarker::DrawTextSLine(20, 1, 30, 3, LineDirection::Horizontal, Consts::TextColor::YELLOW);
    ConsoleMarker::DrawTextSLine(30, 6, 20, 4, LineDirection::Horizontal, Consts::TextColor::LIGHT_YELLOW);

    ConsoleMarker::DrawTextSLine(20, 10, 30, 7, LineDirection::Horizontal, Consts::TextColor::YELLOW);
    ConsoleMarker::DrawTextSLine(30, 11, 20, 14, LineDirection::Horizontal, Consts::TextColor::LIGHT_YELLOW);

    /* Horizontal - Even */
    ConsoleMarker::DrawTextSLine(32, 1, 39, 3, LineDirection::Horizontal, Consts::TextColor::YELLOW);
    ConsoleMarker::DrawTextSLine(39, 6, 32, 4, LineDirection::Horizontal, Consts::TextColor::LIGHT_YELLOW);

    ConsoleMarker::DrawTextSLine(32, 10, 39, 7, LineDirection::Horizontal, Consts::TextColor::YELLOW);
    ConsoleMarker::DrawTextSLine(39, 11, 32, 14, LineDirection::Horizontal, Consts::TextColor::LIGHT_YELLOW);

    /* Horizontal - Long */
    ConsoleMarker::DrawTextSLine(41, 1, 43, 15, LineDirection::Horizontal, Consts::TextColor::YELLOW);
    ConsoleMarker::DrawTextSLine(44, 15, 46, 1, LineDirection::Horizontal, Consts::TextColor::YELLOW);

    ConsoleMarker::DrawTextSLine(49, 1, 47, 15, LineDirection::Horizontal, Consts::TextColor::LIGHT_YELLOW);
    ConsoleMarker::DrawTextSLine(52, 15, 50, 1, LineDirection::Horizontal, Consts::TextColor::LIGHT_YELLOW);


    /* Verticle */
    ConsoleMarker::DrawTextLine(53, 0, 20, LineDirection::Vertical); // Control line
    ConsoleMarker::DrawTextLine(68, 0, 20, LineDirection::Vertical); // Control line
    ConsoleMarker::DrawTextLine(54, 0, 14, LineDirection::Horizontal); // Control line
    ConsoleMarker::DrawTextLine(54, 8, 14, LineDirection::Horizontal); // Control line
    ConsoleMarker::DrawTextLine(54, 15, 14, LineDirection::Horizontal); // Control line

    /* Vertical - Odd */
    ConsoleMarker::DrawTextSLine(54, 1, 56, 7, LineDirection::Vertical, Consts::TextColor::PURPLE);
    ConsoleMarker::DrawTextSLine(59, 7, 57, 1, LineDirection::Vertical, Consts::TextColor::LIGHT_PURPLE);

    ConsoleMarker::DrawTextSLine(54, 9, 56, 14, LineDirection::Vertical, Consts::TextColor::PURPLE);
    ConsoleMarker::DrawTextSLine(59, 14, 57, 9, LineDirection::Vertical, Consts::TextColor::LIGHT_PURPLE);

    /* Vertical - Even */
    ConsoleMarker::DrawTextSLine(60, 7, 63, 1, LineDirection::Vertical, Consts::TextColor::PURPLE);
    ConsoleMarker::DrawTextSLine(67, 1, 64, 7, LineDirection::Vertical, Consts::TextColor::LIGHT_PURPLE);

    ConsoleMarker::DrawTextSLine(60, 14, 63, 9, LineDirection::Vertical, Consts::TextColor::PURPLE);
    ConsoleMarker::DrawTextSLine(67, 9, 64, 14, LineDirection::Vertical, Consts::TextColor::LIGHT_PURPLE);

    /* Vertical - Long */
    ConsoleMarker::DrawTextSLine(69, 1, 81, 3, LineDirection::Vertical, Consts::TextColor::PURPLE);
    ConsoleMarker::DrawTextSLine(69, 6, 81, 4, LineDirection::Vertical, Consts::TextColor::PURPLE);

    ConsoleMarker::DrawTextSLine(81, 7, 69, 9, LineDirection::Vertical, Consts::TextColor::LIGHT_PURPLE);
    ConsoleMarker::DrawTextSLine(81, 12, 69, 10, LineDirection::Vertical, Consts::TextColor::LIGHT_PURPLE);

}