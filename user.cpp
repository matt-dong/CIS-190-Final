// minesweeper game
#include "user.hpp"

#include <memory>
#include <iostream>
#include <iomanip>
#include "random.hpp"

using namespace std;

user::user(string login) : handsPlayed{0},
                           score{0},
                           login{login}
{
}

int user::getScore()
{
    return score;
}

int user::getHandsPlayed()
{
    return handsPlayed;
}

void user::updateUser(int score)
{
    this->score += score;
    this->handsPlayed++;
}