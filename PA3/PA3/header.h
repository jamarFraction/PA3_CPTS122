/*******************************************************************************************
* Programmer: Jamar Fraction                                                               *
* Class: CptS 122, Fall  2017; Lab Section 05											   *
* Programming Assignment: PA3															   *
* Date: September 14, 2017                                                                 *
* Description:This program fulfills the requirements for the second programming assignment *
********************************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <windows.h>

typedef struct duration {

	int minutes;
	int seconds;

} Duration;

typedef struct record {

	/*Artist – a string
	Album title – a string
	Song title – a string
	Genre – a string
	Song length - a struct Duration type consisting of seconds and minutes, both integers
	Number times played – an integer
	Rating – an integer(1 – 5)*/

	char artist[50];
	char albumTitle[50];
	char songTitle[50];
	char genre[10];
	Duration songLength;
	int numberOfPlays;
	int rating;

} Record;

typedef struct node {

	Record data;
	struct Node *next;
	struct Node *previous;


} Node;

int songsInLibrary;

/*************************************************************
* Function: makeNode
* Input parameters: Record passedRecord
* Returns: A pointer to a Node* type
*************************************************************/
Node *makeNode(Record passedRecord);

/*************************************************************
* Function: processLine
* Input parameters: char line[]
* Returns: A struct of type Record
*************************************************************/
Record processLine(char line[]);

/*************************************************************
* Function: calculatprocessDurationeAverageHeartRate
* Input parameters: char* stringDuration
* Returns: A struct of type Duration
*************************************************************/
Duration processDuration(char* stringDuration);

/*************************************************************
* Function: insertSong
* Input parameters: Node **list, Record songRecord
* Returns: nothing
*************************************************************/
void insertSong(Node **list, Record songRecord);

/*************************************************************
* Function: store
* Input parameters: Node *list, FILE *outfile
* Returns: nothing
*************************************************************/
void store(Node *list, FILE *outfile);

/*************************************************************
* Function: displaySongs
* Input parameters: Node *list
* Returns: nothing
*************************************************************/
void displaySongs(Node *list);

/*************************************************************
* Function: displaySongsByArtist
* Input parameters: Node *list, char* artistName
* Returns: nothing
*************************************************************/
void displaySongsByArtist(Node *list, char* artistName);

/*************************************************************
* Function: editSongByArtist
* Input parameters: Node **list, char* artistName
* Returns: nothing
*************************************************************/
void editSongByArtist(Node **list, char* artistName);

/*************************************************************
* Function: editRatingByArtist
* Input parameters: Node **list, char* artistName
* Returns: nothing
*************************************************************/
void editRatingByArtist(Node **list, char* artistName);

/*************************************************************
* Function: playLibrary
* Input parameters: Node *list
* Returns: Nothing
*************************************************************/
void playLibrary(Node *list);

/*************************************************************
* Function: createSong
* Input parameters: Node **list
* Returns: Nothing
*************************************************************/
void createSong(Node **list);

/*************************************************************
* Function: deleteFromList
* Input parameters: Node **list, char* songTitle
* Returns: Nothing
*************************************************************/
void deleteFromList(Node **list, char* songTitle);

/*************************************************************
* Function: sortSubMenu
* Input parameters: Node **list
* Returns: Nothing
*************************************************************/
void sortSubMenu(Node **list);

/*************************************************************
* Function: sortBasedOnArtist
* Input parameters: Node **list, int numOfSongs
* Returns: Nothing
*************************************************************/
void sortBasedOnArtist(Node **list, int numOfSongs);

/*************************************************************
* Function: sortBasedOnAlbum
* Input parameters: Node **list, int numOfSongs
* Returns: Nothing
*************************************************************/
void sortBasedOnAlbum(Node **list, int numOfSongs);

/*************************************************************
* Function: sortBasedOnRating
* Input parameters: Node **list, int numOfSongs
* Returns: Nothing
*************************************************************/
void sortBasedOnRating(Node **list, int numOfSongs);

/*************************************************************
* Function: sortBasedOnPlays
* Input parameters: Node **list, int numOfSongs
* Returns: Nothing
*************************************************************/
void sortBasedOnPlays(Node **list, int numOfSongs);

/*************************************************************
* Function: generateRandomArray
* Input parameters: int songsInLibrary
* Returns: a pointer to the beginning of a integer array
*************************************************************/
int *generateRandomArray(int songsInLibrary);

/*************************************************************
* Function: shuffle
* Input parameters: Node *list
* Returns: Nothing
*************************************************************/
void shuffle(Node *list);

/*************************************************************
* Function: printShuffledList
* Input parameters: int randomArray[], Node *list
* Returns: Nothing
*************************************************************/
void printShuffledList(int randomArray[], Node *list);
