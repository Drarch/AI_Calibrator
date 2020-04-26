#pragma once

#include <iostream>
#include "ConsoleTextHelper.h"

class MessageConsolePrinter
{
private:


public:
    static void PrintIntroduction();
    static void PrintTutorial();
    static void PrintGridInfo(int Level, int EnergySum, int EnergyProduct);
    static void PrintGridResolution(bool isGridCorrect);
    static void PrintEndgame();
};