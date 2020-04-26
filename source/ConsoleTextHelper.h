#pragma once

#include <windows.h>

#include "Consts/TextColor.h"


class ConsoleTextHelper
{
private:
    static HANDLE _hConsole;
    // static HANDLE GetConsole();

public:
    static void SetTextColor(TextColor TextColor);
};
