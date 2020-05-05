#include <iostream>

#include "source/Game.h"
#include "source/Console/ConsoleMarker.h"

int main()
{
    int MaxLevel = 5;

    // Game game(MaxLevel);
    // game.NewGame();

    ConsoleTextHelper::ClearScreen();
    ConsoleMarker::FillTextRectangle(2, 2, 7, 7, Consts::TextColor::RED);
    ConsoleMarker::FillTextRectangle(3, 3, 5, 5, Consts::TextColor::LIGHT_BLUE);
    ConsoleMarker::DrawTextRectangle(5, 4, 8, 9, Consts::TextColor::LIGHT_YELLOW);
    ConsoleMarker::DrawTextRectangle(7, 2, 9, 12, Consts::TextColor::LIGHT_PURPLE);

    system("pause");
    
    return 0;
}