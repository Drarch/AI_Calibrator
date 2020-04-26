#include <iostream>
#include <ctime>

#include "source/ConsoleTextHelper.h"

char* correctnesMessage(bool isCorrect)
{
    if (isCorrect)
    {
        return "correct";
    }

    return "incorrect";
}

void PrintIntroduction()
{
    std::cout << "Energy management AI developed some unwanted behaviour.\n";
    std::cout << "You need to calibrate the AI in order for it to work properly.\n";
    std::cout << "If you fail, our country will fall into darkness.\n";
    std::cout << std::endl;
    std::cout << "To calibrate the AI, you need to provide energy consumption, supply and storage for a given power grid.\n";
    std::cout << "Provide one number for energy consumption, supply and storage (3 numbers).\n";
}

void PrintTutorial()
{
    std::cout << "Input correction for all 3 parameters using '";
    ConsoleTextHelper::SetTextColor(TextColor::RED);
    std::cout <<"X X X";
    ConsoleTextHelper::SetTextColor(TextColor::WHITE);
    std::cout << "' format.\n";
}

void PrintGridInfo(int Level, int EnergySum, int EnergyProduct)
{
    std::cout << "Grid " << Level << " has:\n";
    std::cout << "+ Energy values between: ";
    ConsoleTextHelper::SetTextColor(TextColor::RED);
    std::cout << Level << " - " << (Level * 2) + 1 << std::endl;
    ConsoleTextHelper::SetTextColor(TextColor::WHITE);
    std::cout << "+ Sum of all energy in grid is: ";
    ConsoleTextHelper::SetTextColor(TextColor::RED);
    std::cout << EnergySum << std::endl;
    ConsoleTextHelper::SetTextColor(TextColor::WHITE);
    std::cout << "+ Multiply of all energy in grid is: ";
    ConsoleTextHelper::SetTextColor(TextColor::RED); 
    std::cout << EnergyProduct << std::endl;
    ConsoleTextHelper::SetTextColor(TextColor::WHITE);
}

void PrintCheckMessage(bool isGridCorrect)
{
    if (isGridCorrect)
    {
        ConsoleTextHelper::SetTextColor(TextColor::GREEN);
        std::cout << "The AI is calibrated!";
    }
    else
    {
        ConsoleTextHelper::SetTextColor(TextColor::RED);
        std::cout << "The AI needs recalibrating! Try Again.";
    }
    ConsoleTextHelper::SetTextColor(TextColor::WHITE);
    std::cout << std::endl;
}

bool PlayGame(int Level)
{
    std::cout << std::endl;
    PrintTutorial();

    // Declare grid variables
    int EnergyConsumption = rand() % (Level + 2) + Level;
    int EnergySupply =      rand() % (Level + 2) + Level;
    int EnergyStorage =     rand() % (Level + 2) + Level;

    int EnergySum = EnergyConsumption + EnergySupply + EnergyStorage;
    int EnergyProduct = EnergyConsumption * EnergySupply * EnergyStorage;
    
    // std::cout << "Debug: " << EnergyConsumption << " " << EnergySupply << " " << EnergyStorage << std::endl;
    PrintGridInfo(Level, EnergySum, EnergyProduct);

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

    PrintCheckMessage(isGridCorrect);
    system("pause");
    
    return isGridCorrect;
}

int main()
{
    srand(time(NULL));
    int Level = 1;
    int MaxLevel = 5;

    ConsoleTextHelper::SetTextColor(TextColor::WHITE);
    PrintIntroduction();

    while (Level <= MaxLevel)
    {
        if (PlayGame(Level)) ++Level;
        std::cin.clear();
        std::cin.ignore();
    }
    
    ConsoleTextHelper::SetTextColor(TextColor::GREEN);
    std::cout << "Congratulations!\n";
    std::cout << "Thanks to you, the AI works perfectly!\n";
    ConsoleTextHelper::SetTextColor(TextColor::WHITE);
    system("pause");
    
    return 0;
}