#include "source/Game.h"
#include "source/Console/ConsoleMarker.h"

int main()
{
    int MaxLevel = 5;

    Game game(MaxLevel);
    game.NewGame();

    system("pause");
    
    return 0;
}