/*******************************************************************************************
* Programmer: Jamar Fraction                                                               *
* Class: CptS 122, Fall  2017; Lab Section 05											   *
* Programming Assignment: PA3															   *
* Date: September 14, 2017                                                                 *
* Description:This program fulfills the requirements for the second programming assignment *
********************************************************************************************/
#include "header.h"

Node *makeNode(Record passedRecord) {

	//making a doubly linked node
	Node *newNode;

	//allocate memory for the Node
	newNode = (Node *)malloc(sizeof(Node));

	//check if node created successfully
	if (newNode != NULL) {

		//set the data fields
		strcpy(newNode->data.artist, passedRecord.artist);
		strcpy(newNode->data.albumTitle, passedRecord.albumTitle);
		strcpy(newNode->data.songTitle, passedRecord.songTitle);
		strcpy(newNode->data.genre, passedRecord.genre);
		newNode->data.songLength = passedRecord.songLength;
		newNode->data.numberOfPlays = passedRecord.numberOfPlays;
		newNode->data.rating = passedRecord.rating;


		//initialize the next and previous pointers before returning
		newNode->next = NULL;
		newNode->previous = NULL;

	}

	//return the pointer to the newly created node
	return newNode;
}

Record processLine(char line[]) {

	char *currentValue, *currentDuration; 
	char lineCopy[100] = "";
	Record tempRecord;
	char fullName[25];

	//needed for strtod
	char *ptr;

	//int needed for comparison for artist and line length
	int lineLength = strlen(line);

	//preserve the original line by copying the passed line to our local currentLine variable
	strcpy(lineCopy, line);






	//Artist
	//check must be made for artists with FIrst and Last name VS. Single moniker
	//get (or attempt to get) a token with quotation marks
	currentValue = strtok(lineCopy, "\"");

	//Artist goes by a single Moniker
	if (strlen(currentValue) == lineLength) {
		//single moniker name

		//testing
		//Resetting the line for use with strtok
		strcpy(lineCopy, line);

		//grab the single name
		currentValue = strtok(lineCopy, ",");

		//set the artist name

		strcpy(tempRecord.artist, currentValue);
		//tempRecord.artist = currentValue;

	}
	else {
		//Artist goes by a first and last name
		//set the artist name
		strcpy(tempRecord.artist, currentValue);
		//tempRecord.artist = currentValue;
	}





	//Album Title
	//get the album title
	currentValue = strtok(NULL, ",");

	//set the value in the record
	//tempRecord.albumTitle = currentValue;
	strcpy(tempRecord.albumTitle, currentValue);




	//Song Title
	//get the song title
	currentValue = strtok(NULL, ",");

	//set the value in the record
	//tempRecord.songTitle = currentValue;
	strcpy(tempRecord.songTitle, currentValue);



	//Genre
	//get the genre
	currentValue = strtok(NULL, ",");

	//set the value in the record
	//tempRecord.genre = currentValue;
	strcpy(tempRecord.genre, currentValue);



	//Song Length
	//get the song duration
	//different variable being used here so as not to currupt the values
	//Setting the variable here but will not set the value into the record until after plays and rating
	currentDuration = strtok(NULL, ",");




	//Number of Plays
	currentValue = strtok(NULL, ",");

	//set the value in the record after casting (int <--- double)
	tempRecord.numberOfPlays = (int)strtod(currentValue, &ptr);




	//Rating
	//get the rating
	currentValue = strtok(NULL, ",");

	//set the value in the record after casting (int <--- double)
	tempRecord.rating = (int)strtod(currentValue, &ptr);




	//Duration part 2
	//send currentDuration to our processor function
	//set our tempRecord.duration values by setting it's value to 'Duration' type struct that will be returned*/
	tempRecord.songLength = processDuration(currentDuration);



	//return the Record struct
	return tempRecord;
}

