#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <unistd.h>
#include <vector>
#include <windows.h>
#include <conio.h>

using namespace std;

void gotoxy(short x, short y) { //copas stackoverflow wkwkwk
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };

    SetConsoleCursorPosition(hStdout, position);
}

struct node{
	string flight;
	string remarks;
	string country;
	string time;
	
};

node arr[24];

string Remarks[] = {
	"On Schedule","Landing","Refuel","Boarding","Final Check","Delayed","Departed"
};


string remarks(int index) { //Generate Remarks (Sequencial)

	string remarks;

	remarks = Remarks[index];
	
	return remarks;
}

string flight() { //Generate Random Flight Number
	
	char letter;
	int random;
	string number;
	
	string flightcode;
	
	for (int i=0; i<2; i++) {
		random = rand() % 26;
		letter = 'A' + random;
		flightcode += letter;
	}
	
	flightcode += " ";
	
	for (int i=0; i<4; i++) {
		random = rand() % 10;
		number = to_string(random);
		flightcode += number;
	}
		
	return flightcode;
}

string country() { //Generate Random Country
	
	string arr[] = {
	"London","Alaska","Boston","Madrid","Queens",
	"Athens","Berlin","Moscow","Beirut","Bogota",
	"Havana","Dublin","Manila","Monaco","Prague",
	"Vienna","Warsaw","Taipei","Lisbon"
	};
	
	string country;
	int random;
	
	random = rand() % (sizeof(arr)/sizeof(*arr));
	country = arr[random];
	return country;
}

string time() { //Generate Random Time
	
	string clock;
	
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	
	int hour = aTime->tm_hour;
	int min = aTime->tm_sec;
	clock += to_string(hour);
	clock += ":";
	clock += to_string(min);
	
	return clock;
}


void checkData(){
	
	
	for (int i=0; i<(sizeof(arr)/sizeof(*arr)); i++){
		if(arr[i].remarks == "Departed"){
			node obj;
			
			obj.country = "";
			obj.flight = "";
			obj.time = "";
			obj.remarks = "";
			
			arr[i] = obj;
		}
		else if(arr[i].remarks == "") {
			node obj;
			
			obj.country = country();
			obj.flight = flight();
			obj.time = time();
			obj.remarks = remarks(0);
			
			arr[i] = obj;
		}
		
	}
}
	
void declaredata(){
	
	for (int i=0; i<(sizeof(arr)/sizeof(*arr)); i++){
		
		node obj;
		
		obj.flight=flight();
		obj.time=time();
		obj.country=country();
		obj.remarks=remarks(0);
		
		arr[i] = obj;
	}
}

void printdata(){
	
	for (int i=0;i<(sizeof(arr)/sizeof(*arr));i++){
			cout 
			<<"||"<< setw(9)<< arr[i].flight << setw(9)
			<<"||"<< setw(9) << arr[i].country << setw(9)
			<<"||"<< setw(9) << arr[i].time << setw(9)
			<<"||"<< setw(15)<< arr[i].remarks<<setw(9)<<"||" << endl;

	}
	sleep(1);
	gotoxy(0,0);
}


void update() {
	int random;
	int x;
	int r;
	
	r = rand() % 6 + 1;
	
	for (int i=0; i<r; i++) { // Calculate how many Remarks are updated (randomly)
		random = rand() % (sizeof(arr)/sizeof(*arr));
	
		if (arr[random].remarks != "") {
			if (arr[random].remarks == Remarks[0] ) x = 1;
			else if (arr[random].remarks == Remarks[1] ) x = 2;
			else if (arr[random].remarks == Remarks[2] ) x = 3;
			else if (arr[random].remarks == Remarks[3] ) x = 4;
			else if (arr[random].remarks == Remarks[4] ) x = 5;
			else if (arr[random].remarks == Remarks[5] ) x = 6;
		
			arr[random].remarks = remarks(x);
		}	
	}

} 

int main(){
	srand(time(NULL));
	
	declaredata();
	
	while(true){
		printdata(); //cout << "print ";
		checkData(); //cout << "check ";
		update(); //cout << "update "<< endl;
	}
		
	cin.ignore();
	return 0;
}



