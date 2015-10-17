//
//  day.cpp
//
// Enter overview information here.

#include "dayDynamicArray.h"
#include <cassert>
#include <string>
#include <sstream>

const int Day::INIT_CAPACITY;

Day::Day(){ // constructor
        eventList = NULL; // empty Day
        eventCount = 0;
        eventCapacity = 0;
        theDate.day = 1;
        theDate.month = 1;
        theDate.year = 2014;
}

Day::Day(date aDate) { // constructor
        eventList = NULL; // empty Day
        eventCount = 0;
        eventCapacity = 0;
        theDate.year = aDate.year;
	theDate.month = aDate.month;
	theDate.day = aDate.day;
}

void Day::scheduleEvent() { // add default event for a full Day
        scheduleEvent(0,2359,"");
}
void Day::scheduleEvent(int startTime, int endTime, string description){
        if (eventList == NULL) {
                eventList = new Event[INIT_CAPACITY];
                eventCapacity = INIT_CAPACITY;
        }
        else if (eventCapacity == eventCount){
                Event *tempList = new Event[eventCapacity * 2];
                for (int index=0;index<eventCount;index++){
                        tempList[index] = eventList[index];
                }
                delete [] eventList;
                eventList = tempList;
                eventCapacity = eventCapacity * 2;
        }
        
        // create a new event
        Event evt = Event(startTime,endTime,description);
        
        // find the location where we need to insert the event
        int index;
        for (index=0;index<eventCount;index++) {
                if (evt.amIBefore(eventList[index])) break;
        }
        // move the second to last item to the end, and then
        // continue down the list
        for (int moveIndex=eventCount;moveIndex > index; moveIndex--) {
                eventList[moveIndex] = eventList[moveIndex - 1];
        }
        eventList[index] = evt;
        eventCount++;
}

void Day::scheduleEvent(Event anEvent){
        scheduleEvent(anEvent.getStartTime(),anEvent.getEndTime(),anEvent.getDescription());
}

// attempts to schedule an Event at the earliest time available at or after the event starts
// This may schedule the Event at the original time, or later in the Day.
// Returns true if successful, false if the Day is full and the Event could not be scheduled
bool Day::scheduleEarliest(Event anEvent){
	//cerr << "schedule Earliest" << endl;
        int nextAvailableTime = nextFreeBlock(anEvent);
        if (nextAvailableTime == -1) {
                return false; // no time during the Day!
        }
	//finds the earliest possible start time and then just adds the duration of the event
	//to the new start time to get that events end time
        else {
		int timeblock = duration(anEvent.getStartTime(), anEvent.getEndTime());
                anEvent.setStartTime(nextAvailableTime);
		anEvent.setEndTime(nextAvailableTime + timeblock);

		scheduleEvent(anEvent);
		return true;
        }
}

void Day::cancelEvent(Event anEvent){
        // find the event
        int index;
        for (index = 0;index < eventCount; index++){
                if (eventList[index].isSameEventAs(anEvent)){
                        int delIndex;
                        for (delIndex=index;delIndex<eventCount-1;delIndex++){
                                eventList[delIndex] = eventList[delIndex+1];
                        }
                        eventCount--;
                        break; // found it, so no need to continue
                }
        }
}

// nextFreeBlock() returns a startTime integer for the next free block of time
// that will fit the Event.
// If the time is the same as the event's original startTime,
// then there wasn't a conflict.
// The function returns -1 if there was no suitable time for the event to end before 2359.
int Day::nextFreeBlock(Event anEvent) {
        int timeblock = duration(anEvent.getStartTime(), anEvent.getEndTime());
	int placehold = 1;
	int i = 0;
	bool marked = false;
	//check to make sure the same event isnt inserted more then once
	for(int check = 0; check < eventCount; check++){
		if(anEvent.getStartTime() == eventList[check].getStartTime() &&
		   anEvent.getEndTime() == eventList[check].getEndTime() &&
		   anEvent.getDescription() == eventList[check].getDescription()){
			return -1;
		}
	}
	//if list is empty or if the event's start time is after the last event in the list
	
	if ((eventCount == 0) || (anEvent.getStartTime() >= eventList[eventCount-1].getEndTime() && 
	     duration(eventList[eventCount-1].getEndTime(), 2359) >= timeblock)){
		return anEvent.getStartTime();
	}
	//finding the first event in the list that has a larger start time then anEvent
	for(i = 0; i < eventCount; i++){
		if (anEvent.getStartTime() < eventList[i].getStartTime()){
			placehold = i;
			marked = true;
			break;
		}
	}
	//with the way that I cycle through the array I needed a case where it checked to see if
	//the event didnt fit between the last event and the second to last event. If it doesnt
	//then it just returns the endtime of the last event.
	//if the first event in the list is marked and there are no conflicts then returnthe start 
	//time of the event.	
	if(placehold == 0 && marked == true){
		if (duration(0, eventList[placehold].getStartTime()) >= timeblock &&
		    anEvent.getEndTime() <= eventList[placehold].getStartTime()){
			return anEvent.getStartTime();
		}
	}
	if (marked == true){
		if(placehold == eventCount-1 && (anEvent.getEndTime() > eventList[placehold].getStartTime() ||
			  anEvent.getStartTime() < eventList[placehold-1].getEndTime()) &&
			  duration(eventList[placehold].getEndTime(), 2359) >= timeblock){
				return eventList[placehold].getEndTime();
			}
	}
	//checks to see if the event can fit in between two events on its own. If it can it returns the events start time.
	// If it cant then it cycles through the array until it finds a time block between two events where the event can fit. 
	// Tried to use the conflictsWith function but I could not get it to work.
		if(marked == true){
			for(int j= placehold; j <= eventCount-1; j++){
			 	if ((anEvent.getEndTime() <= eventList[placehold].getStartTime()) && 
			    	anEvent.getStartTime() >= eventList[placehold-1].getEndTime()
				&& duration(eventList[placehold-1].getEndTime(), eventList[placehold].getStartTime()) >= timeblock){
					return anEvent.getStartTime();
			}
				else if (duration(eventList[j].getEndTime(), eventList[j+1].getStartTime()) >= timeblock &&
				anEvent.getStartTime() >= eventList[j].getEndTime() && 
				anEvent.getEndTime() <= eventList[j+1].getStartTime()
				&& duration(eventList[j].getEndTime(), eventList[j+1].getStartTime()) >= timeblock){
					return eventList[j].getEndTime();
				}
			}
		}
	//if it makes it to the end then the only logicl place for the event to go is at the 
	//end of the list
	if (duration(eventList[eventCount-1].getEndTime(), 2359) >= timeblock){
		return eventList[eventCount-1].getEndTime();
	}
	return (-1);
}

