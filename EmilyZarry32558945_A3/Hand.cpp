#include "Hand.h"

void Hand::addCard(Card* newCard)
{
	cards.push_back(newCard);
}

Card* Hand::getLastCard()
{
	return cards.back();
}

void Hand::discardCards(vector<Card*>& deckToDiscard)
{
	for (int i = 0; i < cards.size(); ++i) {
		cards[i]->setStatus("discarded");
		deckToDiscard.push_back(cards[i]);
	}
	while (!cards.empty()) {
		cards.erase(cards.begin());
	}
}

void Hand::displayAsciiArt()
{
	stringstream sAsciiArt;
	string line1 = "";
	string line2 = "";
	string line3 = "";
	string line4 = "";
	string line5 = "";
	string line6 = "";

	line1 += "\t\t";
	line2 += "\t\t";
	line3 += "\t\t";
	line4 += "\t\t";
	line5 += "\t\t";
	line6 += "\t\t";

	for (int i = 0; i < cards.size(); ++i) {
		line1 += " .------. ";
		line2 += " |";
		line2 += to_string(cards[i]->getRank());
		if (cards[i]->getRank() != 10) {
			line2 += " ";
		}
		line2 += "    | ";
		line3 += " |      | ";
		line4 += " |      | ";
		line5 += " |    ";
		if (cards[i]->getRank() != 10) {
			line5 += " ";
		}
		line5 += to_string(cards[i]->getRank());
		line5 += "| ";
		line6 += " '------' ";
	}
	line1 += "\n";
	line2 += "\n";
	line3 += "\n";
	line4 += "\n";
	line5 += "\n";
	line6 += "\n";

	sAsciiArt << line1 << line2 << line3 << line4 << line5 << line6;
	cout << sAsciiArt.str();
}