Duration processDuration(char* stringDuration) {

	Duration tempDuration;
	int tempMinutes = 0, tempSeconds = 0;
	char *ptr, *stringDurationCOPY;

	char minutes[10];

	//super roundabout way of making it so my original value for duration is not modified
	//shout-out to C
	strcpy(minutes, stringDuration);
	stringDurationCOPY = minutes;

	//add a ":" to the end of the string. This will make tokenizing easier
	strcat(stringDurationCOPY, ":");

	//grab the minutes by casting (int <-- double) the token from stringDuration
	tempMinutes = (int)strtod(strtok(stringDurationCOPY, ":"), &ptr);

	//do the same for setting the seconds
	tempSeconds = (int)strtod(strtok(NULL, ":"), &ptr);

	//set the minutes and seconds values into the tempDuration that will be returned
	tempDuration.minutes = tempMinutes;
	tempDuration.seconds = tempSeconds;

	//return the Duration struct
	return tempDuration;

}

void insertSong(Node **list, Record songRecord) {

	//Node worker variable
	Node *tempNode = NULL;

	//Pointers to be used for insertion
	Node *pExisting = NULL, *pNew = NULL;

	//Create node for insertion
	tempNode = makeNode(songRecord);


	//Inserting into an empty list
	if (*list == NULL) {

		(*list) = tempNode;

		//update song count
		songsInLibrary += 1;
	}
	//Inserting into non-empty list
	else {

		//Set my current pointer to the node in the list
		pExisting = *list;

		//Set my previous pointer to the node we just created
		pNew = tempNode;

		//Update the new pointer's 'next' to the existing node
		pNew->next = pExisting;

		//Update the existing item in the list's 'previous' pointer to the new node
		pExisting->previous = pNew;

		//Update the new pointer's "previous" to NULL (should be already set by default, but just being extra careful
		pNew->previous = NULL;

		//Set the list to point to the newest node in the list
		*list = pNew;

		//update song count
		songsInLibrary += 1;

	}

}

void store(Node *list, FILE *outfile) {

	char* currentValue;
	char artistFullName[50];
	char* artistFirstName;
	char* artistLastName;


	//if the list is empty then there's nothing to write to the file
	if (list != NULL) {

		//Loop ---> through the list until you get to the "front"
		while (list->next != NULL) {

			list = list->next;

		}


		//list is now at the "front"
		//loop backwards until you are back at the "end" of the list
		//EX: <--- Looping this way
		while (list != NULL) {

			//single moniker
			if (strstr(list->data.artist, ",") == NULL) {

				//print to file
				fprintf(outfile, "%s,%s,%s,%s,%d:%d,%d,%d", list->data.artist, list->data.albumTitle, list->data.songTitle, list->data.genre,
					list->data.songLength.minutes, list->data.songLength.seconds, list->data.numberOfPlays, list->data.rating);
			}
			else {
				//first and last name

				//make a copy of the artist's name but add a comma a the end
				//this will make tokenization easier
				strcpy(artistFullName, list->data.artist);
				strcat(artistFullName, ",");

				//use strtok to seperate the first and last names
				artistLastName = strtok(artistFullName, ",");
				artistFirstName = strtok(NULL, ",");

				//print to file
				fprintf(outfile, "\"%s,%s\",%s,%s,%s,%d:%d,%d,%d", artistLastName, artistFirstName, list->data.albumTitle, list->data.songTitle, list->data.genre,
					list->data.songLength.minutes, list->data.songLength.seconds, list->data.numberOfPlays, list->data.rating);

			}

			//Prevents there being a newline character at the end of the file
			if (list->previous != NULL) {

				fprintf(outfile, "\n");

			}

			//advance to the next in the list
			list = list->previous;

		}
	}

}

void displaySongs(Node *list) {

	printf("Songs List:\n\n");

	//Loop through the linked list and print the details of each record
	while (list != NULL) {
		printf("Artist: %s\nSong Title: %s\nAlbum Title: %s\nDuration: %d:%d\nGenre: %s\nNumber of Plays: %d\nRating: %d\n\n",
			list->data.artist, list->data.songTitle, list->data.albumTitle, list->data.songLength.minutes, list->data.songLength.seconds,
			list->data.genre, list->data.numberOfPlays, list->data.rating);

		//move to the next item in the list
		list = list->next;
	}

}

