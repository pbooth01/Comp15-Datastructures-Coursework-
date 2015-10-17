//
//  dayLinkedList.h
//  CalendarOrderedLists
//
//  Name: Phillip Booth
//  Class: Comp 15 
//  Professor Chris Gregg.

#ifndef __CalendarOrderedLists__dayLinkedList__
#define __CalendarOrderedLists__dayLinkedList__

#include <iostream>
#include "event.h"

struct EventNode {
        Event theEvent;
        EventNode *next;
};

class Day {
public:        
	Day(); // constructor
        void scheduleEvent(); // default event for full day
        void scheduleEvent(int startTime, int endTime, string description);
        void scheduleEvent(Event anEvent);
        void cancelEvent(Event anEvent);
        void printDay();
        string exportDay();
        ~Day(); // destructor
private:
	EventNode *eventList;
        int eventCount;        
};


#endif /* defined(__CalendarOrderedLists__dayLinkedList__) */
