#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <unistd.h>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <queue>

using namespace std;

void clearQueue(queue<int>& dep, queue<int>& land){
	while(!land.empty()){
		land.pop();
	}
	while(!dep.empty()){
		dep.pop();
	}
}

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

node arr[15];
queue<int> dep;
queue<int> land;
queue<int> empty;

string Remarks[] = {
	"Landing","Refuel","On Schedule","Delayed","Boarding","Final Check","Departed"
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
	int min = (aTime->tm_min)+(rand()%4);
	clock += to_string(hour);
	clock += ":";

	if (min%10==min){
		clock += to_string(0);
		clock += to_string(min);
	}else {
		clock += to_string(min);
	}

	return clock;
}

void announcement(queue<int> dep, queue<int> lan, node arr[]){

	int x;
	while(!dep.empty()){
		x = dep.front();
		dep.pop();
		cout<<arr[x].time<<setw(9)<<" flight No."<<arr[x].flight<<" has departed"<<endl;
	}
	while(!lan.empty()){
		x=lan.front();
		lan.pop();
		cout<<arr[x].time<<setw(9)<<" flight No."<<arr[x].flight<<" has landed"<<endl;
	}

}

void newData(queue<int> dep){
	int y;
	while(!dep.empty()){
		y=dep.front();
		dep.pop();

		node obj;
		obj.country=country();
		obj.flight=flight();
		obj.time=time();
		obj.remarks=remarks(0);

		arr[y].country=obj.country;
		arr[y].flight=obj.flight;
		arr[y].remarks=obj.remarks;
		arr[y].time=obj.time;

	}
}

void checkData(){

	for (int i=0; i</*(sizeof(arr)/sizeof(*arr))*/15; i++){
		if(arr[i].remarks == "Departed"){
			dep.push(i);

		}else if(arr[i].remarks=="Landing"){
			land.push(i);
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
}

string getHour(string time){ //Get the hour of the obj
	string seperator = ":";
	int pos = time.find(seperator);
  string hour = time.substr(0, pos);

  return hour;
}

string getMin(string time){ //Get the min of the obj
	string seperator = ":";
	int pos = time.find(seperator);
  string token = time.substr(0, pos);

  string min = time.erase(0, pos + seperator.length());
  return min;
}

void update() {
	int random;
	int random2;
	int x;
	int r;

	r = rand() % 6 + 1;

	for (int i=0; i<r; i++) { // Calculate how many Remarks are updated (randomly)
		random = rand() % (sizeof(arr)/sizeof(*arr));

		if (arr[random].remarks != "") {
			if (arr[random].remarks == Remarks[0] ) x = 1;
			else if (arr[random].remarks == Remarks[1] ) x = 2;
			else if (arr[random].remarks == Remarks[2] ){
				random2 = rand();
				if (random2%2 == 0){
					x = 3;

					// Add 1 min due to delay;
					string newtime = getHour(arr[random].time) + ":";
					string min = getMin(arr[random].time);
					int newmin = stoi(min)+1;

					if (newmin%10==newmin){
						newtime += "0";
						newtime += to_string(newmin);
					}else {
						newtime += to_string(newmin);
					}

					arr[random].time = newtime;
				}else {
					x = 4;
				}
			}
			else if (arr[random].remarks == Remarks[3] ) x = 4;
			else if (arr[random].remarks == Remarks[4] ) x = 5;
			else if (arr[random].remarks == Remarks[5] ) x = 6;
			arr[random].remarks = remarks(x);
		}
	}

	for (int k = 0; k<empty.size();k++){
		int x = empty.front();

		arr[x].country=country();
		arr[x].flight=flight();
		arr[x].time=time();
		arr[x].remarks=remarks(0);

		empty.pop();
	}

	for (int j = 0; j<dep.size();j++){
		int x = dep.front();

		arr[x].remarks = "";
		arr[x].flight = "";
		arr[x].time = "";
		arr[x].country = "";

		dep.pop();
		empty.push(x);
	}

	clearQueue(dep, land);
}

int main(){
	srand(time(NULL));

	declaredata();

	while(true){
		printdata(); //cout << //"print ";
		checkData(); //cout << //"check ";
		sleep(1);
		update(); //cout << "update "<< endl;

		gotoxy(0,0);
	//	system("cls");
	}

	cin.ignore();
	return 0;
}
