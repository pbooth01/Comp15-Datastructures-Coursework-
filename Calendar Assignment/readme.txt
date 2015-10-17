The overall purpose of this program is to import data from a google calendar
and put that data into a logical order

The program had 3 different classes

The first class was an event class which held various functions to help your
second class (dayDynamicArray) order events within a specific day as they are
scheduled. These functions include one to tell you when two events conflict
and when one event is before another.  Also the event class was resposible 
for converting the times of each event into regular AM and PM times when 
they were printed out.

The second class of the program is the dayDynamicArray class, which is
responsible for taking in scheduled events and putting them in order
within a specific day.  The two functions in this class that were new
compared to the last homework were scheduleEarliest and nextFreeBlock.
NextFreeBlock was supposed to search through the array of events and return
the closest free block of time that would fit an event you want to schedule.
This function took into account the starttime of the event and wheather the
event would conflict with any other events in the array if was put into that
block of time.  Also, in my program nextfreeblock takes into account weather
an event already exists in he array so that the same event is not scheduled
more then once.  The info from nextfreeblock is used by the schedule earliest
function so that it can correctly alter the start and end times of an event so
it can keep the list in order.

The last Class in the program is the Calendar class which just keeps track of
the number of days and also schedules days in order by placing them inside of
a dynamic array.

The overall outcome of the program is to import data from google calendar and
organize it into an array of days with each day containing an aray of events. 
