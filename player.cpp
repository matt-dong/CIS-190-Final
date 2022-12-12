#include "player.hpp"

Player::Player(string name, int stack) : name{name}, stack{stack}
{
}

string Player::get_name() const
{
    return name;
}

int Player::get_stack() const
{
    return stack;
}

int Player::get_hands_played() const
{
    return hands_played;
}

void Player::incr_stack(int incr)
{
    stack += incr;
}

void Player::incr_hands_played()
{
    hands_played++;
}