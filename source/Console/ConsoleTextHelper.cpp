#include "ConsoleTextHelper.h"

HANDLE ConsoleTextHelper::GetConsole()
{
    return GetStdHandle(STD_OUTPUT_HANDLE);
}

HANDLE ConsoleTextHelper::GetConsoleInput()
{
    return GetStdHandle(STD_INPUT_HANDLE);
}

COORD ConsoleTextHelper::GetConsoleSize()
{
    CONSOLE_SCREEN_BUFFER_INFO ConsoleBufferInfo;
    if(GetConsoleScreenBufferInfo(GetConsole(), &ConsoleBufferInfo))
    {
        return ConsoleBufferInfo.dwSize;
    }
    else
    {
        return { 0, 0 };
    }
}

COORD ConsoleTextHelper::GetCursorPosition()
{
    CONSOLE_SCREEN_BUFFER_INFO ConsoleBufferInfo;
    if(GetConsoleScreenBufferInfo(GetConsole(), &ConsoleBufferInfo))
    {
        return ConsoleBufferInfo.dwCursorPosition;
    }
    else
    {
        return { 0, 0 };
    }
}

void ConsoleTextHelper::SetCursorPosition(COORD Position)
{
    HANDLE hConsole = GetConsole();
    SetConsoleCursorPosition(hConsole, Position);
}

void ConsoleTextHelper::SetCursorPosition(short X, short Y)
{
    COORD position = {X, Y};
    SetCursorPosition(position);
}


bool ConsoleTextHelper::SetConsoleModeInput(HANDLE hConsoleIn, DWORD *mode)
{
    if (hConsoleIn == INVALID_HANDLE_VALUE
    || !GetConsoleMode( hConsoleIn, &*mode )
    || !SetConsoleMode( hConsoleIn, 0 ))
    {
        std::cout << "ConsoleTextHelper::SetConsoleModeInput() - Mode Error: " << GetLastError();
        system("pause");
        return false;
    }

    if(!FlushConsoleInputBuffer( hConsoleIn ))
    {
        std::cout << "ConsoleTextHelper::SetConsoleModeInput() - Flush Error: " << GetLastError();
        system("pause");
        return false;
    }

    return true;
}


void ConsoleTextHelper::ClearScreen()
{
    COORD coordScreen = { 0, 0 };

    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize; 
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

void ConsoleTextHelper::ClearPartScreen(short StartLine, short Height)
{
    COORD coordScreen = { 0, StartLine };

    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize; 
    HANDLE hConsole = GetConsole();

    GetConsoleScreenBufferInfo( hConsole, &csbi );

    dwConSize = csbi.dwSize.X * Height;

    FillConsoleOutputCharacter( hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten );
    FillConsoleOutputAttribute( hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten );

    SetConsoleCursorPosition( hConsole, coordScreen );
}

void ConsoleTextHelper::ClearPartScreen(short StartLine)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetConsole();

    GetConsoleScreenBufferInfo( hConsole, &csbi );

    short Height = csbi.dwSize.Y - StartLine;

    ClearPartScreen(StartLine, Height);
}

void ConsoleTextHelper::ClearBackspace()
{
    DWORD count;
    TCHAR back[] = { VK_BACK, ' ', VK_BACK };
    // COORD CursorPosition = ConsoleTextHelper::GetCursorPosition();
    WriteConsole(GetConsole(), back, std::size(back) , &count, NULL);
}


void ConsoleTextHelper::SetTextColor(Consts::TextColor TextColor)
{
    SetConsoleTextAttribute(GetConsole(), TextColor);
}


bool ConsoleTextHelper::GetAnyKey()
{
    DWORD        mode;
    INPUT_RECORD inrec;
    DWORD        count;
    HANDLE hConsole = GetConsoleInput();

    /* Check and set console mode for input */
    if ( !ConsoleTextHelper::SetConsoleModeInput( hConsole, &mode) )
    {
        return false;
    }

    /* Get a single key RELEASE */
    do
    {
        if (!ReadConsoleInput( hConsole, &inrec, 1, &count ))
        {
            std::cout << std::endl << "ConsoleTextHelper::GetAnyKey() - Read Error: " << GetLastError();
            system("pause");
            return false;
        }
    }
    while (inrec.EventType != KEY_EVENT || inrec.Event.KeyEvent.bKeyDown);

    /* Restore the original console mode */
    SetConsoleMode( hConsole, mode );

    /* Debug */
    // std::cout << "KeyCode: " << inrec.Event.KeyEvent.wVirtualKeyCode;
    // system("pause");

    return true;
}

bool ConsoleTextHelper::GetEnterKey()
{
    DWORD        mode;
    INPUT_RECORD inrec;
    DWORD        count;
    HANDLE hConsole = GetConsoleInput();

    /* Check and set console mode for input */
    if ( !ConsoleTextHelper::SetConsoleModeInput( hConsole, &mode) )
    {
        return false;
    }

    /* Get a single key RELEASE */
    do
    {
        if (!ReadConsoleInput( hConsole, &inrec, 1, &count ))
        {
            std::cout << std::endl << "ConsoleTextHelper::GetEnterKey() - Read Error: " << GetLastError();
            system("pause");
        }
    }
    while (inrec.EventType != KEY_EVENT || inrec.Event.KeyEvent.bKeyDown || inrec.Event.KeyEvent.wVirtualKeyCode != VK_RETURN);

    /* Restore the original console mode */
    SetConsoleMode( hConsole, mode );

    /* Debug */
    // std::cout << "KeyCode: " << inrec.Event.KeyEvent.wVirtualKeyCode;
    // system("pause");

    return true;
}