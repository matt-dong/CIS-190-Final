#include "game.hpp"
#include "player.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
    string s, playerName;
    bool gameExists = false;
    bool loggedIn = false;
    int numMines;
    unique_ptr<Player> p;
    unique_ptr<Game> g;
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

    cout << "Input your login: ";
    cin >> playerName;

    while (getline(cin, s)) // terminate when EOF is received
    {
        istringstream iss{s};
        string command;

        iss >> command;

        if (command == "start")
        {
            int decks, reshuffle;
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
            g = make_unique<game>(width, height);
            // print game
            cout << *g << endl;
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
        else if (command == "quit")
        {
            gameExists = false;
            loggedIn = false;

            // save user score/hands played to file
            ofstream myfile;
            myfile.open("player_data.txt");
            myfile << "Name\tScore\tHands Played"<< endl;
            for (auto &player : players)
            {
                myfile << player->get_name() << "\t" << player->get_score() << "\t" << player->get_hands_played() << endl;
            }
            myfile.close();

            break;
        }
        else
        {
            if (!loggedIn)
            {
                cout << "Welcome " << playerName << "!" << endl;
                p = make_unique<Player>(playerName);
                players.push_back(move(p));
                loggedIn = true;
            }
            else
                cout << "Invalid command" << endl;
        }
    }
}
