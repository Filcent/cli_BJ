#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

void printLogo();
void startUp(int& money, int& bet);
void showCards(vector<int>& dealerCards, vector<int>& playerCards);


int main() {

	int money = 200;
	int bet = 0;
	char choice;


	random_device rd;
	uniform_int_distribution<int> dist(1, 13);

	vector <int> dealerCards = {};
	vector <int> playerCards = {};

	printLogo();
	startUp(money, bet);

	dealerCards.push_back(dist(rd));	//gives dealer 1 card

	playerCards.push_back(dist(rd));
	playerCards.push_back(dist(rd));	//gives player 2 cards

	showCards(dealerCards, playerCards);


	//make a function void game() that maybe can be called inside itself

	cout << "[H]it, [S]tay, [D]ouble down or [G]ive up (surrender)?";
	cin >> choice;

	switch (choice)
	{
	case 'H': {
		playerCards.push_back(dist(rd));
		// check to see if all the cards combined are >21, if they are break and auto-loose, else continue (call the "game()" function)
	}
	case 'S': {
		break;		//breaks the switch case, and makes 
	}
	case 'D': {
		//if (bet*2 >=0) {bet *= 2; money -= bet;}
		//else {cout << "Not enought money to Double down!" << endl 
		//call the "game()" function so it restarts
	}
	case 'G': {
		money += bet / 2;
		break;
	}
	default:
		cout << "invalid option! " << endl;	//says the user put in an invalid value	
											//call the "game()" function so it restarts		
	}


//TODO: make the card dealing repetable (duh)
							
//TODO: add a something to "translate"  1,11,12 and 13 to A,J,Q and K
	
	system("pause");
	return 0;
}

void printLogo()
{
	ifstream in("logo.txt");			//takes logo.txt ads input
	string lString;						//defines the first line of the file
	while (getline(in, lString))		//while it is reading something...
	{
		cout << lString << endl;		//print that thing
	}
	in.close();
}
//prints logo

void startUp(int& money, int& bet) {

	cout << "You currently have " << money << " chips." << endl;
	cout << "how much do you want to bet?: ";

	do {
		cin >> bet;
		if (bet <= 0) {
			cout << "You need to bet a valid ammount! \n";
		}
		else if (bet > money) {
			cout << "You can't bet more money than what you have! \n";
		}
		else
		{
			money -= bet;
		}
	} while (bet <= 0 || bet > money);
}
//asks the user how much they want to bet and saves and removes it from the player's money

void showCards(vector<int>& dealerCards, vector<int>& playerCards) {
	cout << "Dealer card(s): ";
	for (int card : dealerCards) {
		cout << card << ' ';
	}

	cout << endl;

	cout << "Player cards: ";
	for (int card : playerCards) {
		cout << card << ' ';
	}

	cout << endl;
}
//shows all of the dealer and the player's cards