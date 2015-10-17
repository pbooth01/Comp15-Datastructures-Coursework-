
	The purpose of the program was to create an ordered list that remains sorted
at all times.  In this program specifically, I was creating ordered lists of
Events within a single day.
	The program contained two seperate kind of classes.  One was the event
class and the other was the day class.  The  event class contains the private 
data of: startTime, endTime, and description ,as well as functions that allow 
me to get and set this data. The Event class also contains one function to 
compare the start times of two different events and another function that 
compares whether two events are thesame.
	Two versions of the day class were written.  One was dayLinkedList and
the other was dayDynamicArray and both functioned as classes that created a
list of events that were stored in order based on start time.  the difference
between the two programs was that the dayLinkedList used a linked list to
store the events and keep them in order while dayDynamicArray stored the data
in a dynamic array that constantly increased in size depending on the number
of events being added to the particular day.
	Both day classes contained the same functions that allowed the user to
add events to the day, cancel events in the day, and print all of the
events that are stored for that particular day.
	Whats interesting about the program is that both day classes are
linked to the event class and can be used interchangeably with main.cpp to do
the same things.
