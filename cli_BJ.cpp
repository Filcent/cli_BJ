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

int* ptPTR = &playerTotal;

int dealerTotal = 0;

int* dtPTR = &dealerTotal;
//make all of this shit into a class or two or something

void printLogo();
void startUp();
void betting();
void showCards();
void game();
void cardTranslator(vector<int>& whoseCards, int& whoseTotal);
//void dealToDealer(){}  <-- this should happen when player cards value <21 and said "Stay"

random_device rd;
uniform_int_distribution<int> dist(1, 13);

int main() {

	printLogo();
	startUp();

	dealerCards.push_back(dist(rd));	//gives dealer 1 card
	cardTranslator(dealerCards, dealerTotal);

	playerCards.push_back(dist(rd));

	playerCards.push_back(dist(rd));	
	cardTranslator(playerCards, playerTotal); //gives player 2 cards

	showCards();

	//	dealerCards.push_back(dist(rd));	<-- this has to be hidden somehow
	
	//makes it so A,J,Q,K have their true value... perhaps put this into a function (for the player too)? 

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

	map<int, char> cards;

	cards[1] = 'A';
	for (int i = 2; i <= 10; i++) {
		cards[i] = (char)i+48;		//adds 48 to the int value, turning it into its char equivalent (ASCII table) 
	}
	cards[11] = 'J';		
	cards[12] = 'Q';		
	cards[13] = 'K';	//translates the values into chars to be displayed
	
	cout << "Dealer card(s): ";
	for (int i = 0; i < size(dealerCards); i++ ) {

		cout << cards[dealerCards[i]] << ' ';
	
	}

	cout << endl;

	cout << "Player cards: ";
	for (int i = 0; i < size(playerCards); i++) {
		cout << cards[playerCards[i]] << ' ';
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
		cardTranslator(playerCards, playerTotal);	//this works!? 

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

void cardTranslator(vector<int>& whoseCards, int& whoseTotal) {
	
	whoseTotal = 0;
	
	for (int i = 0; i < size(whoseCards); i++) {

		switch (whoseCards[i])
		{
		case 1: {

			if (whoseTotal + 11 <= 21) {

				whoseTotal += 11;
			}
			else {
				whoseTotal += 1;
			}
			break;
		}

		case 11:
		case 12:
		case 13: {
			whoseTotal += 10;
			break;
		}

		default: {
			whoseTotal += whoseCards[i];
			break;
		}
		}

	}
}

//this also updates whoseTotal 