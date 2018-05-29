#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <string>
#include <queue>
#include "Time.h"

using namespace std;

class Flight {
	public:

		Flight();

		struct node{
			string flight;
			string remarks;
			string country;
			Time time;
		};

		node arr[20];
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
		void randomiseQueue(queue<int> q);
		void announcement();
		void checkData();
		void clearQueue();
		void declareData();
		void printData();
		void fillEmpty();
		void emptyObj();
		void update();
		int checkNum(string input);
};

#endif
