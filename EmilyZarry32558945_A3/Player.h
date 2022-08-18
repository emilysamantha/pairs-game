/**************************************************
Project: Pairs Card Game
Author: Emily Samantha Zarry
Purpose: Player Class Header
**************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Hand.h"

class Player {
private:
	string name;
	int score;
	int winCount;
	int loseCount;
	
public:
	Player();
	Player(string aName);
	~Player();

	Hand hand;

	void setName(string aName);
	string getName();

	void resetScore();
	void addScore(int scoreToAdd);
	int getScore();

	void addWin();
	void resetWin();
	int getWinCount();

	void addLose();
	void resetLose();
	int getLoseCount();
};

#endif // !PLAYER_H