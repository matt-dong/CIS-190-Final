#include "game.hpp"
#include <memory>
#include <iostream>
#include <iomanip>

using namespace std;

Game::Game(Player player) : score{0},
                            player{player}
{
}

void Game::deal_hand(int bet)
{
    player_hand.push_back(deck.draw());
    player_hand.push_back(deck.draw());

    dealer_hand.push_back(deck.draw());
    dealer_hand.push_back(deck.draw());
}
