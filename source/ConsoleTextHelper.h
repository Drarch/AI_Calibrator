#pragma once

#include <windows.h>

#include "Consts/TextColor.h"


class ConsoleTextHelper
{
private:
    static HANDLE GetConsole();

public:
    static void SetTextColor(Consts::TextColor TextColor);
};
