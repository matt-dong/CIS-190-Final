#ifndef GAME_HPP
#define GAME_HPP

#include <algorithm>
#include <random>
#include <chrono>

#include "game.hpp"

Game::Game(int num_decks, shared_ptr<Player> player) : bet{0}, num_decks{num_decks}, active_hand{false}, player{player}, player_hand(), dealer_hand(), deck()
{
}

bool Game::is_active() const
{
    return active_hand;
}

int Game::get_balance() const
{
    return active_hand ? player->get_stack() - bet : player->get_stack();
}

void Game::reshuffle()
{
    deck.clear();
    for (int i = 0; i < 52; ++i)
    {
        for (int j = 0; j < num_decks; ++j)
        {
            deck.push_back(i);
        }
    }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rng{seed};
    shuffle(deck.begin(), deck.end(), rng);
}

void Game::deal_hand(int bet)
{
    if (deck.size() < 4)
    {
        reshuffle();
    }
    this->bet = bet;
    player_hand.clear();
    dealer_hand.clear();
    player_hand.push_back(deck.at(deck.size() - 1));
    player_hand.push_back(deck.at(deck.size() - 2));
    dealer_hand.push_back(deck.at(deck.size() - 3));
    dealer_hand.push_back(deck.at(deck.size() - 4));
    deck.resize(deck.size() - 4);
    active_hand = true;
    player->incr_hands_played();
}

void Game::hit(vector<int> &hand)
{
    if (deck.size() < 1)
    {
        reshuffle();
    }
    hand.push_back(deck.at(deck.size() - 1));
    deck.resize(deck.size() - 1);
}

void Game::hit_player()
{
    hit(player_hand);
    int score = evaluate(player_hand);
    if (score > 21)
    {
        end_turn();
    }
}

void Game::stand()
{
    int dealer = evaluate(dealer_hand);
    while (dealer < 17)
    {
        hit(dealer_hand);
        dealer = evaluate(dealer_hand);
    }
    end_turn();
}

int Game::evaluate(vector<int> &hand)
{
    int low = 0;
    int high = 0;
    for (int card : hand)
    {
        int score = (card % 13 >= 9 ? 9 : card % 13) + 1;
        if (score == 1)
        {
            low += 1;
            high += 11;
        }
        else
        {
            low += score;
            high += score;
        }
    }
    return high <= 21 ? high : low;
}

void Game::end_turn()
{
    int player_score = evaluate(player_hand);
    int dealer_score = evaluate(dealer_hand);
    cout << *this;
    if (player_score == 21 && player_hand.size() == 2)
    {
        cout << "Blackjack! Pays 2:1" << endl;
        player->incr_stack(bet * 2);
    }
    else if (dealer_score > 21)
    {
        cout << "Dealer Busts! Player wins" << endl;
        player->incr_stack(bet);
    }
    else if (player_score > 21)
    {
        cout << "Player Busts! Dealer wins" << endl;
        player->incr_stack(-1 * bet);
    }
    else if (player_score > dealer_score)
    {
        cout << "Player wins!" << endl;
        player->incr_stack(bet);
    }
    else if (player_score < dealer_score)
    {
        cout << "Dealer wins!" << endl;
        player->incr_stack(-1 * bet);
    }
    else
    {
        cout << "Player and dealer tie. Push!" << endl;
    }
    cout << "-------------------------" << endl;
    cout << "Account Balance: " << player->get_stack() << endl;
    cout << "-------------------------" << endl;
    active_hand = false;
}

string translate(int card)
{
    string res;
    int value = (card % 13) + 1;
    int suit = card / 13;
    if (value == 1)
    {
        res += "A";
    }
    else if (1 < value && value < 10)
    {
        res += to_string(value);
    }
    else if (value == 10)
    {
        res += "T";
    }
    else if (value == 11)
    {
        res += "J";
    }
    else if (value == 12)
    {
        res += "Q";
    }
    else
    {
        res += "K";
    }
    if (suit == 0)
    {
        res += "s";
    }
    else if (suit == 1)
    {
        res += "h";
    }
    else if (suit == 2)
    {
        res += "c";
    }
    else
    {
        res += "d";
    }
    return res;
}

ostream &operator<<(ostream &os, const Game &g)
{
    if (!g.active_hand)
    {
        return os;
    }
    os << "Dealer Hand:" << endl;
    for (int hand : g.dealer_hand)
    {
        os << translate(hand) << " ";
    }
    os << endl;
    os << "Player Hand:" << endl;
    for (int hand : g.player_hand)
    {
        os << translate(hand) << " ";
    }
    os << endl;
    cout << "-------------------------" << endl;
    return os;
}

#endif