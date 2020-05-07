#pragma once

#include "ConsoleTextHelper.h"
#include "Consts/TextColor.h"

enum LineDirection
{
    Horizontal = 0,
    Verical
};

class ConsoleMarker
{
private:

public:
    static void DrawCharacter(short X, short Y, TCHAR Character, Consts::TextColor Color = Consts::TextColor::GREY);
    static void DrawCharacter(COORD Position, TCHAR Character, Consts::TextColor Color = Consts::TextColor::GREY);

    static void DrawTextLine(COORD Start, short Length, LineDirection Direction, Consts::TextColor Color = Consts::TextColor::GREY);
    static void DrawTextLine(short StartX, short StartY, short Length, LineDirection Direction, Consts::TextColor Color = Consts::TextColor::GREY);

    static void DrawRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);
    static void DrawRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);

    static void FillRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);
    static void FillRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);

    static void DrawTextRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);
    static void DrawTextRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);

    static void FillTextRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY, TCHAR Character = (TCHAR)'-');
    static void FillTextRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY, TCHAR Character = (TCHAR)'-');
};

