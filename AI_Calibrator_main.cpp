#include <iostream>

#include "source/Game.h"
#include "source/Console/ConsoleMarker.h"

int main()
{
    int MaxLevel = 5;

    Game game(MaxLevel);
    game.NewGame();

    // ConsoleTextHelper::ClearScreen();
    // ConsoleMarker::FillRectangle(2, 2, 7, 7, Consts::TextColor::RED);
    // ConsoleMarker::FillRectangle(3, 3, 6, 6, Consts::TextColor::LIGHT_BLUE);

    system("pause");
    
    return 0;
}