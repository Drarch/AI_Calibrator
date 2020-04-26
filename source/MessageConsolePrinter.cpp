#include "MessageConsolePrinter.h"

void MessageConsolePrinter::PrintIntroduction()
{
    ConsoleTextHelper::SetTextColor(Consts::TextColor::WHITE);
    std::cout << "Energy management AI developed some unwanted behaviour.\n";
    std::cout << "You need to calibrate the AI in order for it to work properly.\n";
    std::cout << "If you fail, our country will fall into darkness.\n";
    std::cout << std::endl;
    std::cout << "To calibrate the AI, you need to provide energy consumption, supply and storage for a given power grid.\n";
    std::cout << "Provide one number for energy consumption, supply and storage (3 numbers).\n";
}

void MessageConsolePrinter::PrintTutorial()
{
    ConsoleTextHelper::SetTextColor(Consts::TextColor::WHITE);
    std::cout << "Input correction for all 3 parameters using '";
    ConsoleTextHelper::SetTextColor(Consts::TextColor::RED);
    std::cout <<"X X X";
    ConsoleTextHelper::SetTextColor(Consts::TextColor::WHITE);
    std::cout << "' format.\n";
}

void MessageConsolePrinter::PrintGridInfo(int Level, int EnergySum, int EnergyProduct)
{
    ConsoleTextHelper::SetTextColor(Consts::TextColor::WHITE);
    std::cout << "Grid " << Level << " has:\n";
    std::cout << "+ Energy values between: ";
    ConsoleTextHelper::SetTextColor(Consts::TextColor::RED);
    std::cout << Level << " - " << (Level * 2) + 1 << std::endl;
    ConsoleTextHelper::SetTextColor(Consts::TextColor::WHITE);
    std::cout << "+ Sum of all energy in grid is: ";
    ConsoleTextHelper::SetTextColor(Consts::TextColor::RED);
    std::cout << EnergySum << std::endl;
    ConsoleTextHelper::SetTextColor(Consts::TextColor::WHITE);
    std::cout << "+ Multiply of all energy in grid is: ";
    ConsoleTextHelper::SetTextColor(Consts::TextColor::RED); 
    std::cout << EnergyProduct << std::endl;
    ConsoleTextHelper::SetTextColor(Consts::TextColor::WHITE);
}

void MessageConsolePrinter::PrintGridResolution(bool isGridCorrect)
{
    if (isGridCorrect)
    {
        ConsoleTextHelper::SetTextColor(Consts::TextColor::GREEN);
        std::cout << "The AI is calibrated!";
    }
    else
    {
        ConsoleTextHelper::SetTextColor(Consts::TextColor::RED);
        std::cout << "The AI needs recalibrating! Try Again.";
    }
    ConsoleTextHelper::SetTextColor(Consts::TextColor::WHITE);
    std::cout << std::endl;
}

void MessageConsolePrinter::PrintEndgame()
{
    ConsoleTextHelper::SetTextColor(Consts::TextColor::GREEN);
    std::cout << "Congratulations!\n";
    std::cout << "Thanks to you, the AI works perfectly!\n";
    ConsoleTextHelper::SetTextColor(Consts::TextColor::WHITE);
}