#include <iostream>
#include <sstream>

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

string login()
{
    string input;
    cout << "Login: " << endl;
    getline(cin, input);
    return input;
}

int main()
{
    string player_name = login();
    Game game{6, Player{player_name, 0}};

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
        else if (command == "hint" && game.is_active())
        {
            game.get_hint();
        }
        else if (command == "quit")
        {
        }
        else
        {
        }

        cout << game;
    }
}