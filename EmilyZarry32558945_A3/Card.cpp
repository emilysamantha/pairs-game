/**************************************************
Project: Pairs Card Game
Author: Emily Samantha Zarry
Purpose: Card Class File
**************************************************/
#include "Card.h"

Card::Card()
{
	rank = 0;
	status = "";
}

Card::Card(int aRank)
{
	rank = aRank;
}

Card::~Card(){}

void Card::setStatus(string newStatus)
{
	status = newStatus;
}

string Card::getStatus()
{
	return status;
}

int Card::getRank()
{
	return rank;
}