void displaySongsByArtist(Node *list, char* artistName) {

	int count = 0;

	printf("Songs by %s: \n\n", artistName);

	//Loop through the linked list and print the details of each record
	while (list != NULL) {

		//comparing the name name of the artist in the data set to the passed in string of the artist
		if (strcmp(list->data.artist, artistName) == 0) {

			printf("Artist: %s\nSong Title: %s\nAlbum Title: %s\nDuration: %d:%d\nGenre: %s\nNumber of Plays: %d\nRating: %d\n\n",
				list->data.artist, list->data.songTitle, list->data.albumTitle, list->data.songLength.minutes, list->data.songLength.seconds,
				list->data.genre, list->data.numberOfPlays, list->data.rating);

			count += 1;
		}


		//move to the next item in the list
		list = list->next;
	}

	if (count == 0) {

		printf("No songs by: %s found\n", artistName);

	}

}

void editSongByArtist(Node **list, char* artistName) {

	//varibles to be used to enter new song record information
	char charNewValue[50] = "";
	int intNewValue = 0;

	//Boolean to keep track of there being a change made
	bool changeMade = false;

	//Head pointer, will point to the first Node in the list
	Node *headPtr;

	int option = 0, count = 0;

	//Set the head pointer to the first Node in the list so as not to lose track of it after edit
	headPtr = *list;

	//Loop through the linked list and print the details of each record
	while ((*list) != NULL || option != 1) {

		//comparing the name name of the artist in the data set to the passed in string of the artist
		if (strcmp((*list)->data.artist, artistName) == 0) {

			printf("Artist: %s\nSong Title: %s\nAlbum Title: %s\nDuration: %d:%d\nGenre: %s\nNumber of Plays: %d\nRating: %d\n\n",
				(*list)->data.artist, (*list)->data.songTitle, (*list)->data.albumTitle, (*list)->data.songLength.minutes, (*list)->data.songLength.seconds,
				(*list)->data.genre, (*list)->data.numberOfPlays, (*list)->data.rating);


			do {
				//Prompt user for edit
				//1 = Yes, 2 = No

				printf("Would you like to edit this record? (1 = Yes, 2 = No) ");
				scanf("%d", &option);


			} while (option != 1 && option != 2);

			//User entered 1, so we will proceed with edit
			if (option == 1) {

				//prompting user for which field to edit
				do {

					system("cls");

					//Print the song information
					printf("Artist: %s\nSong Title: %s\nAlbum Title: %s\nDuration: %d:%d\nGenre: %s\nNumber of Plays: %d\nRating: %d\n\n",
						(*list)->data.artist, (*list)->data.songTitle, (*list)->data.albumTitle, (*list)->data.songLength.minutes, (*list)->data.songLength.seconds,
						(*list)->data.genre, (*list)->data.numberOfPlays, (*list)->data.rating);

					printf("\nPlease enter a selection for the field you would like to edit:\n(1.) Artist\n(2.) Song Title\n(3.) Genre\n(4.) Rating\n");
					scanf("%d", &option);


				} while (option < 1 || option > 4);

				//clear the screen
				system("cls");

				//Edit the field selected
				switch (option) {

				case 1:
					//Artist
					//get the value to be inserted into the record
					printf("Current entry: %s\nPlease enter the new information: ", (*list)->data.artist);
					scanf(" %[^\n]s", &charNewValue);

					//copy the new information
					strcpy((*list)->data.artist, charNewValue);
					changeMade = true;

					break;
				case 2:
					//Song Title
					//get the value to be inserted into the record
					printf("Current entry: %s\nPlease enter the new information: ", (*list)->data.songTitle);
					scanf(" %[^\n]s", &charNewValue);

					//copy the new information
					strcpy((*list)->data.songTitle, charNewValue);
					changeMade = true;

					break;

				case 3:
					//Genre
					//get the value to be inserted into the record
					printf("Current entry: %s\nPlease enter the new information: ", (*list)->data.genre);
					scanf(" %[^\n]s", &charNewValue);

					//copy the new information
					strcpy((*list)->data.genre, charNewValue);
					changeMade = true;

					break;

				case 4:
					//Rating
					//get the value to be inserted into the record
					//Loop until a valid entry is received
					do {
						system("cls");

						printf("Current entry: %d\nPlease enter the new information: ", (*list)->data.rating);
						scanf("%d", &intNewValue);

					} while (intNewValue < 1 || intNewValue > 5);


					//copy the new information
					(*list)->data.rating = intNewValue;
					changeMade = true;

					break;

				default:

					printf("Invalid Selection");

				}

				//display the song record again reflecting the change
				system("cls");
				printf("Song information reflecting change made:\n");

				//Print the song information
				printf("Artist: %s\nSong Title: %s\nAlbum Title: %s\nDuration: %d:%d\nGenre: %s\nNumber of Plays: %d\nRating: %d\n\n",
					(*list)->data.artist, (*list)->data.songTitle, (*list)->data.albumTitle, (*list)->data.songLength.minutes, (*list)->data.songLength.seconds,
					(*list)->data.genre, (*list)->data.numberOfPlays, (*list)->data.rating);

			}
			//Add to the count of records with this artist name
			count += 1;


		}


		//if a change has been made, end the looping through possible song entries here 
		if (changeMade == true || (*list)->next == NULL) {

			break;
		}

		//move to the next item in the list
		*list = (*list)->next;

	}


	//Display message that no songs matched the search criteria
	if (count == 0) {

		printf("\nThere were no songs that matched the search criteria\n");

	}

	//Display message that no changes were made
	if (changeMade == false) {

		printf("\nThere were no changes made to any song records\n");

	}


	//reset the list to the pointer to the lead node
	*list = headPtr;


}

