#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include "Flight.cpp"

using namespace std;

int menu = 0;
bool run = true;

Flight flight;

void gotoxy(short x, short y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };

    SetConsoleCursorPosition(hStdout, position);
}

void input() {

	if(_kbhit()) {
		switch(_getch()) {
			case '1' :
				menu = 0;
				break;
			case '2' :
				menu = 1;
				break;
			case '3' :
				menu = 2;
				break;
			case 'x' :
				system("cls");
				exit(0);
				break;
		}
	}
}

void menu1() {
	flight.printData(); //cout << //"print ";

	cout<<"Press 2 to search for flight..."<<endl;
	cout<<"Press 3 to see the announcement..."<<endl;

	sleep(2);

	gotoxy(0,0);

}

void menu2() {
	string flightnum;

	system("cls");
	cout<<"Flight Number : ";
	getline (std::cin,flightnum);
	flight.checkNum(flightnum);


	cout<<"press 1 to exit search"<<endl;
	sleep(3);
	system("cls");

}

void menu3() {
	system("cls");
	flight.announcement();
	sleep(3);
	system("cls");

}

int main() {
	srand(time(NULL));

	flight.declareData();

	while (run) {
		input();

		if(menu == 0) {
			menu1();
		} else if (menu == 1) {
			menu2();
		} else if(menu == 2) {
			menu3();
		}

		// keeping the table updated in the background

		flight.clearQueue();
		flight.checkData(); //cout << //"check ";
		flight.update(); //cout << "update "<< endl;

	}

	cin.ignore();
	return 0;
}
