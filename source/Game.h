#pragma once

#include <limits>
#include <ctime>
#include <iostream>
#include <string>

#include "Art\ArtPainter.h"
#include "Console\MessageConsolePrinter.h"
#include "Console\ConsoleTextHelper.h"

class Game
{
private:
    const COORD TextStartPosition = {0, 17};
    const WORD AllowedKeys[20] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9};
    const WORD SeparatorKeys[3] = {VK_SPACE, VK_TAB, VK_RETURN};


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