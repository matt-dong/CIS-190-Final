#include "game.hpp"
#include <memory>
#include <iostream>
#include <iomanip>

using namespace std;

Game::Game(Player player, int num_decks) : score{0},
                                           player{player}
{
    deck = Deck(num_decks);
    deck.shuffle();
}

void Game::deal_hand(int bet)
{
    player_hand.push_back(deck.draw());
    player_hand.push_back(deck.draw());

    dealer_hand.push_back(deck.draw());
    dealer_hand.push_back(deck.draw());
}
