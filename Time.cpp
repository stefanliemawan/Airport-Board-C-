#include <iostream>
#include <string>
#include <iomanip>
#include "Time.h"

using namespace std;

// Empty the time
void Time::emptyTime(){
  ttime = "";
}

// Add delay to time
void Time::addDelay(){
	int delay = rand()%2 + 1;

	// Add 1 min to current obj.time due to delay;
	int newhour = stoi(getHour(ttime));
	int newmin = stoi(getMin(ttime))+delay;

	string newtime = convertTime(newhour, newmin);

  ttime = newtime;
}

// Produce current time + random int (between 0 & 3)
void Time::maketime() {

	time_t theTime = std::time(NULL);
	struct tm *aTime = localtime(&theTime);

	int hour = aTime->tm_hour;
	int min;

	// Check second to avoid getting current minute after current minute increase due to sleep
	if (aTime->tm_sec >= 46){
		min = (aTime->tm_min)+(rand()%3+1);
	}else {
		min = (aTime->tm_min)+(rand()%3);
	}

  ttime = convertTime(hour, min);
}

// Return the current time for checkData()
void Time::currentTime(){

	time_t theTime = std::time(NULL);
	struct tm *aTime = localtime(&theTime);

	int hour = aTime->tm_hour;
	int min = aTime->tm_min;

	ttime = convertTime(hour, min);
}

// Return the current time for checkData()
void Time::startTime(){

	time_t theTime = std::time(NULL);
	struct tm *aTime = localtime(&theTime);

	int hour = aTime->tm_hour;
	int min = (aTime->tm_min)+1;

	ttime = convertTime(hour, min);
}

// Convert integer hour and min to a proper time string
string Time::convertTime(int hour, int min){
	string newtime;

	if (min >= 60){
		hour += 1;
		min = min%60;
	}

	if (hour%10==hour){
		newtime += "0";
		newtime += to_string(hour);
	}else {
		newtime += to_string(hour);
	}

	newtime += ":";

	if (min%10==min){
		newtime += "0";
		newtime += to_string(min);
	}else {
		newtime += to_string(min);
	}

	return newtime;
}

//Get the hour of the obj
string Time::getHour(string time){
	string seperator = ":";
	int pos = time.find(seperator);
  string hour = time.substr(0, pos);

  return hour;
}

//Get the min of the obj
string Time::getMin(string time){
	string seperator = ":";
	int pos = time.find(seperator);
  string token = time.substr(0, pos);

  string min = time.erase(0, pos + seperator.length());
  return min;
}

// Return time for printing
string Time::getTime(){
  return ttime;
}
