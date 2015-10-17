
//  Created by Chris Gregg on 3/29/14.
//  Copyright (c) 2014 Chris Gregg. All rights reserved.
//
//Note some of this code came from the link that professor Greg supplied
//to us.  SourceTricks.com
#include "Trie.h"

Trie::Trie()
{
        root = new Node();
}

Trie::~Trie()
{
        // Free memory
}
//The function adds a word to a trie by breaking it down into its individual
//characters and placing each one into a trie.
void Trie::addWord(string s)
{
        Node *tmp = root;
	Node *childnode;

	if (s.length() == 0){
		tmp->setWordMarker(); //an empty word
		return;
	}
	for(size_t i = 0; i < s.length(); i++){
		if (tmp->findChild(s[i]) == NULL){
			childnode = new Node();
			childnode->setCharacter(s[i]);
			tmp->appendChild(childnode);
			tmp = tmp->findChild(s[i]); 
		} 
		else{ tmp = tmp->findChild(s[i]);}

		if (i == s.length() -1){
			tmp->setWordMarker();
			tmp->trackfreq();
		}
	}	
}
//The function returns the freq that is part of the preNode struct.
//This function is very important later because it allows songs
//to be sorted based on the frequency that a particular word appears.
int Trie::getfreq(string s)
{
        Node *tmp = root;
	while (tmp != NULL){
		for (size_t i = 0; i < s.length(); i++){
		
			tmp = tmp->findChild(s[i]);
		}
		if (tmp->getWordMarker() == true){
			return tmp->getfreq();
		}					
	}
}
//The function searches in the trie for a word.  It does this by following
//where the characters of a word would end up in the trie and then seeing
//if the final letter node is marked as being a word.
bool Trie::searchWord(string s)
{
        Node *tmp = root;
	while (tmp != NULL){
		for (size_t i = 0; i < s.length(); i++){
			if (tmp->findChild(s[i]) == NULL){
				return false;
			}
			else {tmp = tmp->findChild(s[i]);}
		}
		if (tmp->getWordMarker() == true){
			//cout << "frequency is " << getfreq(s) << endl;
			return true;
		}		
		else {return false;}
	}
	return false;
}
		

/*void Trie::printTrie(){
        root->printNode(0);
}
*/
void Trie::addPreNodes(vector<preNode> preNodes) {
	root->addPreNodes(preNodes,0,1);
}
