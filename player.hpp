#pragma once

#include <string>

using namespace std;

class Player
{
private:
    int hands_played;
    int stack;
    string name;

public:
    Player(string name);
    Player(string name, int stack, int hands_played);
    string get_name() const;
    int get_stack() const;
    int get_hands_played() const;
    void incr_stack(int incr);
    void incr_hands_played();
};
