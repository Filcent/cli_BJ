#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>
using namespace std;

int money = 200;
int bet = 0;
vector <int> dealerCards = {};
vector <int> playerCards = {};
int playerTotal = 0;
int dealerTotal = 0;
//make all of this shit into a class or two or something

void printLogo();
void startUp();
void betting();
void showCards();
void game();
//void dealToDealer(){}  <-- this should happen when player cards value <21 and said "Stay"

random_device rd;
uniform_int_distribution<int> dist(1, 13);

int main() {

	printLogo();
	startUp();

	dealerCards.push_back(dist(rd));	//gives dealer 1 card

	playerCards.push_back(dist(rd));
	playerCards.push_back(dist(rd));	//gives player 2 cards

	showCards();

	dealerCards.push_back(dist(rd));	//gives the dealer the "hidden" card
	
	for (int i : dealerCards) {
		dealerTotal += i;
	}
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

	betting();
}
//asks the user how much they want to bet 

void betting() {
		cin >> bet;
		if (bet <= 0) {
			cout << "You need to bet a valid ammount! \n";
			betting();
		}
		else if (bet > money) {
			cout << "You can't bet more money than what you have! \n";
			betting();
		}
		else
		{
			money -= bet;
		}
	}
//saves and removes the bet from the player's money

void showCards() {

	/*
	map<int, char> cards;
	cards[1] = 'A';
	for (int i = 2; i <= 10; i++) {
		cards[i] = (char)i;		//does not work
	}
	cards[11] = 'J';		//does not work
	cards[12] = 'Q';		//does not work
	cards[13] = 'K';		//does not work
	*/
	
	cout << "Dealer card(s): ";
	for (int i = 0; i < size(dealerCards); i++ ) {

		cout << cards[dealerCards[i]] << ' ';
	
	}

	cout << endl;

	cout << "Player cards: ";
	for (int card : playerCards) {
		cout << card << ' ';
	}

	cout << endl;
}
//shows all of the dealer AND the player's cards

void game() {

	char choice;


	cout << "[H]it, [S]tay, [D]ouble down or [G]ive up (surrender)? ('C' to show cards): ";
	cin >> choice;

	switch (choice)
	{
	case 'H': case 'h': {
		playerCards.push_back(dist(rd));
		// check to see if all the cards combined are >21, if they are break and auto-loose, else continue (call the "game()" function)
		playerTotal = 0;
		for (int i : playerCards) {
			playerTotal += i;
		}
		if (playerTotal > 21) {
			cout << "Player Bust!" << endl;
			break;
		}
	}
	case 'S': case 's': {
		break;		//breaks the switch case, and makes the dealer get cards
	}
	case 'D': case 'd': {
		if (bet*2 <= money){
			bet *= 2; money -= bet/2;
		}
		else {
		cout << "Not enough money to Double down!" << endl;
		game();
		}
		break;
	}
	case 'G': case 'g': {
		money += bet / 2;
		break;
	}
	case 'C': case 'c': {
		showCards();
		game();
	}
	default:
		cout << "invalid option! " << endl;	//says the user put in an invalid value	
		game();								//calls the function and makes the player pick again
	}

}

