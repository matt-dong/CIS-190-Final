#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>

using namespace std;

class Player
{
private:
    int handsPlayed;
    int score;
    string name;

public:
    Player(string name);
    Player(string name, int score, int handsPlayed);
    string get_name() const;
    int get_score();
    int get_hands_played();
    friend ostream &operator<<(ostream &os, const Player &p);

    // called everytime a round is finished
    void update_player(int score);
};

#endif
