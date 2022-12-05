#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>

using namespace std;

class Player
{
private:
    string name;
    int stack;

public:
    Player(string, int stack);
    string get_name() const;
    int get_stack() const;
    friend ostream &operator<<(ostream &os, const Player &p);
};

#endif
