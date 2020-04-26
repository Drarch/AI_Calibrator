#include "ConsoleTextHelper.h"

// HANDLE ConsoleTextHelper::GetConsole()
// {
//     if (hConsole == NULL)
//         hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//     return hConsole;
// }


void ConsoleTextHelper::SetTextColor(TextColor TextColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, TextColor);
}