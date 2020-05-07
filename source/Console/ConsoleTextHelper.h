#pragma once

#include <windows.h>
#include <iostream>

#include "Consts/TextColor.h"


/* Standard error macro for reporting API errors */ 
//  #define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s \ on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

class ConsoleTextHelper
{
private:

public:
    static HANDLE GetConsole();
    static HANDLE GetConsoleInput();

    static void ClearScreen();
    static void ClearPartScreen();
    static void ClearBackspace();

    static COORD GetCursorPosition();

    static void SetCursorPosition(COORD Position);
    static void SetCursorPosition(short X, short Y);

    static void SetTextColor(Consts::TextColor TextColor);


    static bool GetAnyKey();
    static bool GetEnterKey();
};
