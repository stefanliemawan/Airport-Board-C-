#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <unistd.h>

using namespace std;

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
	
	for (int i=0; i<4; i++) {
		random = rand() % 10;
		number = to_string(random);
		flightcode += number;
	}
		
	return flightcode;
}

string country() { //Generate Random Country
	
	string arr[] = {"London","Alaska","Boston","Roma"} ;
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
	int min = aTime->tm_min;
	clock += to_string(hour);
	clock += ":";
	clock += to_string(min);
	
	return clock;
}

string remarks() { //Generate Remarks (Sequencial)

	string arr[] = {"Landing","Delayed","Boarding","On Schedule","Departed"};
	string remarks;
	int random;
	
	random = rand() % (sizeof(arr)/sizeof(*arr));
	remarks = arr[random];
	
	return remarks;
}

struct node {
	string flight;
	string country;
	string time;
	string remarks;
}*data;

void createnode(){
	data = new node;
	data->flight = flight();
	data->country = country();
	data->time = time();
	data->remarks = remarks();
}

void printnode() {
	cout << endl;
	cout << data->flight << setw(20) << data->country << setw(20) << data->time << setw(20) << data->remarks;
	cout << endl;
}

//use queue to print node, with max number

int main() {
	
	srand(time(NULL));

	int i;
	
	while (i<30){
		createnode();
		sleep(1);
		printnode();
		cout << "\33[2K";
		i++;
	}
	
}
