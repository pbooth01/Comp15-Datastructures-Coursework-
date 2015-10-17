#
# Makefile for Calendar Ordered Lists
#
CXX = clang++
FLAGS = -Wall -Wextra -Wconversion -g

all: dayDynamicArray.cpp dayDynamicArray.h \
     dayLinkedList.cpp dayLinkedList.h \
     event.cpp event.h main.cpp
	${CXX} ${FLAGS} -o orderedDynamicArray dayDynamicArray.cpp event.cpp main.cpp
	${CXX} ${FLAGS} -o orderedLinkedList dayLinkedList.cpp event.cpp main.cpp

orderedDynamicArray: dayDynamicArray.cpp dayDynamicArray.h event.cpp event.h main.cpp
	${CXX} ${FLAGS} -o orderedDynamicArray dayDynamicArray.cpp event.cpp main.cpp

orderedLinkedList: dayLinkedList.cpp dayLinkedList.h event.cpp event.h main.cpp
	${CXX} ${FLAGS} -o orderedLinkedList dayLinkedList.cpp event.cpp main.cpp

clean:
	rm -f orderedDynamicArray orderedLinkedList

make provide:
	provide comp15 hw2 main.cpp dayDynamicArray.cpp dayDynamicArray.h \
	        dayLinkedList.cpp dayLinkedList.h event.cpp event.h main.cpp \
	        readme.txt Makefile

