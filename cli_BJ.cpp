#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

int money = 200;
int bet = 0;
	vector <int> dealerCards = {};
	vector <int> playerCards = {};


void printLogo();
void startUp();
void showCards();
void game();

int main() {
	random_device rd;
	uniform_int_distribution<int> dist(1, 13);

	printLogo();
	startUp();

	dealerCards.push_back(dist(rd));	//gives dealer 1 card

	playerCards.push_back(dist(rd));
	playerCards.push_back(dist(rd));	//gives player 2 cards

	showCards();

	game();


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

void startUp() {

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
	} while (bet <= 0 || bet > money+bet);
}
//asks the user how much they want to bet and saves and removes it from the player's money

void showCards() {
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

void game() {

	char choice;

	random_device rd;
	uniform_int_distribution<int> dist(1, 13);

	cout << "[H]it, [S]tay, [D]ouble down or [G]ive up (surrender)? ('C' to show cards)";
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
		if (bet*2 <= money){
			bet *= 2; money -= bet/2;
		}
		else {
		cout << "Not enought money to Double down!" << endl;
		game();
		}
		break;
	}
	case 'G': {
		money += bet / 2;
		break;
	}
	case 'C': {
		showCards();
		game();
	}
	default:
		cout << "invalid option! " << endl;	//says the user put in an invalid value	
		game();								//calls the function and makes the player pick again
	}

}