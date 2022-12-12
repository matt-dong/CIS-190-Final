#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "card.hpp"

using namespace std;

const vector<string> suits = {"Hearts", "Diamonds", "Spades", "Clubs"};

// Create a deck of num_decks* 52 cards
Deck::Deck(int num_decks) : num_decks{num_decks}
{
    for (int i = 0; i < num_decks; i++)
    {
        for (const auto &suit : suits)
        {
            for (auto i = 1; i <= 13; ++i)
            {
                Card card;
                card.suit = suit;
                card.value = i;
                cards.push_back(card);
            }
        }
    }
    shuffle();
}

// Draw a card from the deck
Card Deck::draw()
{
    Card card = cards.back();
    cards.pop_back();
    return card;
}

// check percentage of cards left in the deck
double Deck::percent_left()
{
    return cards.size() / (num_decks * 52);
}

// shuffle the deck
void Deck::shuffle()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), default_random_engine(seed));
}