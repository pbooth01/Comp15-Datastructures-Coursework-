//
//  Node.h
//  trie
//
//  Created by Chris Gregg on 3/29/14.
//  Copyright (c) 2014 Chris Gregg. All rights reserved.
//

#ifndef __trie__Node__
#define __trie__Node__

#include <iostream>
#include <vector>

using namespace std;

struct preNode {
	int level;
	char c;
	bool wordMarker;
	int freq;    //way to keep track of number of times
		    //a word  appears in a song
};

class Node {
public:
	//static const int ALPHABET_LENGTH = 26;
        Node ();
        ~Node() {}
        char content() { return theCharacter; }
        void setCharacter(char c) { theCharacter = c; }
        bool getWordMarker() { return wordMarker; }
        void setWordMarker() { wordMarker = true; }
        Node* findChild(char c);
        void appendChild(Node* child);
        //void printNode(int level);
        size_t addPreNodes(vector <preNode> preNodes, int level, size_t index);
	void trackfreq(){ freq = freq+1;} //making sure to increment frequency
	int getfreq(){return freq;}
	vector <Node*> kids();
        
private:
        char theCharacter;
        bool wordMarker;
	int freq;
        vector <Node*> children;
};


#endif /* defined(__trie__Node__) */
