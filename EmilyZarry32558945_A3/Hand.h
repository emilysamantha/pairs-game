#ifndef HAND_H
#define HAND_H
#include "Card.h"

class Hand 
{
public:
	vector<Card*> cards;
	void addCard(Card* newCard);
	Card* getLastCard();
	void discardCards(vector<Card*>& deckToDiscard);
	void displayAsciiArt();
};

#endif // !HAND_H

