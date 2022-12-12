#pragma once

#include <string>

using namespace std;

class Player
{
private:
    string name;
    int stack, hands_played;

public:
    Player(string name, int stack);
    string get_name() const;
    int get_stack() const;
    int get_hands_played() const;
    void incr_stack(int incr);
    void incr_hands_played();
};
