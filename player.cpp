#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "player.hpp"

Player::Player(string name) : hands_played{0},
                              stack{0},
                              name{name}
{
}

Player::Player(string name, int stack, int hands_played) : hands_played{hands_played},
                                                           stack{stack},
                                                           name{name}
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
#endif
