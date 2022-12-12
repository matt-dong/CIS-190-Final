#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <memory>

#include "player.hpp"

using namespace std;

class Game
{
private:
    int bet, num_decks;
    bool active_hand;
    shared_ptr<Player> player;
    vector<int> player_hand;
    vector<int> dealer_hand;
    vector<int> deck;

    void reshuffle();
    void hit(vector<int> &hand);
    int evaluate(vector<int> &hand);
    void end_turn();
    string translate(int card);

public:
    Game(int num_decks, shared_ptr<Player> player);
    bool is_active() const;
    int get_balance() const;
    void deal_hand(int bet);
    void hit_player();
    void stand();
    friend ostream &operator<<(ostream &os, const Game &g);
};
