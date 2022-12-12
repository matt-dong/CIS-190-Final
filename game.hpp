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
    int score;
    Player player;
    vector<Card> player_hand;
    vector<Card> dealer_hand;
    Deck deck;

public:
    Game(Player player);
    void deal_hand(int bet);
    void hit();
    void stand();
    friend ostream &operator<<(ostream &os, const Game &g);
};

#endif
