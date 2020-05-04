#include "Game.h"
#include "MessageConsolePrinter.h"

Game::Game(int _MaxLevel)
{
    Level = 1;
    MaxLevel = _MaxLevel;
}


void Game::StartGame()
{
    srand(time(NULL));
    
    MessageConsolePrinter::PrintIntroduction();

    while (MaxLevel >= Level)
    {
        if (this->PlayRound()) (*this).NextLevel();
        std::cin.clear();
        std::cin.ignore();
    }
    
    MessageConsolePrinter::PrintEndgame();
}

bool Game::PlayRound()
{
    std::cout << std::endl;
    MessageConsolePrinter::PrintTutorial();

    // Declare grid variables
    int EnergyConsumption = rand() % (Level + 2) + Level;
    int EnergySupply =      rand() % (Level + 2) + Level;
    int EnergyStorage =     rand() % (Level + 2) + Level;

    int EnergySum = EnergyConsumption + EnergySupply + EnergyStorage;
    int EnergyProduct = EnergyConsumption * EnergySupply * EnergyStorage;
    
    // std::cout << "Debug: " << EnergyConsumption << " " << EnergySupply << " " << EnergyStorage << std::endl;
    MessageConsolePrinter::PrintGridInfo(Level, EnergySum, EnergyProduct);

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
