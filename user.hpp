#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <memory>

using namespace std;

class user
{
private:
    int handsPlayed;
    int score;
    string login;

public:
    user(string login);
    int getScore();
    int getHandsPlayed();

    // called everytime a round is finished
    void updateUser(int score);
};

#endif
