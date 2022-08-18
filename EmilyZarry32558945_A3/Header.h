/**************************************************
Project: Pairs Card Game
Author: Emily Samantha Zarry
Purpose: Pairs Header File
**************************************************/

#ifndef HEADER_H
#define HEADER_H

#include "Player.h"
#include "Card.h"
#include <fstream>
#include <algorithm>
#include <ctime>

void displayText(string fileName);
void displayGameSettings();
void displayScores(int targetScore, Player players[], int numPlayers);
void displayGameOver(Player players[], int numPlayers, string loserName);

void initializePlayers(int& numPlayers, int& targetScore, Player* &playerPtr);
void shuffleDeck(vector<Card*>& deck);
void burnCards(vector<Card*> &mainDeck, vector<Card*> &discardPile, int &burnSize);
void initializeCards(int &burnSize, Card* &cardPtr, vector<Card*> &mainDeck);
void checkForTie(int &numPlayers, Player*& playerPtr, vector<Card*> &mainDeck, vector<Card*> &discardPile);
void checkForReshuffle(vector<Card*>& mainDeck, vector<Card*>& discardPile, int& burnSize);
void setLowestPlayer(int &lowestPlayer, int& numPlayers, Player*& playerPtr);
void playPairs(bool& gameOn, bool& roundOn, bool& pair, bool& fold, bool& quit, int start, int end, vector<Card*>& mainDeck, vector<Card*>& discardPile, int burnSize, int targetScore, int &numPlayers, string& loserName, Player*& playerPtr);

void waitForPlayer();

int askForNumber(string question);
char askForLetter(string question);
string askForString(string question);

int myRandom(int i);
#endif // !HEADER_H