void editRatingByArtist(Node **list, char* artistName) {

	//varible to be used to enter new rating
	int intNewValue = 0;

	//Boolean to keep track of there being a change made
	bool changeMade = false;

	//Head pointer, will point to the first Node in the list
	Node *headPtr;

	int option = 0, count = 0;

	//Set the head pointer to the first Node in the list so as not to lose track of it after edit
	headPtr = *list;

	//Loop through the linked list and print the details of each record
	while ((*list) != NULL || option != 1) {

		//comparing the name name of the artist in the data set to the passed in string of the artist
		if (strcmp((*list)->data.artist, artistName) == 0) {

			printf("Artist: %s\nSong Title: %s\nAlbum Title: %s\nDuration: %d:%d\nGenre: %s\nNumber of Plays: %d\nRating: %d\n\n",
				(*list)->data.artist, (*list)->data.songTitle, (*list)->data.albumTitle, (*list)->data.songLength.minutes, (*list)->data.songLength.seconds,
				(*list)->data.genre, (*list)->data.numberOfPlays, (*list)->data.rating);


			do {
				//Prompt user for edit
				//1 = Yes, 2 = No

				printf("Would you like to edit this record? (1 = Yes, 2 = No) ");
				scanf("%d", &option);


			} while (option != 1 && option != 2);

			//User entered 1, so we will proceed with edit
			if (option == 1) {

				system("cls");

				//Rating
				//get the value to be inserted into the record
				//Loop until a valid entry is received
				do {
					system("cls");

					printf("Current entry: %d\nPlease enter the new information: ", (*list)->data.rating);
					scanf("%d", &intNewValue);

				} while (intNewValue < 1 || intNewValue > 5);


				//copy the new information
				(*list)->data.rating = intNewValue;
				changeMade = true;


				//display the song record again reflecting the change
				system("cls");
				printf("Song information reflecting change made:\n");

				//Print the song information
				printf("Artist: %s\nSong Title: %s\nAlbum Title: %s\nDuration: %d:%d\nGenre: %s\nNumber of Plays: %d\nRating: %d\n\n",
					(*list)->data.artist, (*list)->data.songTitle, (*list)->data.albumTitle, (*list)->data.songLength.minutes, (*list)->data.songLength.seconds,
					(*list)->data.genre, (*list)->data.numberOfPlays, (*list)->data.rating);

			}
			//Add to the count of records with this artist name
			count += 1;


		}


		//if a change has been made, end the looping through possible song entries here 
		if (changeMade == true || (*list)->next == NULL) {

			break;
		}

		//move to the next item in the list
		*list = (*list)->next;

	}


	//Display message that there were no songs that matched the search criteria
	if (count == 0) {

		printf("\nThere were no songs that matched the search criteria\n");

	}

	//Display message that no changes were made
	if (changeMade == false) {

		printf("\nThere were no changes made to any song records\n");

	}


	//reset the list to the pointer to the lead node
	*list = headPtr;

}

