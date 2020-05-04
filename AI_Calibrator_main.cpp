#include <iostream>

#include "source/Game.h"

int main()
{
    int MaxLevel = 5;

    Game game(MaxLevel);
    game.NewGame();

    system("pause");
    
    return 0;
}