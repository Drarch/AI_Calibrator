#pragma once

#include <ctime>
#include <iostream>

#include "Art\ArtPainter.h"
#include "MessageConsolePrinter.h"
#include "Console\ConsoleTextHelper.h"

class Game
{
private:
    int Level;
    int MaxLevel;

    void DrawArt();

public:
    Game(int _MaxLevel);

    void NewGame();
    bool PlayRound();
    int NextLevel();
};