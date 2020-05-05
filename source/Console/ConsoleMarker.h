#pragma once

#include "ConsoleTextHelper.h"
#include "Consts/TextColor.h"


class ConsoleMarker
{
private:

public:
    static void FillRectangle(short LeftTopX, short LeftTopY, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);
    static void FillRectangle(COORD LeftTop, short Width, short Height, Consts::TextColor Color = Consts::TextColor::GREY);
};