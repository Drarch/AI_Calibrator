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

void ConsoleTextHelper::ClearScreen()
{
    COORD coordScreen = { 0, 0 };    /* here's where we'll home the
                                        cursor */ 
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */ 
    DWORD dwConSize;                 /* number of character cells in
                                        the current buffer */ 
    HANDLE hConsole = GetConsole();


    /* get the number of character cells in the current buffer */ 

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    // PERR( bSuccess, "GetConsoleScreenBufferInfo" );
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    /* fill the entire screen with blanks */ 

    bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten );
    // PERR( bSuccess, "FillConsoleOutputCharacter" );

    /* get the current text attribute */ 

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    // PERR( bSuccess, "ConsoleScreenBufferInfo" );

    /* now set the buffer's attributes accordingly */ 

    bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten );
    // PERR( bSuccess, "FillConsoleOutputAttribute" );

    /* put the cursor at (0, 0) */ 

    bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
    // PERR( bSuccess, "SetConsoleCursorPosition" );
    return;
}