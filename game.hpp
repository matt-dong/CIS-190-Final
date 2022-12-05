#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <memory>
#include <iostream>

#include "player.hpp"
#include "card.hpp"

using namespace std;

class Game
{
private:
    int bet;
    Player player;
    vector<unique_ptr<Card>> player_hand;
    vector<unique_ptr<Card>> dealer_hand;
    vector<unique_ptr<Card>> deck;

public:
    Game(Player player);
    void reshuffle(int num_decks);
    void deal_hand(int bet);
    void hit();
    void stand();
    friend ostream &operator<<(ostream &os, const Game &g);
};

#endif