#include <iostream>
#include <string>
#include <iomanip>
#include <queue>
#include "Flight.h"
#include "Time.cpp"

using namespace std;


Flight::Flight(){};

// Produce random remark
string Flight::remarks(int index) {

	string remarks;

	remarks = Remarks[index];

	return remarks;
}

// Produce random flight number
string Flight::flight() {

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
string Flight::country() {

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

// Announce the depart plane
void Flight::announcement(){
	cout<<"============"<<endl;
	cout<<"ANNOUNCEMENT"<<endl;
	cout<<"============"<<endl;
	int x;
	while(!dep.empty()){
		x = dep.front();
		dep.pop();
		cout<<arr[x].time.ttime<<setw(9)<<" flight No."<<arr[x].flight<<" has departed"<<endl;
	}
	while(!land.empty()){
		x=land.front();
		land.pop();
		cout<<arr[x].time.ttime<<setw(9)<<" flight No."<<arr[x].flight<<" has landed"<<endl;
	}
	while(!delay.empty()){
		x = delay.front();
		delay.pop();
		cout<<arr[x].time.ttime<<setw(9)<<" flight No."<<arr[x].flight<<" has been delayed"<<endl;
	}

	cout<<"press 1 to return to notice board"<<endl;
}

// Fill up the dep, land and ontime queue
void Flight::checkData(){

	Time ctime;
	Time stime;

	for (int i=0; i< (sizeof(arr)/sizeof(*arr)); i++){
		if(arr[i].remarks == "Departed"){
			dep.push(i);

		}else if(arr[i].remarks=="Landing"){
			land.push(i);

		}else if(arr[i].remarks == "Delayed"){
			delay.push(i);
		}
	}

	ctime.currentTime();
	stime.startTime();


	for (int i = 0; i < (sizeof(arr)/sizeof(*arr)); i++){
		if (arr[i].time.ttime == ctime.ttime){
			ontime.push(i);
		}else if (arr[i].time.ttime == stime.ttime){
			start.push(i);
		}else {
			continue;
		}
	}
}

// Clear up the dep, land and ontime queues
void Flight::clearQueue(){
	while(!land.empty()){
		land.pop();
	}
	while(!dep.empty()){
		dep.pop();
	}
	while(!ontime.empty()){
		ontime.pop();
	}
	while (!start.empty()){
		start.pop();
	}
	while(!delay.empty()){
		delay.pop();
	}
}

// Fill array with new objs
void Flight::declareData(){

	for (int i=0; i<(sizeof(arr)/sizeof(*arr)); i++){

		node obj;

		obj.flight=flight();
		obj.time.maketime();
		obj.country=country();
		obj.remarks=remarks(0);

		arr[i] = obj;
	}
}

// Print all data in form of Board
void Flight::printData(){

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
			<<"||"<< setw(9) << arr[i].time.ttime << setw(9)
			<<"||"<< setw(15)<< arr[i].remarks<<setw(9)<<"||" << endl;

	}
	cout<<"================================================================================"<<endl;



}

// Fill up obj that has "" / empty data
void Flight::fillEmpty(){
	for (int k = 0; k<empty.size();k++){
		int x = empty.front();

		arr[x].country=country();
		arr[x].flight=flight();
		arr[x].time.maketime();
		arr[x].remarks=remarks(0);

		empty.pop();
		empty.push(x);
	}

	while(!empty.empty()){
		empty.pop();
	}
}

// Empty data of obj with "Departed" remark
void Flight::emptyObj(){
	for (int j = 0; j<dep.size();j++){
		int x = dep.front();

		arr[x].remarks = "";
		arr[x].flight = "";
		arr[x].time.emptyTime();
		arr[x].country = "";

		dep.pop();
		empty.push(x);
	}
}

// Update the board >> logics applied here
void Flight::update(){

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

	// Avoid error if ontime queue is empty
	if (ontime.size() > 0){
		r = rand() % ontime.size()+1;

		if (ontime.size() > 2 & r <= ontime.size()/2){
			r += 1;
		}

		for (int a = 0; a < r; a++){
			int index = ontime.front();

			if (arr[index].remarks == Remarks[0] ){
				x = 1;
			}
			else if (arr[index].remarks == Remarks[1] ){
				x = 2;
			}
			else if (arr[index].remarks == Remarks[2] ){
				if (rand()%4 == 0){
					x = 3;

					arr[index].time.addDelay();
				}
				else{
					x = 4;
				}
			}
			else if (arr[index].remarks == Remarks[3] ){
				x = 4;
			}
			else if (arr[index].remarks == Remarks[4] ){
				x = 5;
			}
			else if (arr[index].remarks == Remarks[5] ){
				x = 6;
			}
			ontime.pop();
			ontime.push(index);

			arr[index].remarks = remarks(x);
		}
	}

	// Avoid error if start time queue is empty
	if (start.size() > 0){
		r = rand() % start.size()+1;

		if (start.size() > 2 & r <= start.size()/2){
			r += 1;
		}

		for (int a = 0; a < r; a++){
			int index = start.front();
			if (arr[index].remarks == Remarks[0] ){
				x = 1;
			}
			else if (arr[index].remarks == Remarks[1] ){
				x = 2;
			}
			else if (arr[index].remarks == Remarks[2] ){
				if (rand()%4 == 0){
					x = 3;

					arr[index].time.addDelay();
				}
				else{
					x = 4;
				}
			}
			else if (arr[index].remarks == Remarks[3] ){
				x = 4;
			}
			else {
				x = 5;
			}
			start.pop();
			start.push(index);

			arr[index].remarks = remarks(x);
		}
	}

	fillEmpty();

	emptyObj();
}

// Print the searched flight num
int Flight::checkNum(string input){

	for (int i=0;i<(sizeof(arr)/sizeof(*arr));i++){
		if(arr[i].flight==input){
			cout<<arr[i].flight<<setw(9);
			cout<<arr[i].country<<setw(9);
			cout<<arr[i].time.ttime<<setw(15);
			cout<<arr[i].remarks;
			cout<<endl;
			return 0;
		}
	}

	cout<< "Flight Number " << input <<" Not Found"<<endl;
	return 1;
}
