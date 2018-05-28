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
		int timer;
		queue<int> dep;
		queue<int> land;
		queue<int> delay;
		queue<int> empty;

		queue<int> start;
		queue<int> ontime;

		string Remarks[7] = {
			"Landing","Refuel","On Schedule","Delayed","Boarding","Final Check","Departed"
		};

		string remarks(int index);
		string flight();
		string country();
		string time();
		string currentTime();
		string startTime();
		void announcement();
		void checkData();
		void clearQueue();
		void declareData();
		void printData();
		string convertTime(int hour, int min);
		string getHour(string time);
		string getMin(string time);
		void fillEmpty();
		void emptyObj();
		void update();
		int getSecond();
		int checkNum(string input);
};

#endif
