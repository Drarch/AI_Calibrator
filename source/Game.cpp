#include "Game.h"

Game::Game(int _MaxLevel)
{
    Level = 1;
    MaxLevel = _MaxLevel;
}


void Game::NewGame()
{
    srand(time(NULL));
    Level = 1;

    MainMenu();

    while (MaxLevel >= Level)
    {
        ResetScreen();
        if (this->PlayRound()) this->NextLevel();
        // std::cin.clear(); std::cin.ignore();
    }
    
    MessageConsolePrinter::PrintEndgame();
}

bool Game::MainMenu()
{
    ResetScreen();
    MessageConsolePrinter::PrintIntroduction();
    std::cout << std::endl;
    std::cout << "Press Enter to Continue";

    ConsoleTextHelper::GetEnterKey();

    return true;
}

bool Game::PlayRound()
{
    // std::cout << std::endl;

    // Declare grid variables
    int Grid[3] =
    {
        rand() % (Level + 2) + Level,
        rand() % (Level + 2) + Level,
        rand() % (Level + 2) + Level
    };

    int EnergySum = Grid[0] + Grid[1] + Grid[2];
    int EnergyProduct = Grid[0] * Grid[1] * Grid[2];
    
    MessageConsolePrinter::PrintGridInfo(Level, EnergySum, EnergyProduct);
    MessageConsolePrinter::PrintTutorial();

    // Declare input variables
    int GridInput[3] = {-1, -1, -1};

    // Get input
    GetRoundInput(GridInput);

    int GuessSum = GridInput[0] + GridInput[1] + GridInput[2];
    int GuessProduct = GridInput[0] * GridInput[1] * GridInput[2];

    bool isSumCorrect = EnergySum == GuessSum;
    bool isProductCorrect = EnergyProduct == GuessProduct;


    MessageConsolePrinter::PrintGridResolution(isSumCorrect, isProductCorrect);
    std::cout << "Press any to continue";
    std::cout << std::endl << "Debug: " << GridInput[0] << " " << GridInput[1] << " " << GridInput[2];
    ConsoleTextHelper::GetAnyKey();
    // ConsoleTextHelper::GetEnterKey();

    return isSumCorrect && isProductCorrect;
}

void Game::GetRoundInput(int GridInput[3])
{
    std::cout << "Input: ";

    WORD AllowedKeys[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9};
    WORD SeparatorKeys[] = {VK_SPACE, VK_TAB, VK_RETURN};

    std::string Input = "";

    int i = 0;
    DWORD        mode;
    INPUT_RECORD inrec;
    DWORD        count;
    HANDLE hConsoleIn = ConsoleTextHelper::GetConsoleInput();

    /* Check and set console mode for input */
    if (hConsoleIn == INVALID_HANDLE_VALUE
    || !GetConsoleMode( hConsoleIn, &mode )
    || !SetConsoleMode( hConsoleIn, 0 ))
    {
        std::cout << "Game::GetRoundInput() - Mode Error: " << GetLastError();
        system("pause");
        return;
    }

    if(!FlushConsoleInputBuffer( hConsoleIn ))
    {
        std::cout << "Game::GetRoundInput() - Flush Error: " << GetLastError();
        system("pause");
        return;
    }

    /* Get input values */
    do
    {
        if (!ReadConsoleInput( hConsoleIn, &inrec, 1, &count ))
        {
            std::cout << std::endl << "Game::GetRoundInput() - Read Error: " << GetLastError();
            system("pause");
        }

        if (inrec.EventType == KEY_EVENT && inrec.Event.KeyEvent.bKeyDown)
        {
            if ( Contains(AllowedKeys, inrec.Event.KeyEvent.wVirtualKeyCode ))
            {
                Input += inrec.Event.KeyEvent.uChar.AsciiChar;
                std::cout << inrec.Event.KeyEvent.uChar.AsciiChar;
            }
            else if ( inrec.Event.KeyEvent.wVirtualKeyCode == VK_BACK )
            {
                if(!Input.empty())
                {
                    Input.pop_back();
                    ConsoleTextHelper::ClearBackspace();
                }
                else if(Input.empty() && i > 0)
                {
                    ConsoleTextHelper::ClearBackspace();
                    i--;
                    Input = std::to_string(GridInput[i]);
                }
                else
                {
                    // Do nothing
                }
            }
            else if ( Contains(SeparatorKeys, inrec.Event.KeyEvent.wVirtualKeyCode) && Input != "" )
            {
                GridInput[i] = std::stoi(Input);
                Input.clear();
                i++;
                if (i < 3) std::cout << " ";
            }
        }
    }
    while (inrec.EventType != KEY_EVENT || inrec.Event.KeyEvent.bKeyDown || i < 3);

    /* Restore the original console mode */
    SetConsoleMode( hConsoleIn, mode );
    // std::cin.clear();
    std::cout << std::endl;
}

void Game::DrawArt()
{
    ArtPainter::DrawAI();
}

void Game::ResetScreen()
{
    ConsoleTextHelper::ClearScreen();
    DrawArt();
    ConsoleTextHelper::SetCursorPosition(TextStartPosition);
}

int Game::NextLevel()
{
    return Level++;
}


template<typename T, size_t N>
bool Game::Contains(const T (&Table)[N], const T &Element)
{
    auto b = std::begin(Table);
    auto e = std::end(Table);

    return std::find(b, e, Element) != e;
}