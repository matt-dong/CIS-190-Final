#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>

class Card
{
private:
    int value, suit;

public:
    Card(int value, int suit);
    int get_value() const;
    int get_suit() const;
    friend ostream &operator<<(ostream &os, const Card &c);
};

#endif