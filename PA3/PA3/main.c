/*******************************************************************************************
* Programmer: Jamar Fraction                                                               *
* Class: CptS 122, Fall  2017; Lab Section 05											   *
* Programming Assignment: PA3															   *
* Date: September 14, 2017                                                                 *
* Description:This program fulfills the requirements for the second programming assignment *
********************************************************************************************/

#include "header.h"

int main(int argc, char *argv[]) {

	//dataFile, information that will be read into the program/written to the file
	FILE *dataFile = NULL;

	//line and line copy to be used to read in from the dataFile
	char line[100] = "", copyLine[100] = "";

	//Menu control variable
	int option = 0;

	//Pointer to the list
	Node *list = NULL;

	//artist name to be used in searching for records to edit/display
	char artistName[50] = "";

	//song title to be used for searching records to edit/display
	char songTitle[50] = "";

	//open the file for reading and writing
	dataFile = fopen("musicPlayList.csv", "r");


	if (dataFile != NULL) {

		//Start Digital Music Manager
		do {
			option = 0;
			system("cls");

			printf("Digital Music Manager\n");
			printf("MENU\n(1.) Load\n(2.) Store\n(3.) Display\n(4.) Insert\n(5.) Delete\n(6.) Edit\n(7.) Sort\n(8.) Rate\n(9.) Play\n(10.) Shuffle\n(11.) Exit\n");
			//printf("Note: Only current functionality of: (1) load, (2) store, (3) display, (6) edit, (8) rate, (9) play, and (11) exit\n");

			scanf("%d", &option);




			if (option == 1) {
				//(  1  ) Load
				Record tempRecord;

				//while loop needed for reading in all of the data
				//While the end of the file has not been reached, we will continue to loop
				while (!feof(dataFile)) {

					//pull the line into "line" variable from infile
					fgets(line, 100, dataFile);

					//preserve the original line
					strcpy(copyLine, line);

					//pass the line to our processLine function
					//processLine will accept a line as a parameter and return a Record struct
					tempRecord = processLine(copyLine);

					//insert the song record into the list
					insertSong(&list, tempRecord);
				}

				//close the file
				fclose(dataFile);

				printf("\nSongs read in successfully\n");

				system("pause");
			}
			else if (option == 2) {
				//(  2  ) Store
				//The �store� command writes the current records, in the dynamic
				//doubly linked list, to the musicPlayList.csv file. The store will completely
				//overwrite the previous contents in the file.
				dataFile = fopen("musicPlayList.csv", "w");

				//send the pointer to the list and the dataFile to the store function
				store(list, dataFile);

				fclose(dataFile);
			}
			else if (option == 3) {
				//( 3 ) Display

				//Prompt for all songs or only songs by a particular artist
do {
	system("cls");
	printf("Would you like to display all songs or songs by a particular artist?\n");
	printf("(1.) All Songs\n(2.) Songs by Artist (case-sensitive... for now)\n");

	//assing a value to option
	scanf("%d", &option);

} while (option != 1 && option != 2);

if (option == 1) {
	//display all songs
	system("cls");

	//send the pointer to the list to the display function
	displaySongs(list);

	system("pause");

}
else if (option == 2) {

	//Display songs by a certain artist
	printf("What artist name would you like to display songs for?: ");

	//Scan for the name of the artist.. delimeter set to the \n char and not whitespace
	scanf(" %[^\n]s", &artistName);

	//pass the list and art name to the display function
	system("cls");
	displaySongsByArtist(list, artistName);
	system("pause");
}

system("cls");

			}
			else if (option == 4) {
				//Insert
				//The "insert" command must prompt the user for the details of a new record.
				//The prompt must request the artist name, album title, song title, genre, song length,
				//number of times played, and rating. The new record must be inserted at the front of the list.

				//pass the pointer to the list to the create song function
				createSong(&list);

				system("cls");

				//display the song list until user provides input
				displaySongs(list);

				system("pause");

			}
			else if (option == 5) {

				//The �delete� command must prompt the user for a song title, and remove 
				//the matching record from the list. If the song title does not exist, 
				//then the list remains unchanged.


				//Prompt for all songs or only songs by a particular artist

				system("cls");

				printf("Please enter the song title of which will be deleted\n");

				//assign a value to songTitle
				scanf(" %[^\n]s", &songTitle);

				system("cls");

				//pass the song title to the delete function
				deleteFromList(&list, songTitle);

				//Display the new song list
				displaySongs(list);

				system("pause");

			}
			else if (option == 6) {
				//(  6  ) Edit
				system("cls");

				//prompt for artist record to edit
				printf("What is the name of the artist who's song you'd like to edit: ");

				//Scan for the name of the artist.. delimeter set to the \n char and not whitespace
				scanf(" %[^\n]s", &artistName);

				system("cls");

				//pass the list and artist name to search for to the edit function
				editSongByArtist(&list, artistName);

				system("pause");


			}
			else if (option == 7){

				//The �sort� command must prompt the user for 4 different methods to sort the records in the list. These include:
				//1.    Sort based on artist(A - Z)
				//2.    Sort based on album title(A - Z)
				//3.    Sort based on rating(1 - 5)
				//4.    Sort based on times played(largest - smallest)
				//Once a sort method is selected by the user, the sort must be performed on the records in the list.Consider using bubble sort, insertion sort, or selection sort.

				system("cls");

				sortSubMenu(&list);

}
			else if (option == 8) {
				//( 8 ) Rate

				system("cls");

				//prompt for artist record to edit
				printf("What is the name of the artist who's song you'd like to edit: ");

				//Scan for the name of the artist.. delimeter set to the \n char and not whitespace
				scanf(" %[^\n]s", &artistName);

				system("cls");

				//pass the list and artist name to search for to the edit function
				editRatingByArtist(&list, artistName);

				system("pause");


			}
			else if (option == 9) {
				//( 9 ) Play

				system("cls");

				//send the pointer to the list to the play function
				playLibrary(list);
				system("pause");
			}
			else if (option == 10) {

				//clear the screen
				system("cls");

				//pass our list to the shuffle function
				shuffle(list);

				system("pause");


			}
			else if (option == 11) {

				//The �exit� command saves the most recent list to the musicPlayList.csv file.
				//This command will completely overwrite the previous contents in the file

				//open the file for writing
				dataFile = fopen("musicPlayList.csv", "w");

				//send the pointer to the list and the datafile to the store function
				store(list, dataFile);

				//close the file
				fclose(dataFile);
			}
			//end of application
		} while (option != 11);

	}


	return 0;
}