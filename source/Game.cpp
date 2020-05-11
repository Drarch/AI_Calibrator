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

    DrawArt();
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

    MessageConsolePrinter::PrintPressEnter();
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
    MessageConsolePrinter::PrintPressAnyKey();
    // std::cout << std::endl << "Debug: " << GridInput[0] << " " << GridInput[1] << " " << GridInput[2];
    ConsoleTextHelper::GetAnyKey();

    return isSumCorrect && isProductCorrect;
}

void Game::GetRoundInput(int GridInput[3])
{
    std::cout << "Input: ";

    std::string Input = "";

    int i = 0;
    DWORD        mode;
    INPUT_RECORD inrec;
    DWORD        count;
    HANDLE hConsoleIn = ConsoleTextHelper::GetConsoleInput();

    /* Check and set console mode for input */
    if ( !ConsoleTextHelper::SetConsoleModeInput( hConsoleIn, &mode) )
    {
        return ;
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

    std::cout << std::endl;
}

void Game::DrawArt()
{
    // ConsoleMarker::DebugTextElbowLine();

    ArtPainter::DrawAI();
    ArtPainter::DrawCell({5,5});
}

void Game::ResetScreen()
{
    ConsoleTextHelper::ClearPartScreen(TextStartPosition.Y);
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