#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <unistd.h>
#include <vector>

using namespace std;

struct node{
	string flight;
	string remarks;
	string country;
	string time;
	
};

node arr[10];

string Remarks[] = {"Landing","Delayed","Boarding","On Schedule","Departed"};


string remarks() { //Generate Remarks (Sequencial)

//	string Remarks[] = {"Landing","Delayed","Boarding","On Schedule","Departed"};
	string remarks;
	int random;
	
	random = rand() % (sizeof(Remarks)/sizeof(*Remarks));
	remarks = Remarks[random];
	
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


void checkData(){
	for (int i=0;i<10;){
		if(arr[i].remarks=="Departed"){
			node obj;
			obj.country=country();
			obj.flight=flight();
			obj.time=time();
			obj.remarks=remarks();

			
			arr[i].country=obj.country;
			arr[i].flight=obj.flight;
			arr[i].remarks=obj.remarks;
			arr[i].time=obj.time;
		}
	}
}






	
	
void declaredata(){
	for (int i=0;i<10;i++){
	node obj;
	obj.flight=flight();
	obj.time=time();
	obj.country=country();
	obj.remarks=remarks();
	
	arr[i].flight=obj.flight;
	arr[i].country=obj.country;
	arr[i].remarks=obj.remarks;
	arr[i].time=obj.time;
	}
}

void printdata(){
	for (int i=0;i<10;i++){
			cout <<"||"<< setw(9)<< arr[i].flight << setw(9)<<"||"<< setw(9) << arr[i].country << setw(9)<<"||"<< setw(9) << arr[i].time << setw(9) <<"||"<< setw(15)<< arr[i].remarks<<setw(9)<<"||";

	}
	sleep(3);
	system("cls");
	sleep(0.8);
}


int main(){
	
	declaredata();
	
	while(true){
		printdata();
		//checkData();
		}
		

}



