#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Flight {
	public :
		
		Flight();
		
		struct node{
			string flight;
			string remarks;
			string country;
			string time;
		};
		node arr[20];
		queue<int> dep;
		queue<int> land;
		queue<int> empty;
		queue<int> ontime;
		queue<int> delay;
		
		string Remarks[7] = {
			"Landing","Refuel","On Schedule","Delayed","Boarding","Final Check","Departed"
		};

		string remarks(int index);
		string flight();
		string country();
		string time();
		string currentTime();
		void announcement();
		void newData();
		void checkData();
		void clearQueue();
		void declareData();
		void printData();
		string getHour(string time);
		string getMin(string time);
		void update();
		int checkNum(string input);
};

#endif

