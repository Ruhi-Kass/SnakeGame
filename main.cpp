#include "SnakeGame.h"
#include <iostream>

int main()
{
    std::cout << "=== Flicker-Free Modular Snake ===\n"
                 "Press any key to start...\n";
    _getch();

    SnakeGame game;
    game.run();

    return 0;
}