void playLibrary(Node *list) {

	while (list != NULL) {
		printf("Now Playing:\n\n");

		printf("Artist: %s\nSong Title: %s\nAlbum Title: %s\nDuration: %d:%d\nGenre: %s\nNumber of Plays: %d\nRating: %d\n\n",
			list->data.artist, list->data.songTitle, list->data.albumTitle, list->data.songLength.minutes, list->data.songLength.seconds,
			list->data.genre, list->data.numberOfPlays, list->data.rating);

		//increment the number of plays by 1
		list->data.numberOfPlays += 1;

		//move to the next item in the list
		list = list->next;

		//display the song for 3 seconds
		Sleep(3000);

		system("cls");
	}

	system("cls");
}

void createSong(Node **list) {

	//Insert
	//The "insert" command must prompt the user for the details of a new record.
	//The prompt must request the artist name, album title, song title, genre, song length,
	//number of times played, and rating. The new record must be inserted at the front of the list.

	//New Node variables
	char artistName[50];
	char albumTitle[50];
	char songTitle[50];
	char genre[50];
	int currentValue;

	//Record variable for the new Node
	Record newRecord;

	//clear the screen for the insert
	system("cls");

	//Start prompts for new Node information
	printf("Please enter new song's Artist name: \n");


	//Artist
	//Get the new artist's name and store it in the character array
	scanf(" %[^\n]s", &artistName);

	//set the value into the new Node
	strcpy(newRecord.artist, artistName);



	//Album Title
	printf("\nPlease enter %s's album title: \n", artistName);

	//Get the new artist's album title and store it in the character array
	scanf(" %[^\n]s", &albumTitle);

	//set the value into the new Node
	strcpy(newRecord.albumTitle, albumTitle);



	//Song Title
	printf("\nPlease enter the song title on %s: \n", albumTitle);

	//Get the new album's sibg title and store it in the character array
	scanf(" %[^\n]s", &songTitle);

	//set the value into the new Node
	strcpy(newRecord.songTitle, songTitle);



	//Genre
	printf("\nPlease enter the genre of %s: \n", songTitle);

	//Get the new album's sibg title and store it in the character array
	scanf(" %[^\n]s", &genre);

	//set the value into the new Record
	strcpy(newRecord.genre, genre);


	//Song length - minutes
	do {

		printf("\nPlease enter the \"minutes\" value of %s: \n", songTitle);
		scanf("%d", &currentValue);

	} while (currentValue < 0 || currentValue >= 999999999);

	//set the value into the new Record
	newRecord.songLength.minutes = currentValue;



	//Song length - seconds
	do {

		printf("\nPlease enter the \"seconds\" value of %s: \n", songTitle);
		scanf("%d", &currentValue);

	} while (currentValue < 0 || currentValue > 59);

	//set the value into the new Record
	newRecord.songLength.seconds = currentValue;



	//Number of plays
	do {

		printf("\nHow many times have you played %s? \n", songTitle);
		scanf("%d", &currentValue);

	} while (currentValue < 0 || currentValue >= 999999999);
	
	//set the value into the new Record
	newRecord.numberOfPlays = currentValue;



	//Rating
	do {

		printf("\nWhat rating do you give %s? \n", songTitle);
		scanf("%d", &currentValue);

	} while (currentValue < 1 || currentValue > 5);

	//set the value into the new Record
	newRecord.rating = currentValue;


	//Insert the song into the new list (at the front)
	insertSong(list, newRecord);

}

