#pragma once

#include <limits>
#include <ctime>
#include <iostream>
#include <string>

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
    
    template<typename T, size_t N>
    bool Contains(const T (&Table)[N], const T &Element);
public:
    Game(int _MaxLevel);

    void NewGame();
    bool MainMenu();
    bool PlayRound();
    void GetRoundInput(int GridInput[3]);
    int NextLevel();
};