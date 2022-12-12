# Blackjack

## CIS 190 Final Project: Matthew Dong and Jonathan Kao

**Project Proposal:**

We plan to make a blackjack simulator. On a computer, can basically be a completely random game. The computer can use a near infinite deck of cards and reshuffle those cards after every round. However, this would make the game really boring as there would be no advantage in being able to memorize cards (as the deck is impossibly large and constantly reshuffuled), and the strategy component of the game would essentially disappear. We plan to make a blackjack that can be played with a user-specified number of desk of cards and reshuffled after a user-specified number of rounds. The program would also be able to keep the high/low card count of the current shoe (decks) between shuffles and quiz the user on the count. 

To implement this version of blackjack, we will have card, deck, game, and player classes that store information about the state of the game and player. We will have to use smart pointers to manage the several decks of cards that are in play. We will also use containers and operations in the algorithms library to manage the cards that are in play and to deal/reshuffle all cards. We will also use input/output streams to receive player actions (through shell) and use file input/output to keep a running ledger of player balances to allow for information retention across games. With the player information stored, we will be able to create a leaderboard command that prints the top 5 balances and the corresponding number of hands that the player has played.

**Timeline:**
 - By the project checkpoint (12/5), we aim to get the initial setup for the blackjack logic done. Also, we want to be able to have file input/output and the player class setup to properly store player data.
 - By the final checkpoint (12/12), we will add the card counting/quizzing and leaderboard features along with ability to specify the number of decks a player can play with and the game's reshuffling frequency.
