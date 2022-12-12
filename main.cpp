#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <array>
#include <memory>

#include "player.hpp"
#include "game.hpp"

using namespace std;

void print_instructions()
{
    cout << "-------------------------" << endl;
    cout << "Welcome to Blackjack!" << endl;
    cout << "Commands:" << endl;
    cout << "\thit" << endl;
    cout << "\tstand" << endl;
    cout << "\tbet <dollars bet>" << endl;
    cout << "\thint" << endl;
    cout << "\tscore" << endl;
    cout << "\tleaderboard" << endl;
    cout << "\tquit" << endl;
    cout << "-------------------------" << endl;
}

void load_data(vector<shared_ptr<Player>> &players)
{
    string s;
    ifstream file("player_data.txt");
    if (file.is_open())
    {
        while (getline(file, s))
        {
            istringstream iss(s);
            string name;
            int score, handsPlayed;
            iss >> name >> score >> handsPlayed;
            if (!iss)
            { // reads an invalid input
                continue;
            }

            shared_ptr<Player> p = make_shared<Player>(name, score, handsPlayed);
            players.push_back(move(p));
        }
        cout << players.size() << " players loaded!" << endl;
        file.close();
    }
}

void save_data(vector<shared_ptr<Player>> &players)
{
    // save user score/hands played to file
    ofstream myfile;
    myfile.open("player_data.txt");
    myfile << "Name\tScore\tHands Played" << endl;

    // save all player information to file
    for (auto &player : players)
    {
        if (player)
            myfile << player->get_name() << "\t" << player->get_stack() << "\t" << player->get_hands_played() << endl;
    }
    cout << players.size() << " players saved!" << endl;
    myfile.close();
}

void leaderboard(vector<shared_ptr<Player>> &players)
{
    // don't modify or sort original vector
    vector<shared_ptr<Player>> leaders(min(5, (int)players.size()));
    partial_sort_copy(
        begin(players), end(players),
        begin(leaders), end(leaders),
        [](auto &p1, auto &p2)
        { return p1->get_stack() > p2->get_stack(); });

    cout << "Player Leaderboard:" << endl;
    for (auto player : leaders)
        cout << player->get_name() << "\t" << player->get_stack() << endl;
}

shared_ptr<Player> login(vector<shared_ptr<Player>> &players)
{
    string playerName;
    shared_ptr<Player> p;
    cout << "Login: " << endl;
    getline(cin, playerName);

    // do this with algorithms
    auto player_exists = find_if(
        begin(players), end(players), [playerName](auto &player)
        { return player->get_name() == playerName; });
    if (player_exists != end(players))
    {
        p = *player_exists;
        cout << "Welcome back " << playerName << "!" << endl;
    }
    else
    {
        p = make_shared<Player>(playerName);
        players.push_back(p);
        cout << "Welcome " << playerName << "!" << endl;
    }
    return p;
}

int main()
{
    vector<shared_ptr<Player>> players;
    load_data(players);

    shared_ptr<Player> player = login(players);
    Game game{6, player};

    print_instructions();
    string input;

    while (getline(cin, input))
    {
        istringstream iss{input};
        string command;
        iss >> command;

        cout << "-------------------------" << endl;

        if (command == "hit" && game.is_active())
        {
            game.hit_player();
        }
        else if (command == "stand" && game.is_active())
        {
            game.stand();
        }
        else if (command == "bet" && !game.is_active())
        {
            int amount;
            iss >> amount;
            cout << "Amount Wagered: " << amount << endl;
            cout << "Account Balance: " << game.get_balance() << endl;
            if (game.is_profitable())
            {
                cout << "Hint: based on the true count of " << game.get_true_count() << " this was a +EV bet" << endl;
            }
            else
            {
                cout << "Hint: based on the true count of " << game.get_true_count() << " this was a -EV bet" << endl;
            }
            game.deal_hand(amount);
            cout << "-------------------------" << endl;
        }
        else if (command == "leaderboard")
        {
            leaderboard(players);
        }
        else if (command == "hint" && game.is_active())
        {
            game.get_hint();
        }
        else if (command == "quit")
        {
            save_data(players);
            return 0;
        }
        else if (command == "score")
        {
            cout << "You have " << game.get_balance() << " dollars" << endl;
            continue;
        }
        else
        {
        }

        cout << game;
    }
}