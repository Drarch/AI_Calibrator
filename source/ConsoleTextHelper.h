#pragma once

#include <windows.h>

#include "Consts/TextColor.h"


class ConsoleTextHelper
{
private:
    // static HANDLE hConsole;
    // static HANDLE GetConsole();

public:
    static void SetTextColor(Consts::TextColor TextColor);
};
