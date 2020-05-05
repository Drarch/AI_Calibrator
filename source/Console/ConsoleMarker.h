#pragma once

#include "ConsoleTextHelper.h"
#include "Consts/TextColor.h"


class ConsoleMarker
{
private:

public:
    static void DrawRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);
    static void DrawRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);

    static void FillRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);
    static void FillRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);

    static void DrawTextRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);
    static void DrawTextRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);

    static void FillTextRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY, TCHAR Character = (TCHAR)'-');
    static void FillTextRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY, TCHAR Character = (TCHAR)'-');
};