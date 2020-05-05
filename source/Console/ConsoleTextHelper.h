#pragma once

#include <windows.h>

#include "Consts/TextColor.h"


/* Standard error macro for reporting API errors */ 
//  #define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s \ on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

class ConsoleTextHelper
{
private:

public:
    static HANDLE GetConsole();
    static void SetTextColor(Consts::TextColor TextColor);
    static void ClearScreen();
};
