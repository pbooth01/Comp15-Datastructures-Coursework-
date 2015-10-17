//
//  DayLinkedList.cpp
//  CalendarOrderedLists
//
//  Name: Phillip Booth
//  Class: Comp 15 
//  Professor Chris Gregg.

#include "dayLinkedList.h"
#include <cassert>

Day::Day(){ // constructor
        eventList = NULL;
}

void Day::scheduleEvent() { // add default Event for a full Day
        scheduleEvent(0,2359,"");
}
void Day::scheduleEvent(int startTime, int endTime, string description){
	EventNode *neweventnode = new EventNode();
	neweventnode->theEvent = Event(startTime, endTime, description);

	EventNode *prevNode = eventList; //temp nodes that will be used to iterate through the linked list
	EventNode *nextNode = eventList;

	if(prevNode == NULL){  //List is Empty
		eventList = neweventnode;
	}
	else if(neweventnode->theEvent.getStartTime() == prevNode->theEvent.getStartTime()){
		neweventnode->next = prevNode->next;  //runs if start time of the first link  is the same
		prevNode->next = neweventnode;	      //as the start time of the event you want to insert
	}
	else if(neweventnode->theEvent.amIBefore(prevNode->theEvent) == true ){
		neweventnode->next = prevNode; //runs if the event you want to insert comes before the first
		eventList = neweventnode;     // element in the eventlist
	}
	else {
		 while (prevNode->next != NULL){
			nextNode = prevNode->next;
			 
			if ((neweventnode->theEvent.getStartTime() == 
			   nextNode->theEvent.getStartTime()) && nextNode->next != NULL && (nextNode->next->theEvent.getStartTime()!= 
			   neweventnode->theEvent.getStartTime())){       //inserts an event behind an event with the 
			   neweventnode->next = nextNode->next;     //same start time while in the middle of the eventlist.
			   nextNode->next = neweventnode;	   //if a couple of events in the eventlisthave
			   return;				   //have the same start time the event is inserted
			}					   //after the last one of them.

			else if(neweventnode->theEvent.amIBefore(nextNode->theEvent)== true){
				neweventnode->next = nextNode;   //inserts an event in the middle of the eventlist
				prevNode->next = neweventnode;   //after an event in the list with the same time
				return;
			}
			prevNode = prevNode->next;
	 	}
		if(((nextNode->next == NULL) && (neweventnode->theEvent.amIBefore(nextNode->theEvent)== false))||
		 (neweventnode->theEvent.getStartTime() == nextNode->theEvent.getStartTime())){
			nextNode->next = neweventnode;   //inserts an event at the end of the list
			neweventnode->next = NULL;
		}
	}
}

void Day::scheduleEvent(Event anEvent){
        scheduleEvent(anEvent.getStartTime(),anEvent.getEndTime(),anEvent.getDescription());
}

void Day::cancelEvent(Event anEvent){
	EventNode *nextNode = eventList;
	EventNode *prevNode = eventList;
	EventNode *iterator = eventList;
	bool located = false;

	if(prevNode == NULL){}  //If list is empty
	else{
		while(iterator != NULL){
			if(iterator-> theEvent.isSameEventAs(anEvent) == true){
				located = true;    //Check to make sure item is in list
			}
			iterator = iterator -> next;
		}
		if(located == true){
			if(prevNode->next == NULL && anEvent.isSameEventAs(prevNode->theEvent)== true){
				eventList = NULL;  //if there is only one item in the list
			}
			while(prevNode->next != NULL){
				nextNode = prevNode->next;
				if(anEvent.isSameEventAs(prevNode->theEvent) == true){
					eventList = prevNode->next; //if first item in a list of multiple items matches
					eventCount--;
				}
				else if (anEvent.isSameEventAs(nextNode->theEvent) == true
		   		&& nextNode->next == NULL){ //if very last item matches
					prevNode->next = NULL;
					return;
					eventCount--;	
				}
				else if (anEvent.isSameEventAs(nextNode->theEvent) == true //if middle item matches
		        		&& nextNode->next != NULL){
						prevNode->next = nextNode->next;
						eventCount--;
				}
				prevNode = prevNode->next; //making sure you are able to iterate throughout the list
			}
		}
		else if (located == false){return;}
	}
}

void Day::printDay() {
        EventNode *nextNode = eventList;

	while(nextNode != NULL){
		nextNode -> theEvent.printEvent(); //iterates through the eventlist and prints the events
		cout << endl;			   //in order
		nextNode = nextNode -> next;
	}
}

string Day::exportDay(){
        string csvString = "";
        EventNode *tempEventNode = eventList;
        while (tempEventNode != NULL) {
                csvString+= tempEventNode->theEvent.eventCSV() + "\n";
                tempEventNode = tempEventNode->next;
        }
        return csvString;
}
Day::~Day() {
        while (eventList != NULL) {
                EventNode *tempNextNode = eventList->next;
                delete eventList;
                eventList = tempNextNode;
        }
}
