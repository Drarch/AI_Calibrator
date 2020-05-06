#pragma once

#include <limits>
#include <ctime>
#include <iostream>

#include "Art\ArtPainter.h"
#include "MessageConsolePrinter.h"
#include "Console\ConsoleTextHelper.h"

class Game
{
private:
    const COORD TextStartPosition = {0, 17};

    int Level;
    int MaxLevel;

    void ResetScreen();
    void DrawArt();

public:
    Game(int _MaxLevel);

    void NewGame();
    bool MainMenu();
    bool PlayRound();
    int NextLevel();
};