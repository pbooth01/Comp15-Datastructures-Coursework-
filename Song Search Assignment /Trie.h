//
//  Trie.h

#ifndef __trie__Trie__
#define __trie__Trie__

#include <iostream>
#include "Trie.h"
#include "Node.h"

using namespace std;

class Trie {
public:
        Trie();
        ~Trie();
        void addWord(string s);
        bool searchWord(string s);
        void deleteWord(string s);
        void printTrie();
		int getfreq(string s);
        void addPreNodes(vector<preNode> preNodes);
private:
        Node* root;
};

#endif /* defined(__trie__Trie__) */