void deleteFromList(Node **list, char* songTitle) {

	//pointers for keeping track of ourplace in the list
	Node *current = NULL, *previous = NULL, *headPointer = NULL;

	bool changeMade = false;

	current = *list;
	headPointer = *list;


	//Loop through the linked list and print the details of each record
	while ((*list) != NULL) {

		//comparing the name name of the song title in the data set to the passed in string of the song title
		if (strcmp((*list)->data.songTitle, songTitle) == 0) {

			//only do this if we are not at the end of the list
			if (current->next != NULL) {

				//every other item in the list (except the first or last)
				//previous cannot be NULL
				if (previous != NULL) {

					//imagine jumping over a box
					previous->next = current->next;

					//point the list pointer to the head Node's pointer
					*list = headPointer;
					
					//free the current pointer
					free(current);

					//update that a change has been made
					songsInLibrary -= 1;
					changeMade = true;

				}
				else {
					
					//removing the first item in the list
					//point the list to the 
					*list = (*list)->next;

					//free the current pointer
					free(current);

					//no dangling pointers!
					headPointer = NULL;

					//update that a change has been made
					songsInLibrary -= 1;
					changeMade = true;
				}
				

				

			}
			else {

				//removing from the end of the list
				previous->next = NULL;

				*list = headPointer;

				free(current);

				songsInLibrary -= 1;
				changeMade = true;

			}
			

			//if there was a change made there is no need to continue through the list
			if (changeMade == true) {

				break;
			}

		}



		//is the next item in the list null?
		if ((*current).next != NULL) {

			//set the previous pointer to the current
			previous = current;

			//move on to the next item in the list
			*list = (*list)->next;

			//make current point to the next item in the list
			current = *list;
		}
		else {
			
			//it is! so we'll just "advance" through the list to get to the end of the loop
			*list = (*list)->next;

		}

	}

	//set the list back to the head pointer
	*list = headPointer;

	if(changeMade == false) {

		
		printf("\"%s\" was not found in your songs list\n", songTitle);

	}
	


}

void sortSubMenu(Node **list) {

	int option = 0;

	//menu for the sort options
	do {

		system("cls");
		//Prompt for the sort preference
		printf("How would you like to sort the songs list?\n1. Sort based on artist (A-Z)\n2. Sort based on album title(A - Z)\n3. Sort based on rating(1 - 5)\n4. Sort based on times played(largest - smallest)\n");
		scanf("%d", &option);


	} while (option < 1 || option > 4);

	//select the method by which a sort will be performed
	if (option == 1) {
		//sort based on artist
		sortBasedOnArtist(list, songsInLibrary);
	}
	else if (option == 2) {
		//Sort based on album title(A - Z)
		sortBasedOnAlbum(list, songsInLibrary);
	}
	else if (option == 3) {
		//Sort based on rating(1 - 5)
		sortBasedOnRating(list, songsInLibrary);

	}else if(option == 4){
		//Sort based on times played(largest - smallest)
		sortBasedOnPlays(list, songsInLibrary);
	}

	do {

		system("cls");
		//Prompt for displaying the sorted songs list
		printf("Songs list sorted. Would you like to display the list? (1 = Yes 2 = No)\n");
		scanf("%d", &option);

	} while (option < 1 || option > 2);

	if (option == 1) {
		displaySongs(*list);
		system("pause");
	}
	

}

void sortBasedOnArtist(Node **list, int numOfSongs) {

	//Pointers to our position in the list
	Node *left = NULL, *right = NULL;

	//Boundary for the inner loop
	int songBoundary = (songsInLibrary - 1);

	//Do not perform if the list is empty
	//Do not perform if there are < 2 Nodes in the list
	if ((*list != NULL) && ((*list)->next != NULL)) {

		//set the left and right pointers to the first two Nodes in the list
		left = *list;
		right = (*list)->next;

		//Initialize our boundary pointer to the list
		//loop through the list until the a Node's next pointer is null
		//once this happens we are at the end of the list and can set the initial boundary

		for (int i = 0; i < songsInLibrary - 1; i++) {

			for (int j = 0; j < songBoundary; j++) {

				//compare the Artist strings, swapping if necessary
				if (strcmp(left->data.artist, right->data.artist) > 0) {

					Node *tempL = left->previous, *tempR = right->next, *tempPTR = right;


					//swap the pointers to the new left and right Nodes
					left = right;
					right = right->previous;

					//swap the pointers in the Nodes
					if (tempL != NULL) {
						//New "left" Node is not at the front of the list
						tempL->next = left;

					}
					else {
						//Node has been swapped to the first position in the list
						//so point the list to our new "left"
						*list = left;

					}

					if (tempR != NULL) {

						//possibly unnecessary, but just trying to be thorough here	
						tempR->previous = right;

					}
					

					//continuing to update the pointers
					left->next = right;
					left->previous = tempL;

					right->previous = left;
					right->next = tempR;
				}



				//move the L and R pointers forward
				Node *temp = right;
				right = right->next;
				left = temp;

			}

			//move the boundary back one Node
			songBoundary -= 1;

			//reset the position of the L and R pointers
			left = *list;
			right = (*list)->next;
		}		

	}
	
}

