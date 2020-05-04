#pragma once

#include <ctime>
#include <iostream>

class Game
{
private:
    int Level;
    int MaxLevel;

public:
    Game(int _MaxLevel);

    void StartGame();
    bool PlayRound();
    int NextLevel();
};