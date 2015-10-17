//  Node.cpp
//  Created by Chris Gregg on 3/29/14.
//  Copyright (c) 2014 Chris Gregg. All rights reserved.

#include "Node.h"

Node::Node() { 
	theCharacter = ' '; 
	wordMarker = false;
	freq = 0; 
	//does vector initialize itself??
}
//The function adds a a new Node to the vector in another Node. this
//functions so that the trie is able to hold words as well as a word with
//a number it, and still be able to recognize it as a word in the trie.  
//Also good for memory because the vector only hold the children that are
//used in the trie.
void Node::appendChild(Node* child) { 
	children.push_back(child);
}
//The function determines whether one node contains another node by using 
//a char c.  IF the node's vector contians the node with a char c it returns
//a pointer to the node.
Node* Node::findChild(char c){
	for (size_t i = 0; i < children.size(); i++){
		Node* tmp = children.at(i);
		if (tmp->content() == c ){
			return tmp;
		}
	}
	return NULL;
}


size_t Node::addPreNodes(vector <preNode> preNodes,int level,size_t index) {
	while (index != preNodes.size()) { // base case
		preNode pn = preNodes[index];
		//cout << level << "," << pn.level << "," << pn.c << "," << pn.wordMarker << "\n";
		if (pn.level <= level) return index; // next sibling
		// we have a child to add
		Node *tmp = new Node();
		tmp->setCharacter(pn.c);
		if (pn.wordMarker) tmp->setWordMarker();
		appendChild(tmp);
		index = tmp->addPreNodes(preNodes,pn.level,index+1);
	}
	return index;
}
