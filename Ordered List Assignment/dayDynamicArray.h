//
//  day.h
//  CalendarOrderedLists
//
//  Name: Phillip Booth
//  Class: Comp 15 
//  Professor Chris Gregg.

#ifndef __CalendarOrderedLists__day__
#define __CalendarOrderedLists__day__

#include <iostream>
#include "event.h"

class Day {
public:
        static const int INIT_CAPACITY = 5;
        
	Day(); // constructor
        void scheduleEvent(); // default event for full day
        void scheduleEvent(int startTime, int endTime, string description);
        void scheduleEvent(Event anEvent);
        void cancelEvent(Event anEvent);
        void printDay();
        string exportDay();
        
        ~Day(); // destructor
private:
	Event *eventList;
        int eventCount;
        int eventCapacity;

};

#endif /* defined(__CalendarOrderedLists__day__) */
