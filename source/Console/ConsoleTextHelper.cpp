#include "ConsoleTextHelper.h"

HANDLE ConsoleTextHelper::GetConsole()
{
    return GetStdHandle(STD_OUTPUT_HANDLE);
}

HANDLE ConsoleTextHelper::GetConsoleInput()
{
    return GetStdHandle(STD_INPUT_HANDLE);
}


void ConsoleTextHelper::SetTextColor(Consts::TextColor TextColor)
{
    SetConsoleTextAttribute(GetConsole(), TextColor);
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


bool ConsoleTextHelper::GetAnyKey()
{
    DWORD        mode;
    INPUT_RECORD inrec;
    DWORD        count;
    HANDLE hConsole = GetConsoleInput();

    /* Check and set console mode for input */
    if (hConsole == INVALID_HANDLE_VALUE
    || !GetConsoleMode( hConsole, &mode )
    || !SetConsoleMode( hConsole, 0 ))
    {
        std::cout << "ConsoleTextHelper::GetAnyKey() - Mode Error: " << GetLastError();
        system("pause");
        return false;
    }

    FlushConsoleInputBuffer( hConsole );

    /* Get a single key RELEASE */
    do
    {
        if (!ReadConsoleInput( hConsole, &inrec, 1, &count ))
        {
            std::cout << std::endl << "ConsoleTextHelper::GetAnyKey() - Read Error: " << GetLastError();
            system("pause");
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
    if (hConsole == INVALID_HANDLE_VALUE
    || !GetConsoleMode( hConsole, &mode )
    || !SetConsoleMode( hConsole, 0 ))
    {
        std::cout << "ConsoleTextHelper::GetEnterKey() - Mode Error: " << GetLastError();
        system("pause");
        return false;
    }

    //std::cin.clear();
    FlushConsoleInputBuffer( hConsole );

    /* Get a single key RELEASE */
    do
    {
        if (!ReadConsoleInput( hConsole, &inrec, 1, &count ))
        {
            std::cout << std::endl << "ConsoleTextHelper::GetEnterKey() - Read Error: " << GetLastError();
            system("pause");
        }
    }
    while (inrec.EventType != KEY_EVENT || inrec.Event.KeyEvent.wVirtualKeyCode != VK_RETURN); //inrec.Event.KeyEvent.bKeyDown

    /* Restore the original console mode */
    SetConsoleMode( hConsole, mode );

    /* Debug */
    // std::cout << "KeyCode: " << inrec.Event.KeyEvent.wVirtualKeyCode;
    // system("pause");

    return true;
}