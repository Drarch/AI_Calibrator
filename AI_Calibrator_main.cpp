#include <iostream>
#include <ctime>

// #include "source/ConsoleTextHelper.h"
#include "source/MessageConsolePrinter.h"

char* correctnesMessage(bool isCorrect)
{
    if (isCorrect)
    {
        return "correct";
    }

    return "incorrect";
}

bool PlayGame(int Level)
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

    // Output guess message
    std::cout << "Sum is " << correctnesMessage(EnergySum == GuessSum);
    std::cout << " and multiply is " << correctnesMessage(EnergyProduct == GuessProduct) << ".\n";

    bool isGridCorrect = false;
    isGridCorrect = EnergySum == GuessSum && EnergyProduct == GuessProduct;

    MessageConsolePrinter::PrintGridResolution(isGridCorrect);
    system("pause");
    
    return isGridCorrect;
}

int main()
{
    srand(time(NULL));
    int Level = 1;
    int MaxLevel = 5;

    ConsoleTextHelper::SetTextColor(Consts::TextColor::WHITE);
    MessageConsolePrinter::PrintIntroduction();

    while (Level <= MaxLevel)
    {
        if (PlayGame(Level)) ++Level;
        std::cin.clear();
        std::cin.ignore();
    }
    
    ConsoleTextHelper::SetTextColor(Consts::TextColor::GREEN);
    std::cout << "Congratulations!\n";
    std::cout << "Thanks to you, the AI works perfectly!\n";
    ConsoleTextHelper::SetTextColor(Consts::TextColor::WHITE);
    system("pause");
    
    return 0;
}