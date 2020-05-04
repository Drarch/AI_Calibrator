#include "ConsoleTextHelper.h"

HANDLE ConsoleTextHelper::GetConsole()
{
    return GetStdHandle(STD_OUTPUT_HANDLE);
}


void ConsoleTextHelper::SetTextColor(Consts::TextColor TextColor)
{
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(GetConsole(), TextColor);
}