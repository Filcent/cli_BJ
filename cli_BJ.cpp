#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <windows.h>
using namespace std;

int money = 200;
int bet = 0;
vector <int> dealerCards = {};
vector <int> playerCards = {};
int playerTotal = 0;
int dealerTotal = 0;
int* a = &bet;
bool dealerTurn = 0;
//make all of this shit into a class or two or something

void printLogo();
void startUp();
void betting();
void showCards();
void game();
void cardTranslator(vector<int> whoseCards, int& whoseTotal);
void endGame();
//void dealToDealer(){}  <-- this should happen when player cards value <=21 and said "Stay"

random_device rd;
uniform_int_distribution<int> dist(1, 13);

int main() {

	dealerTurn = 0;
	dealerCards.clear();
	playerCards.clear();
	playerTotal = 0;
	dealerTotal = 0;
	//initializes everything back to 0

	system("cls");
	printLogo();
	startUp();

	dealerCards.push_back(dist(rd));
	dealerCards.push_back(dist(rd));		//gives dealer 2 cards
	cardTranslator(dealerCards, dealerTotal);

	playerCards.push_back(dist(rd));
	playerCards.push_back(dist(rd));
	cardTranslator(playerCards, playerTotal); //gives player 2 cards

	game();

	return 1;	//if this happens, something REALLY bad happened
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

	char cashOut;

	if (money == 0) {
		cout << "You currently have... ";
		Sleep(1500);
		cout << "oh... \n";
		Sleep(1500);
		cout << "We're sorry, but we don't offer chip exchange at the table. you'll have to go back to the cashier. (Game over) \n";
		system("pause");
		exit(0);
	}

	cout << "You currently have " << money << " chips. (press 'C' to cash out, 'P' to play)" << endl;
	cin >> cashOut;
	if (cashOut == 'c' || cashOut == 'C') {
		string name;

		cout << "You think about walking home with your money... besides, what even is your name? (C to go back to the blackjack table): \n";
		cin >> name;
		if (name == "C" || name == "c") {
			cout << "now that you think about it, playing a few more hands doesn't sound so bad afterall. What's the worse that can happen, right?";
		}
		else {
			ofstream hiScore;
			hiScore.open("Scoreboard.txt", fstream::app);
			hiScore << name << " : " << money << "\n";
			hiScore.close();
			if (money > 200) {
				cout << "*You go home with your money, satisfied you won something* \n";
			}
			else if (money > 1000) {
				cout << "*you go home feeling like a little kid. That's a lot of money right there!* \n";
			}
			if (money < 200) {
				cout << "*You go home with your wallet feeling a little lighter than before. You wonder how you're going to make that money back...* \n";
			}
			if (money == 200) {
				cout << "*You go home on a net zero. Hey, winning nothing that's better than loosing something!* \n";
			}
			exit(0);
		}
	}
	else if(cashOut == 'p' || cashOut == 'P'){
	betting();
	}
	else {
		cout << "Pick a valid decision \n";
		startUp();
	}
}

void betting() {
	bet = 0;
	cout << "how much do you want to bet?: ";

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

void showCards() {

	map<int, string> cards;

	cards[1] = 'A';
	for (int i = 2; i <= 10; i++) {
		cards[i] = (char)i + 48;		//adds 48 to the int value, turning it into its char equivalent (ASCII table) 
	}
	cards[10] = "10";
	cards[11] = 'J';
	cards[12] = 'Q';
	cards[13] = 'K';	//translates the values into chars to be displayed


	cout << "Dealer card(s): ";
	if (dealerTurn == 1) {		//display all of the dealer's cards only if its their turn
		for (int i = 0; i < size(dealerCards); i++) {

			cout << cards[dealerCards[i]] << ' ';

		}
	}
	else {		//display only the non-hidden dealer card
		cout << cards[dealerCards[0]];
	}
	cout << endl;

	cout << "Player cards: ";
	for (int i = 0; i < size(playerCards); i++) {
		cout << cards[playerCards[i]] << ' ';
	}

	cout << endl;
}
//shows the cards correctly according to whose turn it is

void game() {

	char choice;
	showCards();

	if (playerTotal == 21) {
		if (dealerTotal == 21) {
			endGame();			//if the blackjack is a push it gets handled by the endGame function
		}
		else {
			cout << "Player blackjack! \n";
			money += (bet / 2) * 3;		//if not, the player gets payed 3:2
			system("pause");
			main();
		}
	} //handles player blackjack

	if (dealerTotal == 21) {
		cout << "Dealer has a natural... \n";
		system("pause");
		main();
	}
	// the push should be handled by the if above. ATM, there is no insurance

	cout << "[H]it, [S]tay, [D]ouble down or [G]ive up (surrender)? ('C' to show cards again): ";
	cin >> choice;

	switch (choice)
	{
	case 'H': case 'h': {
		playerCards.push_back(dist(rd));
		cardTranslator(playerCards, playerTotal);	//this works. 

		if (playerTotal > 21) {
			showCards();
			cout << "Player Bust!" << endl;
			system("pause");
			main();
		}
		game();
		// check to see if all the cards combined are >21, if they are break and auto-loose, else continue (call the "game()" function)
	}
	case 'S': case 's': {
		endGame(); //goes to the fuction that gives the dealer their cards
	}
	case 'D': case 'd': {
		if (bet <= money) {
			bet *= 2;		//if the player has enough cash double the bet
			money -= bet / 2; //and take away the money
			playerCards.push_back(dist(rd));
			cardTranslator(playerCards, playerTotal);	//give the player the cards
			showCards();
			Sleep(1500);
			if (playerTotal > 21) {		//if they bust that's it
				cout << "Player Bust!" << endl;
				system("pause");			//let them look at what they have done
				main();
			}
			else {
				endGame();	//if they don't they have to go against the dealer
			}
		}
		else {
			cout << "Not enough money to Double down! (your current bet is " << bet << " and you only have " << money << " chips)" << endl;	//if they're dumb then remind them
			game();
		}
		break;
	}
	case 'G': case 'g': {	//Surrender
		money += bet / 2;	//gives the user half of their bet
		cout << "You have been given back half of your bet (" << bet / 2 << ")";
		Sleep(3000);
		main();				//restarts the program
	}
	case 'C': case 'c': {	//to see the cards	
		game();				//Sends you back at the beginning, where there is showCards()... oh the illusion...
	}
	default:
		cout << "invalid option! " << endl;	//just in case the user is an idiot who tries to cheat (or missclicks)
		game();								//calls the function and makes the player pick again
	}

}

void endGame() {
	dealerTurn = 1;
	showCards();
	while (dealerTotal < 17) {
		dealerCards.push_back(dist(rd));
		Sleep(1500);
		cardTranslator(dealerCards, dealerTotal);
		showCards();
	}
	if (playerTotal == dealerTotal) {
		cout << "It's a push! \n";
		money += bet;
	}
	else if (dealerTotal > 21 || playerTotal > dealerTotal) {
		Sleep(1500);
		cout << "Player wins! \n";
		money += bet * 2;
	}
	else {
		Sleep(1500);
		cout << "Dealer wins..." << endl;
	}

	system("pause");

	main();
}

void cardTranslator(vector<int> whoseCards, int& whoseTotal) {

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
