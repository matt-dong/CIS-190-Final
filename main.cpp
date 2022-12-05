#include "game.hpp"

#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    string s, playerName;
    bool gameExists = false;
    bool loggedIn = false;
    int numMines;
    unique_ptr<game> g;

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
            // TODO: need to save user score/hands played to file
            break;
        }
        else
        {
            if (!loggedIn)
            {
                cout << "Welcome " << playerName << "!" << endl;
                loggedIn = true;
            }
            else
                cout << "Invalid command" << endl;
        }
    }
}
