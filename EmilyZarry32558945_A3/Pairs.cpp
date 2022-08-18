/**************************************************
Project: Pairs Card Game
Author: Emily Samantha Zarry
Purpose: Pairs Application File
**************************************************/

#include "Header.h"

int main()
{
	// Displaying information about the game
	displayText("PairsInfo.txt");

	// Initializing the game settings
	displayGameSettings();

	// Initializing the players
	int numPlayers = 0;
	int targetScore = 0;
	string loserName = "";
	Player* playerPtr = NULL;
	initializePlayers(numPlayers, targetScore, playerPtr);

	// Initializing the cards
	int burnSize = 0;
	Card* cardPtr = NULL;
	vector<Card*> mainDeck;
	vector<Card*> discardPile;
	initializeCards(burnSize, cardPtr, mainDeck);

	// Shuffling the deck
	shuffleDeck(mainDeck);

	// Burning cards before game round starts
	burnCards(mainDeck, discardPile, burnSize);

	// Main Game Loop
	bool gameOn = true;
	while (gameOn) {
		// Start of Game
		// Checking if the deck is empty, if so reshuffle the discard pile and burn cards
		checkForReshuffle(mainDeck, discardPile, burnSize);
		
		// Dealing a card to each player
		for (int i = 0; i < numPlayers; ++i) {
			mainDeck[0]->setStatus("dealt");
			playerPtr[i].hand.addCard(mainDeck[0]);
			mainDeck.erase(mainDeck.begin());

		}

		// Checking if any of the cards dealt to the players are tied
		checkForTie(numPlayers, playerPtr, mainDeck, discardPile);

		bool roundOn = true;
		while (roundOn) {
			// Setting the player with the lowest card to go first
			int lowestPlayer = 0;
			setLowestPlayer(lowestPlayer, numPlayers, playerPtr);

			// Displaying each player�s name, score, and hand
			bool pair = false;
			bool fold = false;
			bool quit = false;

			playPairs(gameOn, roundOn, pair, fold, quit, lowestPlayer, numPlayers, mainDeck, discardPile, burnSize, targetScore, numPlayers, loserName, playerPtr);

			if (!quit && !fold && !pair) {
				playPairs(gameOn, roundOn, pair, fold, quit, 0, lowestPlayer, mainDeck, discardPile, burnSize, targetScore, numPlayers, loserName, playerPtr);
			}
		}
	}

	// End of game
	displayGameOver(playerPtr, numPlayers, loserName);

	delete[] playerPtr;
	delete[] cardPtr;

	waitForPlayer();
	return 0;
}

void displayText(string fileName)
{
	// Clearing the screen
	system("cls");

	// Opening the file and displaying its contents
	ifstream file;
	string line;
	file.open(fileName);
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			cout << line << endl;
		}
		file.close();
	}
	else {
		cout << "Unable to open the file" << endl;
	}

	// Allowing user some time to read
	waitForPlayer();
}

