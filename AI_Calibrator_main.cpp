#include <iostream>

#include "source/Game.h"

int main()
{
    int MaxLevel = 5;

    Game game(MaxLevel);
    game.StartGame();
    
    system("pause");
    
    return 0;
}