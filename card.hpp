#ifndef CARD_HPP
#define CARD_HPP
#include <iostream>
#include <vector>

using namespace std;

struct Card
{
    string suit;
    int value; // 1 = Ace, 2-10 = 2-10, 11 = Jack, 12 = Queen, 13 = King
};

class Deck
{
private:
    vector<Card> cards;
    int num_decks;

public:
    Deck(int num_decks = 1);
    vector<Card> get_cards();
    Card draw();
    double percent_left();
    void shuffle();
};

#endif
