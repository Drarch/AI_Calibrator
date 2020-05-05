#pragma once

#include <ctime>
#include <iostream>

#include "MessageConsolePrinter.h"
#include "ConsoleTextHelper.h"

class Game
{
private:
    int Level;
    int MaxLevel;

public:
    Game(int _MaxLevel);

    void NewGame();
    bool PlayRound();
    int NextLevel();
};