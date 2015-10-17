//  day.cpp
//  CalendarOrderedLists
//
//	Name: Phillip Booth
//  Class: Comp 15 
//	Professor Chris Gregg.


#include "dayDynamicArray.h"
#include <cassert>
#include <string>

const int Day::INIT_CAPACITY;

Day::Day(){ // constructor
        eventList = new Event[INIT_CAPACITY]; //pointer to dynamic array
	eventCount = 0;
	eventCapacity = INIT_CAPACITY;
}

void Day::scheduleEvent() { // add default event for a full Day
        scheduleEvent(0,2359,"");
}
void Day::scheduleEvent(int startTime, int endTime, string description){
	Event newevent = Event(startTime, endTime, description);
	Event tempnode1;// = Event(startTime, endTime, description);

	for(int check = 0; check < eventCount; check++){
		if (eventList[check].isSameEventAs(newevent) == true){
			return;
		}
	}
	if(eventCount == eventCapacity){
		eventCapacity = (eventCapacity * 2);          //creating temparray
		Event *temparray = new Event[eventCapacity];  //with twice as much
		for (int i=0; i < eventCount; i++){	     //space and copying data
			temparray[i] = eventList[i];	     //data into it.
		}
		delete[] eventList;
		eventList = temparray;		//getting rid of old array
	}
	for(int iterate = 0; iterate < eventCount + 1; iterate++){
		if(newevent.amIBefore(eventList[iterate]) == true || iterate == eventCount){
			tempnode1 = eventList[iterate];    //inserting new event into the array in the correct palce
			eventList[iterate] = newevent;     //accounts for both infront of and after with the if statement
			newevent = tempnode1;
		}	
	}
	eventCount++;
}

void Day::scheduleEvent(Event anEvent){
        scheduleEvent(anEvent.getStartTime(),anEvent.getEndTime(),anEvent.getDescription());
}

void Day::cancelEvent(Event anEvent){
	bool eventfound = false;
        for(int i = 0; i <= eventCount; i++){
		if(eventList[i].isSameEventAs(anEvent)){  //making sure that event is in the array
			eventfound = true;
			eventCount = eventCount - 1;     //decrementing the eventcount when
		}					 //the event is found
		if(eventfound == true){
			eventList[i] = eventList[i+1];  
			for(int iterate = i+1; iterate < eventCount; iterate++){ //shift the rest of the data over
				eventList[iterate] = eventList[iterate+1];
			}
		}
	}
}

void Day::printDay() {
        for (int i = 0; i < eventCount; i++){   //iterates through the array and prints each event
		eventList[i].printEvent();
		cout << endl;
	}
}

string Day::exportDay(){
        string csvString = "";
        for (int index=0;index < eventCount; index++) {
                csvString+= eventList[index].eventCSV() + "\n";
        }
        return csvString;
}

Day::~Day(){
        delete [] eventList;
}
