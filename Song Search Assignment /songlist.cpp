#include "songlist.h"
#include <sstream>

using namespace std;

songlist::songlist(){
	//vector <Song*> SongDB;
}
//Function takes in a string and removes all of the puntuation and Capitals.
//returns a string that is free of capitals and punctuation. This function 
//was supplied by Chris Gregg.

string songlist::stripword(string s){
	ostringstream ss;
	for (size_t i = 0; i < s.length(); i++) {
		if (isalnum(s[i])){
			ss << (char)(tolower(s[i]));
		}
	}
	return ss.str();	
}
//Function is used to read in the song information from a text file. It creates
//a new song struct and reads in its title and artist. Then reads in its lyrics.
//Also, it creates a vector of pointers to the song structs that it creates.
void songlist::read_lyrics(const char * filename, bool show_progress){
    	ifstream in(filename);			// creates an input stream
        int song_count = 0;			// for progress indicator
	string artist, title, word;		// data from the file

	// -- While more data to read...
	while ( ! in.eof() ) 
	{
		Song* temp = new Song;
		temp->trie = new Trie;
		// -- First line is the artist
		getline(in, artist);
		if (in.fail()) break;
		temp->artist = artist;
		// -- Second line is the title
		getline(in, title);
		if (in.fail()) break;
		temp->title = title;

		if ( show_progress )
		{
			song_count++;
			if (song_count % 10000 == 0) {
				cout << "At "       << song_count << 
					" Artist: " << artist     << 
					" Title:"   << title << endl;
			}
		}
		// -- Then read all words until we hit the 
		// -- special <BREAK> token
		while ( in >> word && word != "<BREAK>" ){
			//
			// -- Found a word
			temp->lyrics.push_back(word); //add lyrics to vector in song struct
			temp->trie->addWord(stripword(word));//adds a lyric to the trie
		}
		// -- Important: skip the newline left behind
		in.ignore();
		SongDB.push_back(temp); //puts a pointer to a song struct into 
	}				//a vector of song struct pointers
	
}
//Function iterates through the vector of song pointers and checkes to see if the 
//striped word is located inside of the song. If it is then the pointer to that song
//is pushed onto a vector containing pointers to songs where that word is located.  
void songlist::search(string word){
	vector<Song*> list;
	for(size_t t = 0; t < SongDB.size(); t++){
		if (SongDB[t]->trie->searchWord(stripword(word)) == true){
			list.push_back(SongDB[t]);
		}
	}
	topTen(list, word);
}
//Function takes in the list vector that contains pointers to songs that contain the 
//searched word. Then uses an insertion sort to sort the vector so that songs that
//have the word more frequently are in the front.  Afterwards the sorted array is sent
//to the print function so that it can print the sorted list (if there are less then 
//10 songs with the woord) or a Topten vector which contains the top ten songs where
//the word appears the most.  
void songlist::topTen(vector<Song*> list, string word){
	string SW = stripword(word);
	bool switched = false;
	vector<Song*> Topten;
	Song *temp;
	if (list.size() != 0){
	for(size_t i = 1; i < list.size(); i++){
		if (list[i]->trie->getfreq(SW) > list[i-1]->trie->getfreq(SW)){
			switched = true;
			while(switched == true){
				for(size_t j = i; j > 0; j--){
					if (list[j]->trie->getfreq(SW)  >= 
						list[j-1]->trie->getfreq(SW)){
						temp = list[j];
						list[j] = list[j-1];
						list[j-1] = temp;
					}
					else { switched = false;}		
				}
			}
		}
	}
	}
	
	if(list.size() < 10){         //If list is under 10 songs
		print(list, word);
		list.clear();

	}
	else {
		for (int q = 0; q < 10; q++){
			Topten.push_back(list[q]);  //If list is over 10 songs
		}
			print(Topten, word);
			Topten.clear();
	
	}
}
//The Function gets passed a vector of song pointers as well as the word
//being searched for.  It then iterates through the vector of lyrics in
//each song and for every instance that the word in the lyrics matches the
//search word it prints out the 5 lyrics before the word as well as the 5 
//lyrics after.  IF there are not 5 lyrics before or after, it just prints
//out as many as possible. 
void songlist::print(vector<Song*> Topten, string word){
	for(size_t i = 0; i <Topten.size(); i++){
		for(size_t k = 0; k < Topten[i]->lyrics.size(); k++){
			if (stripword(word) == stripword(Topten[i]->lyrics[k])){
				cout <<endl;
				cout <<endl;
				cout << "Title : " << Topten[i]->title << endl;
				cout << "Artist : " << Topten[i]->artist << endl;
				cout << "Context : ";
				if(k < 5){
					for(size_t j = 0; j < k; j++){
						cout << Topten[i]->lyrics[j] << " ";
					}
				}                                           //words before
				else{                             
					for(size_t l = k-5; l < k; l++){
						cout << Topten[i]->lyrics[l] << " ";
					}
				}
				cout << Topten[i]->lyrics[k] << " ";       //word itself
				if(Topten[i]->lyrics.size() - k-1 < 5 ){
					for(size_t h = k+1; h < Topten[i]->lyrics.size(); h++){
						cout << Topten[i]->lyrics[h] << " ";
					}
				}                                        //words after
				else{
					for(size_t z = k+1; z < k+6; z++){
						cout << Topten[i]->lyrics[z] << " ";
					}
				}
			}
		}
	}
	cout << endl;
}

