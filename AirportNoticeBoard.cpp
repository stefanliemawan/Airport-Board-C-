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

//menu added
//delay announcement added
//announcement added

// For printing without cls
void gotoxy(short x, short y) { //copas stackoverflow wkwkwk
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };

    SetConsoleCursorPosition(hStdout, position);
}

// Data structure of obj
struct node{
	string flight;
	string remarks;
	string country;
	string time;
};

// Datas
node arr[15];
queue<int> dep;
queue<int> land;
queue<int> empty;
queue<int> ontime;
queue<int> delay;
int menu = 0;
bool run = true;

string Remarks[] = {
	"Landing","Refuel","On Schedule","Delayed","Boarding","Final Check","Departed"
};

// Produce random remark
string remarks(int index) {

	string remarks;

	remarks = Remarks[index];

	return remarks;
}

// Produce random flight number
string flight() {

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

// Produce random destination/country
string country() {

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

// Produce current time + random int (between 0 & 3)
string time() {

	string clock;

	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);

	int min;
	int hour = aTime->tm_hour;

	// Check second to avoid getting current minute after current minute increase due to sleep
	if (aTime->tm_sec >= 50){
		min = (aTime->tm_min)+(rand()%3)+1;
	}else {
		min = (aTime->tm_min)+(rand()%4);
	}

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

// Return the current time for checkData()
string currentTime(){

	string clock;

	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);

	int hour = aTime->tm_hour;
	int min = aTime->tm_min;
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

// Announce the depart plane
void announcement(queue<int> dep, queue<int> lan,queue<int> delay, node arr[]){
	cout<<"============"<<endl;
	cout<<"ANNOUNCEMENT"<<endl;
	cout<<"============"<<endl;
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
	while(!delay.empty()){
		x = delay.front();
		delay.pop();
		cout<<arr[x].time<<setw(9)<<" flight No."<<arr[x].flight<<" has been delayed"<<endl;
	}

}

// Ini ngapain cuk
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

// Fill up the dep, land and ontime queue
void checkData(){

	for (int i=0; i< (sizeof(arr)/sizeof(*arr)); i++){
		if(arr[i].remarks == "Departed"){
			dep.push(i);

		}else if(arr[i].remarks=="Landing"){
			land.push(i);
			
		}else if(arr[i].remarks == "Delayed"){
			delay.push(i);
		}
	}

	for (int i = 0; i < (sizeof(arr)/sizeof(*arr)); i++){
		if (arr[i].time == currentTime()){
			ontime.push(i);
		}else {
			continue;
		}
	}
	
}

// Clear up the dep, land and ontime queues
void clearQueue(){
	while(!land.empty()){
		land.pop();
	}
	while(!dep.empty()){
		dep.pop();
	}
	while(!ontime.empty()){
		ontime.pop();
	}while(!delay.empty()){
		delay.pop();
	}
}

// Fill array with new objs
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

// Print all data in form of Board
void printdata(){
	
	cout<<"================================================================================"<<endl;
	cout<<"||"<<setw(12)<<"Flight No."<<setw(6)<<"||"<<setw(10);
		cout<<"Country"<<setw(8)<<"||"<<setw(8);
		cout<<"Time"<<setw(10)<<"||"<<setw(15);
		cout<<"Remarks"<<setw(9)<<"||";
		cout<<endl;	
	cout<<"================================================================================"<<endl;


	for (int i=0;i<(sizeof(arr)/sizeof(*arr));i++){
			cout
			<<"||"<< setw(9)<< arr[i].flight << setw(9)
			<<"||"<< setw(9) << arr[i].country << setw(9)
			<<"||"<< setw(9) << arr[i].time << setw(9)
			<<"||"<< setw(15)<< arr[i].remarks<<setw(9)<<"||" << endl;

	}
	cout<<"================================================================================"<<endl;



}

//Get the hour of the obj
string getHour(string time){
	string seperator = ":";
	int pos = time.find(seperator);
  string hour = time.substr(0, pos);

  return hour;
}

//Get the min of the obj
string getMin(string time){
	string seperator = ":";
	int pos = time.find(seperator);
  string token = time.substr(0, pos);

  string min = time.erase(0, pos + seperator.length());
  return min;
}

// Update the board >> logics applied here
void update() {

	int random;
	int x;
	int r;

	r = rand() % 6 + 1;

	// Calculate how many Remarks are updated (randomly)
	for (int i=0; i<r; i++) {
		random = rand() % (sizeof(arr)/sizeof(*arr));

		if (arr[random].remarks != "") {
			if (arr[random].remarks == Remarks[0] ) x = 1;
			else if (arr[random].remarks == Remarks[1] ) x = 2;
			else if (arr[random].remarks == Remarks[3] ) x = 3;
			else {
				// Make remark the same or unchange
				for (int a = 0; a < 7; a++){
					if (arr[random].remarks == Remarks[a] ){
						x = a;
					}else {
						continue;
					}
				}
			}
			arr[random].remarks = remarks(x);
		}
	}

	// Avoid error if notime queue is empty
	if (ontime.size() > 0){
		r = rand() % ontime.size()+1;

		// Increase speed of departing the on time plane to avoid being passed by current time
		if (ontime.size() >= 2){
			r+=1;
		}

		for (int a = 0; a < r; a++){
			int index = ontime.front();

			if (arr[index].remarks == Remarks[0] ){
				x = 1;
				ontime.pop();
				ontime.push(index);
			}
			else if (arr[index].remarks == Remarks[1] ){
				x = 2;
				ontime.pop();
				ontime.push(index);
			}
			else if (arr[index].remarks == Remarks[2] ){
				if (rand()%4 == 0){
					x = 3;

					// Add 1 min to current obj.time due to delay;
					string newtime = getHour(arr[index].time) + ":";
					string min = getMin(arr[index].time);
					int newmin = stoi(min)+1;

					if (newmin%10==newmin){
						newtime += "0";
						newtime += to_string(newmin);
					}else {
						newtime += to_string(newmin);
					}

					arr[index].time = newtime;
					ontime.pop();
				}
				else{
					x = 4;
					ontime.pop();
					ontime.push(index);
				}
			}
			else if (arr[index].remarks == Remarks[3] ){
				x = 4;
				ontime.pop();
	 			ontime.push(index);
			}
			else if (arr[index].remarks == Remarks[4] ){
				x = 5;
				ontime.pop();
				ontime.push(index);
			}
			else if (arr[index].remarks == Remarks[5] ){
				x = 6;
				ontime.pop();
			}
			arr[index].remarks = remarks(x);
		}
	}

	// Fill up obj that has "" / empty data
	for (int k = 0; k<empty.size();k++){
		int x = empty.front();

		arr[x].country=country();
		arr[x].flight=flight();
		arr[x].time=time();
		arr[x].remarks=remarks(0);

		empty.pop();
	}

	// Empty data of obj with "Departed" remark
	for (int j = 0; j<dep.size();j++){
		int x = dep.front();

		arr[x].remarks = "";
		arr[x].flight = "";
		arr[x].time = "";
		arr[x].country = "";

		dep.pop();
		empty.push(x);
	}

	// Clear all queue to avoid stacking the indexes multiple time
//	clearQueue();
}

int checknum(string input){
	
	for (int i=0;i<(sizeof(arr)/sizeof(*arr));i++){
		if(arr[i].flight==input){
			cout<<arr[i].flight<<setw(9);
			cout<<arr[i].country<<setw(9);
			cout<<arr[i].time<<setw(15);
			cout<<arr[i].remarks;
			cout<<endl;		
			return 0;
		}
	}
	
	cout<< "Flight Number " << input <<" Not Found"<<endl;
	return 1;
}

void input(){
	
	if(_kbhit()){
		switch(_getch()){
			case '1' : menu = 0;break;
			case '2' : menu = 1;break;
			case '3' : menu = 2;break;
			case 'x' : run = false;break;
			
		}
	}
}

void menu1(){
		clearQueue();
		printdata(); //cout << //"print ";
		checkData(); //cout << //"check ";
	
		cout<<"press 2 to search for flight."<<endl;
		cout<<"press 3 to see the announcement."<<endl;
		sleep(3);
		update(); //cout << "update "<< endl;
		

		gotoxy(0,0);

}

void menu2(){
	string flightnum;

		system("cls");
		cout<<"Flight Number : ";
		getline (std::cin,flightnum);
		checknum(flightnum);
		
		cout<<"press 1 to exit search"<<endl;
		sleep(3);
		system("cls");

}

void menu3(){
	system("cls");
	announcement(dep, land, delay, arr);
	sleep(3);
	system("cls");
}
int main(){
	srand(time(NULL));

	declaredata();
	
	while (run){
		input();
		if(menu == 0){
			menu1();
		}else if (menu == 1){
			menu2();
		}else if(menu == 2){
			menu3();
		}
		input();
	}

	cin.ignore();
	return 0;
}