int *generateRandomArray(int songsInLibrary) {

	//pointer to the beginning of the to-be int array
	int *randomContainer = NULL;

	//malloc enough memory for space for as many songs there are in the library
	randomContainer = (int)malloc((sizeof(int) * songsInLibrary));


	//initialize the array values
	for (int i = 0; i < songsInLibrary; i++) {

		//interate through the array and initialize the values
		//zero-based index
		randomContainer[i] = i;

	}

	//shuffle the array
	for (int j = 0; j < songsInLibrary; j++) {

		int temp = randomContainer[j];
		int randomIndex = rand() % songsInLibrary;

		randomContainer[j] = randomContainer[randomIndex];
		randomContainer[randomIndex] = temp;

	}

	
	return randomContainer;
}

void shuffle(Node *list) {

	//Array of integers that will contain values 0 through songsInLibrary (inclusive)
	//Array will be used to "jump" to different positions songs in the songs list
	int *referenceArrayForRandoms = NULL;

	//assign the values into the reference array via the generateRandomArray function
	referenceArrayForRandoms = generateRandomArray(songsInLibrary);

	//print the shuffled songs list via the printShuffledList function
	printShuffledList(referenceArrayForRandoms, list);

}

void printShuffledList(int randomArray[], Node *list) {

	//count and position integers
	//count will increment by 1 with each printing of a node
	//Current position will change as the index in the array is changed
	//nextPosition will be necessary to determine if there needs to be a movement forward or backwards in the list
	int count = 0, currentPosition = 0, nextPosition = 0, index = 0;

	Node *currentNode = list;
	nextPosition = randomArray[index];

	//start at a certain point in the list, given the random array at position 0 in the random array

	do {

		printf("Now Playing:\n\n");


		//move forward or backwards based on the number in the next index of the random array
		//if the next value in the array is greater than our current position
		if (currentPosition < nextPosition) {


			for (int i = currentPosition; i < nextPosition; i++) {

				//move "forwards"
				currentNode = currentNode->next;
			}
		}
		//if the next value in the array is less than our current position
		else {

			//loop to move backwards in the list to get to the appropriate position in the list
			for (int i = currentPosition; i > nextPosition; i--) {

				//"move backwards"
				currentNode = currentNode->previous;

			 }
		}

		//print the song at the currentNode's position
		printf("Artist: %s\nSong Title: %s\nAlbum Title: %s\nDuration: %d:%d\nGenre: %s\nNumber of Plays: %d\nRating: %d\n\n",
			currentNode->data.artist, currentNode->data.songTitle, currentNode->data.albumTitle, currentNode->data.songLength.minutes, currentNode->data.songLength.seconds,
			currentNode->data.genre, currentNode->data.numberOfPlays, currentNode->data.rating);

		//display the song for 3 seconds
		Sleep(3000);

		system("cls");

		//increment the count and playCount of the current Node
		count += 1; 
		index += 1;
		currentNode->data.numberOfPlays += 1;

		//if the count < songsInLibrary, set the current position to the next position and the
		//next position to index[count ] + 1
		if (count < songsInLibrary) {
			currentPosition = nextPosition;
			nextPosition = randomArray[index];
		}
		

	} while (count < songsInLibrary);


}

void sortBasedOnAlbum(Node **list, int numOfSongs) {

	//Pointers to our position in the list
	Node *left = NULL, *right = NULL;

	//testing
	int songBoundary = (songsInLibrary - 1);


	//Do not perform if the list is empty
	//Do not perform if there are < 2 Nodes in the list
	if ((*list != NULL) && ((*list)->next != NULL)) {

		//set the left and right pointers to the first two Nodes in the list
		left = *list;
		right = (*list)->next;


		for (int i = 0; i < songsInLibrary - 1; i++) {

			for (int j = 0; j < songBoundary; j++) {



				//compare the Artist strings, swapping if necessary
				if (strcmp(left->data.albumTitle, right->data.albumTitle) > 0) {

					Node *tempL = left->previous, *tempR = right->next, *tempPTR = right;


					//swap the pointers to the new left and right Nodes
					left = right;
					right = right->previous;

					//swap the pointers in the Nodes
					if (tempL != NULL) {
						//New "left" Node is not at the front of the list
						tempL->next = left;

					}
					else {
						//Node has been swapped to the first position in the list
						//so point the list to our new "left"
						*list = left;

					}


					//possibly unnecessary, but just trying to be thorough here	
					if (tempR != NULL) {
						//New "right" Node is not at the front of the list
						tempR->previous = right;

					}
					

					//continuing to update the pointers
					left->next = right;
					left->previous = tempL;

					right->previous = left;
					right->next = tempR;
				}

				//move the L and R pointers forward
				Node *temp = right;
				right = right->next;
				left = temp;

			}

			//move the boundary back one Node
			songBoundary -= 1;

			//reset the position of the L and R pointers
			left = *list;
			right = (*list)->next;
		}

	}


}

