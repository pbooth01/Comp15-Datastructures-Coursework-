//
//

#include "Node.h"
#include "Trie.h"
#include "songlist.h"

using namespace std;

int main(){

	string searchword;
	songlist song_data_base;

	string filename = "lyrics_fulldb.txt";
	song_data_base.read_lyrics(filename.c_str(), true);

		while (searchword != "<BREAK>"){
		cin >> searchword;
		song_data_base.search(searchword);
	}
	
	return 0;
}
