#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

void printLogo();
void startUp(int& money, int& bet);



int main() {

	int money = 200;
	int bet = 0;

	random_device rd;
	uniform_int_distribution<int> dist(1, 13);
	vector <int> dealerCards = {};
	vector <int> playerCards = {};

	printLogo();
	startUp(money, bet);

	dealerCards.push_back(dist(rd));	//TODO: use randomly generated value from 1 (ace) to 13 (king) to assign cards 
	for (int card : dealerCards) {
		cout << card << ' ';
	}
//	playerCards.push_back(1);	//TODO: make the card dealing repetable (duh)
							
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

