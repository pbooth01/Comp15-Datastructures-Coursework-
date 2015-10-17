#
# Makefile for SongSearch, Assignment 5
#
CXX = clang++
FLAGS = -Wall -Wextra -Wconversion -g

songsearch: <your files go here>
	${CXX} ${FLAGS} -o songsearch <your .cpp files go here>

test: 	Trie.cpp Trie.h Node.h Node.cpp main.cpp songlist.cpp songlist.h

	${CXX} ${FLAGS} -o test Trie.cpp Node.cpp main.cpp songlist.cpp

clean:
	rm -f songsearch

provide_design:
	provide comp15 hw5_design songsearch_design.txt

provide:
	provide comp15 hw5 main.cpp Node.h Node.cpp readme.txt songlist.cpp songlist.h Trie.cpp Trie.h


