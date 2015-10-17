The way that my program works is I store a vector of pointers to song structs. 
Each song struct contains a artist, title, a vector of ltrics, and a trie of 
the lyrics in that song.  
	When a person wants to search for a song they input the word that they 
want to find and it gets run through a search function that first goes through
and creates a vector of songs that contain the word. Then afterwards, a sorting 
algorithm sorts the songs based on the frequency that the word appears, putting
the songs with the highest frequency at the front of the vector.  The last step
of the program is to pass the first ten members of the sorted list to a vector 
called topten and passing that to a print function which, for each usage of the
word in each song, prints out the title, artist, the 5 lyrics before, the word 
you are looking for, and the 5 lyrics after.
	The program is split up into 3 different classes.  A Node class, a trie class,
and a songlist class. The node class and trie class handle storing the lyrics
of a song into a trie so that it is possible to determine whether a word
exists in a song and if it does, how many times.  The Node class represents
the individual nodes of the trie which contain a letter, whether it is marked
as the last letter in a word, the freq, and a vector of its children. The
Trie class just handles the actual inputing of letters into the trie.
	THe last class is the songlist class and it is responsible for
handeling the song information as it is passed in from a text file.  The first
major thing that it does is read in song data and store it correctley.  The
last major thing that it does is find songs based on an input word.  Where the
node class and trie class deal with the under the hood storage of the program,
the songlist class is what the user interacts with.

Overall, this is a very different route then I decided to go in.  At first I
talked with a lot of diferent students and was planning on using a hashtable
but I could not figure out how to make my hash table work so I scrapped it and
decided to go in this direction because I felt much more comfortable using
tries. The idea for the whole set up of this program came after I talked with
fellow student: Chris Rodriguez.
