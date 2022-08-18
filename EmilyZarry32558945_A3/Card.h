#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::getline;
using std::ifstream;
using std::endl;
using std::stringstream;
using std::to_string;

class Card {
private:
	int rank;
	string status;
	string ascii;

public:
	Card();
	Card(int aRank);
	~Card();

	void setStatus(string newStatus);
	string getStatus();
	int getRank();
};

#endif // !CARD_H