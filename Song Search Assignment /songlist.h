#ifndef SONGLIST_H
#define SONGLIST_H
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <fstream>
#include "Trie.h"
#include "Node.h"

using namespace std;

struct Song {
	string artist;
	string title;
	vector <string> lyrics;
	Trie *trie;
	
};

class songlist {

public:

songlist();

string stripword(string s);

string lower(string s);

void read_lyrics(const char * filename, bool show_progress);

void search (string s);

void topTen (vector<Song*> song, string word);

void print (vector<Song*> song, string word);
private:
 vector <Song*> SongDB;

};
#endif  /* SONGLIST_H */
