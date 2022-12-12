#include "game.hpp"
#include <memory>
#include <iostream>
#include <iomanip>

using namespace std;

Game::Game(Player player) : score{0},
                            player{player}
{
}

