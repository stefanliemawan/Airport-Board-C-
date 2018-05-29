#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Time {
  public:
    string ttime;

    void emptyTime();
    void addDelay();
    void maketime();
    void currentTime();
    void startTime();
    string convertTime(int hour, int min);
    string getHour(string time);
    string getMin(string time);
    string getTime();
};

#endif
