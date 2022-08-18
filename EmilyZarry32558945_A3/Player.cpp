/**************************************************
Project: Pairs Card Game
Author: Emily Samantha Zarry
Purpose: Player Class File
**************************************************/

#include "Player.h"

Player::Player()
{
	name = "";
	score = 0;
	winCount = 0;
	loseCount = 0;
}

Player::Player(string aName)
{
	name = aName;
	score = 0;
	winCount = 0;
	loseCount = 0;
}

Player::~Player(){}

void Player::setName(string aName)
{
	name = aName;
}

string Player::getName()
{
	return name;
}

void Player::resetScore()
{
	score = 0;
}

void Player::addScore(int scoreToAdd)
{
	score += scoreToAdd;
}

int Player::getScore()
{
	return score;
}

void Player::addWin()
{
	winCount++;
}

void Player::resetWin()
{
	winCount = 0;
}

int Player::getWinCount()
{
	return winCount;
}

void Player::addLose()
{
	loseCount++;
}

void Player::resetLose()
{
	loseCount = 0;
}

int Player::getLoseCount()
{
	return loseCount;
}