void displayGameSettings()
{
	cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\t\t\t   Game Settings" << endl;
	cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void displayScores(int targetScore, Player players[], int numPlayers)
{
	// Clearing the screen
	system("cls");

	// Title
	cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\t\tPairs :: Target Score ~> " << targetScore << endl;
	cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	
	// Player Info
	// Iterating through each player and displaying their names, scores, and hand
	for (int i = 0; i < numPlayers; ++i) {
		cout << "\t\tName: " << players[i].getName() << "\t\tScore: " << players[i].getScore() << endl;
		cout << "\t\tHand: " << endl;
		players[i].hand.displayAsciiArt();
		cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
}

void displayGameOver(Player players[], int numPlayers, string loserName)
{
	// Game Over Message
	cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\t8^) It's game over, man!" << endl;
	cout << "\t" << loserName << " is buying the drinks!" << endl;

	// Player Stats
	cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "			PLAYER STATS" << endl;
	cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	
	// Iterating through each player and displaying their names, win count, lose count, and scores
	for (int i = 0; i < numPlayers; ++i) {
		cout << "\t\tName: " << players[i].getName() << "\t\t\tWin Count: " << players[i].getWinCount() << endl;
		cout << "\t\tScore: " << players[i].getScore() << "\t\tLose Count: " << players[i].getLoseCount() << endl;
		cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
}

void initializePlayers(int& numPlayers, int& targetScore, Player* &playerPtr)
{
	// Initializing the number of players
	int error = 0;
	do
	{
		cout << "\tEnter the number of players (2-8): ";
		cin >> numPlayers;
		error = 0;
		if (cin.fail() || numPlayers < 2 || numPlayers > 8)
		{
			cout << "\tPlease enter a number between 2-8 ..." << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (error == 1);

	// Setting the target score to 11 if the number of players is 7 or 8
	if (numPlayers == 7 || numPlayers == 8) {
		targetScore = 11;
	}
	else {
		targetScore = 60 / numPlayers + 1;
	}

	// Inintializing the player names
	playerPtr = new Player[numPlayers];
	cin.ignore();
	for (int i = 0; i < numPlayers; ++i) {
		string playerName = askForString("\t\tEnter the player's name: ");
		playerPtr[i] = Player(playerName);

	}
}

void playPairs(bool& gameOn, bool& roundOn, bool& pair, bool& fold, bool& quit, int start, int end, vector<Card*>& mainDeck, vector<Card*>& discardPile, int burnSize, int targetScore, int &numPlayers, string& loserName, Player*& playerPtr)
{
	for (int i = start; i < end; ++i) {
		displayScores(targetScore, playerPtr, numPlayers);

		// Asking to [H]it or [F]old
		// Validating the user's input
		int error = 0;
		string question = "\n\t" + playerPtr[i].getName() + ", will you [H]it or [F]old (Type Q to quit): ";
		char playerInput = ' ';
		do
		{
			playerInput = tolower(askForLetter(question));
			error = 0;
			if (playerInput != 'h' && playerInput != 'f' && playerInput != 'q')
			{
				cout << "\tPlease enter 'H', 'F', or 'Q'..." << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);

		// Processing player input
		if (playerInput == 'h') {
			// Checking if the deck is empty, if so reshuffle the discard pile and burn cards
			checkForReshuffle(mainDeck, discardPile, burnSize);

			// Dealing a card to the player
			mainDeck[0]->setStatus("dealt");

			// Checking whether the dealt card matches any of the cards on the player�s hand
			for (int j = 0; j < playerPtr[i].hand.cards.size(); ++j) {
				if (playerPtr[i].hand.cards[j]->getRank() == mainDeck[0]->getRank()) {
					playerPtr[i].hand.addCard(mainDeck[0]);
					mainDeck.erase(mainDeck.begin());

					// Ending the round
					// End of round feedback
					displayScores(targetScore, playerPtr, numPlayers);
					cout << "\n\t" << playerPtr[i].getName() << " ended this round with a PAIR and scoring " << playerPtr[i].hand.cards[j]->getRank() << " points!" << endl;
					waitForPlayer();

					// Adding points to the player
					playerPtr[i].addScore(playerPtr[i].hand.cards[j]->getRank());

					// Discarding all the players' cards
					for (int i = 0; i < numPlayers; ++i) {
						playerPtr[i].hand.discardCards(discardPile);
					}

					// Checking if a player reaches or exceeds the target score
					if (playerPtr[i].getScore() >= targetScore) {
						gameOn = false;
						loserName = playerPtr[i].getName();
						playerPtr[i].addLose();
					}

					roundOn = false;
					pair = true;
					break;
				}
			}

			if (pair) {
				break;
			}
			else {
				playerPtr[i].hand.addCard(mainDeck[0]);
				mainDeck.erase(mainDeck.begin());
			}
		}
		else if (playerInput == 'f') {
			// Ending the round
			// End of round feedback
			displayScores(targetScore, playerPtr, numPlayers);

			// Finding the lowest card on the table
			int lowestCard = playerPtr[0].hand.cards[0]->getRank();
			for (int j = 0; j < numPlayers; ++j) {
				for (int k = 0; k < playerPtr[j].hand.cards.size(); ++k) {
					if (playerPtr[j].hand.cards[k]->getRank() < lowestCard) {
						lowestCard = playerPtr[j].hand.cards[k]->getRank();
					}
				}
			}
			cout << "\n\t" << playerPtr[i].getName() << " ended this round by FOLDING and scoring " << lowestCard << " points!" << endl;
			waitForPlayer();

			// Adding points to the player
			playerPtr[i].addScore(lowestCard);

			// Discarding all the players' cards
			for (int i = 0; i < numPlayers; ++i) {
				playerPtr[i].hand.discardCards(discardPile);
			}

			// Checking if a player reaches or exceeds the target score
			if (playerPtr[i].getScore() >= targetScore) {
				gameOn = false;
				loserName = playerPtr[i].getName();
				playerPtr[i].addLose();
			}

			roundOn = false;
			fold = true;
			break;
		}
		else if (playerInput == 'q') {
			gameOn = false;
			roundOn = false;
			quit = true;
			break;
		}
	}
}

void shuffleDeck(vector<Card*> &deck)
{
	srand(unsigned(time(NULL)));
	random_shuffle(deck.begin(), deck.end(), myRandom);
}

void burnCards(vector<Card*> &mainDeck, vector<Card*> &discardPile, int &burnSize)
{
	// Moving a number of cards from the top of the main deck to the discard pile
	for (int i = 0; i < burnSize; ++i) {
		mainDeck[0]->setStatus("discarded");
		discardPile.push_back(mainDeck[0]);
		mainDeck.erase(mainDeck.begin());
	}
}

void initializeCards(int& burnSize, Card*& cardPtr, vector<Card*>& mainDeck)
{
	// Asking for player to enter the number of cards to burn on each shuffle
	char playerInput = ' ';
	int error = 0;
	do
	{
		playerInput = tolower(askForLetter("\tEnter the number of cards to burn on each shuffle (4-6) or [R] to randomize: "));
		error = 0;
		if (playerInput != '4' && playerInput != '5' && playerInput != '6' && playerInput != 'r')
		{
			cout << "\tPlease enter 4-6 or R ..." << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (error == 1);

	switch (playerInput) {
	case '4':
		burnSize = 4;
		break;
	case '5':
		burnSize = 5;
		break;
	case '6':
		burnSize = 6;
		break;
	case 'r':
		srand(unsigned(time(NULL)));
		burnSize = rand() % 3 + 4;
	}

	// Initializing the 55 cards
	cardPtr = new Card[55];
	int counter = 0;
	for (int i = 1; i <= 10; ++i) {
		for (int j = 0; j < i; ++j) {
			*(cardPtr + counter) = Card(i);
			(cardPtr + counter)->setStatus("deck");
			counter++;
		}
	}

	// Initializing the main deck
	for (int i = 0; i < 55; ++i) {
		mainDeck.push_back(cardPtr + i);
	}
}

void checkForTie(int& numPlayers, Player*& playerPtr, vector<Card*>& mainDeck, vector<Card*>& discardPile)
{
	bool tie = false;
	do {
		// Creating a sorted vector of the dealt cards
		vector<int> dealtCards;
		for (int i = 0; i < numPlayers; ++i) {
			dealtCards.push_back(playerPtr[i].hand.getLastCard()->getRank());
		}
		sort(dealtCards.begin(), dealtCards.end());

		for (int i = 0; i < dealtCards.size() - 1; ++i) {
			// If any of the cards dealt to the players are tied, discard the card and deal another one
			if (dealtCards[i] == dealtCards[i + 1]) {
				tie = true;
				for (int j = 0; j < numPlayers; ++j) {
					if (dealtCards[i] == playerPtr[j].hand.getLastCard()->getRank()) {
						// If the player deals the same number, discard and deal another card
						while (playerPtr[j].hand.getLastCard()->getRank() == mainDeck[0]->getRank()) {
							mainDeck[0]->setStatus("discarded");
							discardPile.push_back(mainDeck[0]);
							mainDeck.erase(mainDeck.begin());
						}

						// Discard the players' card
						playerPtr[j].hand.discardCards(discardPile);

						// Deal another one
						mainDeck[0]->setStatus("dealt");
						playerPtr[j].hand.addCard(mainDeck[0]);
						mainDeck.erase(mainDeck.begin());
					}
				}
				break;
			}
			else {
				tie = false;
			}
		}
	} while (tie);
}

void checkForReshuffle(vector<Card*>& mainDeck, vector<Card*>& discardPile, int& burnSize)
{
	if (mainDeck.empty()) {
		shuffleDeck(discardPile);
		for (int i = 0; i < discardPile.size(); ++i) {
			discardPile[0]->setStatus("deck");
			mainDeck.push_back(discardPile[0]);
			discardPile.erase(discardPile.begin());
		}
		burnCards(mainDeck, discardPile, burnSize);
	}

}

void setLowestPlayer(int& lowestPlayer, int& numPlayers, Player*& playerPtr)
{
	// Setting the player with the lowest card rank
	int lowestCard = playerPtr[0].hand.getLastCard()->getRank();
	for (int i = 1; i < numPlayers; ++i) {
		if (playerPtr[i].hand.getLastCard()->getRank() < lowestCard) {
			lowestCard = playerPtr[i].hand.getLastCard()->getRank();
			lowestPlayer = i;
		}
	}
}

void waitForPlayer()
{
	cout << "\n\t";
	system("pause");
	system("cls");
}

int askForNumber(string question)
{
	int num = 0;
	while (num == 0) {
		cout << question;
		cin >> num;
	}
	return num;
}

char askForLetter(string question)
{
	char letter = ' ';
	while (letter == ' ') {
		cout << question;
		cin >> letter;
	}
	return letter;
}

string askForString(string question)
{
	string userInput = "";
	while (userInput == "") {
		cout << question;
		getline(cin, userInput);
	}
	return userInput;
}

int myRandom(int i) {
	return rand() % i;
}