// the printDay() function prints an entire Day, beginning with the Date on one line, in the
// following format:
// Date: 4/25/2014
void Day::printDay() {

	cout << "Date: " << theDate.month << "/" << theDate.day << "/" << theDate.year << endl;
	for(int i = 0; i < eventCount; i++){
		eventList[i].printEvent();
	}
}

string Day::exportDay(){
        // this function exports the day into 
        ostringstream day_oss;
        day_oss << theDate.month << "/" << theDate.day << "/" << theDate.year;
        string csvString = "";
        for (int index=0;index < eventCount; index++) {
                csvString+= day_oss.str() + "," + day_oss.str() + "," +
                eventList[index].eventCSV() + "\n";
        }
        return csvString;
}

bool Day::isBefore(Day anotherDay) {
        // check year
        if (theDate.year < anotherDay.theDate.year) return true;
        if (theDate.year > anotherDay.theDate.year) return false;
        
        // year is the same, check month
        if (theDate.month < anotherDay.theDate.month) return true;
        if (theDate.month > anotherDay.theDate.month) return false;
        
        // month is the same, check day
        if (theDate.day < anotherDay.theDate.day) return true;
        if (theDate.day > anotherDay.theDate.day) return false;
        return false;
}

int Day::duration(int time1,int time2){
        // calculate a duration between two times in the same day
        // time1 <= time2
        // returns a duration in 24-hour time
        int durationHours,durationMinutes;
        
        int time1Hours = time1 / 100;
        int time1Minutes = time1 - (time1Hours * 100);
        
        int time2Hours = time2 / 100;
        int time2Minutes = time2 - (time2Hours * 100);
        
        durationHours = time2Hours-time1Hours;
        durationMinutes = time2Minutes-time1Minutes;
        
        if (durationMinutes < 0) {
                durationHours--;
                durationMinutes+=60;
        }
        return durationHours * 100 + durationMinutes;
}

int Day::addTimes(int time1,int time2){
        // add two 24-hour times together
        int totalHours,totalMinutes;
        
        int time1Hours = time1 / 100;
        int time1Minutes = time1 - (time1Hours * 100);
        
        int time2Hours = time2 / 100;
        int time2Minutes = time2 - (time2Hours * 100);
        
        totalHours = time2Hours+time1Hours;
        totalMinutes = time2Minutes+time1Minutes;
        
        if (totalMinutes >=60) {
                totalHours++;
                totalMinutes-=60;
        }
        return totalHours * 100 + totalMinutes;
}

Day::~Day(){
        //if (eventList != NULL)
        //        delete [] eventList;
}

Day::Day(const Day &rightHandSide) {
        // first copy the values
        eventCapacity = rightHandSide.eventCapacity;
        eventCount = rightHandSide.eventCount;
        theDate = rightHandSide.theDate;
        eventList = NULL;
        
        if (eventCapacity==0) return;
        
        // create a new eventList and copy all events
        delete [] eventList;
        eventList = new Event[eventCapacity];
        
        for (int i=0;i<eventCount;i++) {
                eventList[i] = rightHandSide.eventList[i];
        }
}

Day &Day::operator=(const Day &rightHandSide){
        if (this != &rightHandSide) {
                // first copy the values
                eventCapacity = rightHandSide.eventCapacity;
                eventCount = rightHandSide.eventCount;
                theDate = rightHandSide.theDate;
                eventList = NULL;
                if (eventCapacity == 0) return *this;
                delete [] eventList;
                
                eventList = new Event[eventCapacity];
                
                for (int i=0;i<eventCount;i++) {
                        eventList[i] = rightHandSide.eventList[i];
                }
        }
        return *this;
        
}
