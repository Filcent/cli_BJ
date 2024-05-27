#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

void printLogo();
void startUp(int& money, int& bet);

int main() {

	int money = 200;
	int bet = 0;

	printLogo();
	startUp(money, bet);

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
