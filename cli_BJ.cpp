#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

class player {
public:
	int money = 200;
private:

};

player player1;

void printLogo();
void startUp();

int main() {

	srand(time(NULL));

	printLogo();
	startUp();




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


	cout << "You currently have " << player1.money <<" chips. Good Luck!" << endl;
}
