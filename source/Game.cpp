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

    COORD TextStartPosition = {0, 17};

    ConsoleTextHelper::ClearScreen();
    ConsoleTextHelper::SetCursorPosition(TextStartPosition);
    MessageConsolePrinter::PrintIntroduction();

    while (MaxLevel >= Level)
    {
        if (this->PlayRound()) this->NextLevel();
        ConsoleTextHelper::ClearScreen();
        ConsoleTextHelper::SetCursorPosition(TextStartPosition);
        std::cin.clear();
        std::cin.ignore();
    }
    
    MessageConsolePrinter::PrintEndgame();
}

bool Game::PlayRound()
{
    // std::cout << std::endl;

    // Declare grid variables
    int EnergyConsumption = rand() % (Level + 2) + Level;
    int EnergySupply =      rand() % (Level + 2) + Level;
    int EnergyStorage =     rand() % (Level + 2) + Level;

    int EnergySum = EnergyConsumption + EnergySupply + EnergyStorage;
    int EnergyProduct = EnergyConsumption * EnergySupply * EnergyStorage;
    
    MessageConsolePrinter::PrintGridInfo(Level, EnergySum, EnergyProduct);
    MessageConsolePrinter::PrintTutorial();

    // Declare input variables
    int EnergyConsumptionInput = -1;
    int EnergySupplyInput = -1;
    int EnergyStorageInput = -1;

    // Get input
    std::cout << "Input: ";
    std::cin >> EnergyConsumptionInput >> EnergySupplyInput >> EnergyStorageInput;

    int GuessSum = EnergyConsumptionInput + EnergySupplyInput + EnergyStorageInput;
    int GuessProduct = EnergyConsumptionInput * EnergySupplyInput * EnergyStorageInput;

    bool isSumCorrect = EnergySum == GuessSum;
    bool isProductCorrect = EnergyProduct == GuessProduct;

    MessageConsolePrinter::PrintGridResolution(isSumCorrect, isProductCorrect);
    system("pause");
    
    return isSumCorrect && isProductCorrect;
}

int Game::NextLevel()
{
    return Level++;
}
