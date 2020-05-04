#pragma once

#include <iostream>
#include "ConsoleTextHelper.h"

class MessageConsolePrinter
{
private:
    static char* CorrectnesMessage(bool isCorrect);

public:
    static void PrintIntroduction();
    static void PrintTutorial();
    static void PrintGridInfo(int Level, int EnergySum, int EnergyProduct);
    static void PrintGridResolution(bool isSumCorrect, bool isProductCorrect);
    static void PrintEndgame();
};