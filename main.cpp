#include "game.hpp"
#include "player.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

void load_data(vector<unique_ptr<Player>> &players)
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

            unique_ptr<Player> p = make_unique<Player>(name, score, handsPlayed);
            players.push_back(move(p));
            // cout << "Player " << name << " loaded!" << endl;
        }
        cout << players.size() << " players loaded!" << endl;
        file.close();
    }
}

void save_data(vector<unique_ptr<Player>> &players)
{
    // save user score/hands played to file
    ofstream myfile;
    myfile.open("player_data.txt");
    myfile << "Name\tScore\tHands Played" << endl;

    // save all player information to file
    for (auto &player : players)
    {
        if (player)
            myfile << player->get_name() << "\t" << player->get_score() << "\t" << player->get_hands_played() << endl;
    }
    cout << players.size() << " players saved!" << endl;
    myfile.close();
}

int main()
{
    string s, playerName;
    int decks, reshuffle;
    bool gameExists = false;
    bool loggedIn = false;
    unique_ptr<Player> p;
    vector<unique_ptr<Player>> players;

    cout << "Welcome to Blackjack!" << endl;
    cout << "Commands:" << endl;
    cout << "\tstart <# of decks> <reshuffule percentage>" << endl;
    cout << "\tbet <dollars bet>" << endl;
    cout << "\thit" << endl;
    cout << "\tstay" << endl;
    cout << "\tscore" << endl;
    cout << "\tleaderboard" << endl;
    cout << "\tquit" << endl;

    load_data(players);

    cout << "Input your login: ";
    cin >> playerName;

    while (getline(cin, s)) // terminate when EOF is received
    {
        istringstream iss{s};
        string command;

        iss >> command;

        if (command == "start")
        {
            iss >> decks >> reshuffle;
            if (decks <= 0)
            {
                cout << "Invalid number of decks" << endl;
                continue;
            }
            if (reshuffle < 0 || reshuffle > 100)
            {
                cout << "Invalid reshuffle percentage" << endl;
                continue;
            }
            // generate game
            cout << "Starting game with " << decks << " decks and reshuffle at " << reshuffle << "%" << endl;
            Game g = Game(*p, decks);
            gameExists = true;
        }

        else if (command == "hit")
        {
            // TODO: implement
            if (!gameExists)
            {
                cout << "Invalid command" << endl;
                continue;
            }
        }

        else if (command == "stay")
        {
            // TODO: implement
            if (!gameExists)
            {
                cout << "Invalid command" << endl;
                continue;
            }
        }

        else if (command == "bet")
        {
            // TODO: implement
            if (!gameExists)
            {
                cout << "Invalid command" << endl;
                continue;
            }
            int bet;
            iss >> bet;
            // g.deal_hand(bet);
            // // show player hand
            // cout << "Player hand: " << endl;
            // for (auto &card : g.player_hand)
            // {
            //     cout << card.value << endl;
            // }
            // // show dealer hand
            // cout << "Dealer hand: " << endl;
            // for (auto &card : g.dealer_hand)
            // {
            //     cout << card.value << endl;
            // }
        }

        else if (command == "quit")
        {
            gameExists = false;
            loggedIn = false;
            players.push_back(move(p));

            save_data(players);

            return 0;
        }
        else
        {
            if (!loggedIn)
            { // check if player exists and login

                // for (auto &player : players)
                // {
                //     if (player->get_name() == playerName)
                //     {
                //         p = move(player);
                //         loggedIn = true;
                //         break;
                //     }
                // }

                // do this with algorithms
                auto player_exists = find_if(
                    begin(players), end(players), [playerName](auto &player)
                    { return player->get_name() == playerName; });
                if (player_exists != end(players))
                {
                    p = move(*player_exists);
                    players.erase(player_exists);
                    
                    loggedIn = true;
                    cout << "Welcome back " << playerName << "!" << endl;
                }
                else
                {
                    p = make_unique<Player>(playerName);
                    players.push_back(move(p));
                    loggedIn = true;
                    cout << "Welcome " << playerName << "!" << endl;
                }
            }
            else
                cout << "Invalid command" << endl;
        }
    }
}
