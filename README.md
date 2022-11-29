# CIS-190-Final
CIS 190 Final Project: Matthew Dong and Jonathan Kao

Project Proposal:
We plan to make a blackjack simulator. On a computer, can basically be a completely random game. The computer can use a near infinite deck of cards and reshuffle those cards after every round. However, this would make the game really boring as there would be no advantage in being able to memorize cards (as the deck is impossibly large and constantly reshuffuled), and the strategy component of the game would essentially disappear. We plan to make a blackjack that can be played with a user-specified number of desk of cards and reshuffled after a user-specified number of rounds. The program would also be able to keep the high/low card count of the current shoe (decks) between shuffles and quiz the user on the count. 

To implement this version of blackjack, we will have card, deck, game, and player classes that store information about the state of the game and player. We will have to use smart pointers to manage the several decks of cards that are in play. We will also use containers and operations in the algorithms library to manage the cards that are in play and to deal/reshuffle all cards. We will also use input/output streams to receive player actions (through shell) and use file input/output to keep a running ledger of player balances to allow for information retention across games. 