void sortBasedOnRating(Node **list, int numOfSongs) {

	//Pointers to our position in the list
	Node *left = NULL, *right = NULL;

	//testing
	int songBoundary = (songsInLibrary - 1);


	//Do not perform if the list is empty
	//Do not perform if there are < 2 Nodes in the list
	if ((*list != NULL) && ((*list)->next != NULL)) {

		//set the left and right pointers to the first two Nodes in the list
		left = *list;
		right = (*list)->next;


		for (int i = 0; i < songsInLibrary - 1; i++) {

			for (int j = 0; j < songBoundary; j++) {



				//compare the Artist strings, swapping if necessary
				if (left->data.rating < right->data.rating) {

					Node *tempL = left->previous, *tempR = right->next, *tempPTR = right;


					//swap the pointers to the new left and right Nodes
					left = right;
					right = right->previous;

					//swap the pointers in the Nodes
					if (tempL != NULL) {
						//New "left" Node is not at the front of the list
						tempL->next = left;

					}
					else {
						//Node has been swapped to the first position in the list
						//so point the list to our new "left"
						*list = left;

					}


					//possibly unnecessary, but just trying to be thorough here	
					if (tempR != NULL) {
						//New "right" Node is not at the front of the list
						tempR->previous = right;

					}


					//continuing to update the pointers
					left->next = right;
					left->previous = tempL;

					right->previous = left;
					right->next = tempR;
				}

				//move the L and R pointers forward
				Node *temp = right;
				right = right->next;
				left = temp;

			}

			//move the boundary back one Node
			songBoundary -= 1;

			//reset the position of the L and R pointers
			left = *list;
			right = (*list)->next;
		}

	}

}

void sortBasedOnPlays(Node **list, int numOfSongs) {


	//Pointers to our position in the list
	Node *left = NULL, *right = NULL;

	//testing
	int songBoundary = (songsInLibrary - 1);


	//Do not perform if the list is empty
	//Do not perform if there are < 2 Nodes in the list
	if ((*list != NULL) && ((*list)->next != NULL)) {

		//set the left and right pointers to the first two Nodes in the list
		left = *list;
		right = (*list)->next;


		for (int i = 0; i < songsInLibrary - 1; i++) {

			for (int j = 0; j < songBoundary; j++) {



				//compare the Artist strings, swapping if necessary
				if (left->data.numberOfPlays < right->data.numberOfPlays) {

					Node *tempL = left->previous, *tempR = right->next, *tempPTR = right;


					//swap the pointers to the new left and right Nodes
					left = right;
					right = right->previous;

					//swap the pointers in the Nodes
					if (tempL != NULL) {
						//New "left" Node is not at the front of the list
						tempL->next = left;

					}
					else {
						//Node has been swapped to the first position in the list
						//so point the list to our new "left"
						*list = left;

					}


					//possibly unnecessary, but just trying to be thorough here	
					if (tempR != NULL) {
						//New "right" Node is not at the front of the list
						tempR->previous = right;

					}


					//continuing to update the pointers
					left->next = right;
					left->previous = tempL;

					right->previous = left;
					right->next = tempR;
				}

				//move the L and R pointers forward
				Node *temp = right;
				right = right->next;
				left = temp;

			}

			//move the boundary back one Node
			songBoundary -= 1;

			//reset the position of the L and R pointers
			left = *list;
			right = (*list)->next;
		}

	}

}