#include "utility.h"

#define MAX_LENGTH 10000

//Make sure that the user input is valid!
bool checkValidInput(char sequence[], struct retValues s) {
	for(int i = 0; i < strlen(sequence); i++) {
		if(isdigit(sequence[i]) == 0 && sequence[i] != EOF) {
			printf("Error, non-digit character detected!\n");
			s.validStruct = 0;
			return false;
		}
	}
	return true;
}

//Validate the flagstruct object!
bool validateStruct(struct retValues s) {
	return s.validStruct == 1;
}

//Recieve input from the user for the program
void getUserInput(char sequence1[], char sequence2[], struct retValues s) {
	bool validInput = false;
	while(validInput == false) {
		printf("\nEnter the first sequence: ");
		fgets(sequence1, MAX_LENGTH, stdin);
		sequence1[strlen(sequence1) - 1] = '\0'; //Null terminator
		//Check valid inputs for the entered sequences
		if(checkValidInput(sequence1, s)) {
			printf("Enter the second sequence: ");
			fgets(sequence2, MAX_LENGTH, stdin);
			sequence2[strlen(sequence2) - 1] = '\0';
			if(checkValidInput(sequence2, s)) {
				validInput = true;
				
			}
		}
	}
	return;
}

int readInputFile(char s1[], char s2[], char filename[], struct retValues s) {

	FILE *fp;
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("Error opening file!\n");
		return -1;
	}

	int flag = 0;
	int counter = 0;
	char c;
	while((c != EOF)) {
		c = fgetc(fp);
		if(flag == 0) {
			if(c == '\n') {
				flag = 1;
				s1[counter] = '\0';
				counter = 0;
				continue;
			}
			else {
				s1[counter] = c;
				counter++;
			}
		}
		else {
			if(c == '\n') {
				flag = 2;
				s2[counter] = '\0';
				counter = 0;
				break;
			}
			else {
				s2[counter] = c;
				counter++;
			}
		}
	}

	//printf("\n");
	fclose(fp);
	if(checkValidInput(s1, s) && checkValidInput(s2, s)) {
		if(s1[0] != EOF) {
			//printf("Test");
			printf("This is the string (1) (Length = %ld) that was read: %s", strlen(s1), s1);
			printf("\nThis is the string (2) (Length = %ld) that was read: %s\n\n", strlen(s2), s2);
		}
		else {
			printf("This is the string (1) (Length = 0) that was read: ");
			printf("\nThis is the string (2) (Length = 0) that was read:\n\n ");
		}
	}
	else {
		printf("At least one of the sequences is invalid!\n");
		return -1;
	}
	return 0;
}

int generateSequence(char s1[], char s2[], int writeToFile, char filename[]) {
	FILE *fp;
	fp = fopen(filename, "w");
	srand(time(0)); // Initialize randomness generation

	int l1;
	int l2;

	printf("Enter the lengths of two sequences: ");
	if(scanf("%d%d", &l1, &l2) != 2) {
		printf("Invalid entry!\n");
		fclose(fp);
		return 0; 
	}
	
	//Populate s1

	for(int i = 0; i < l1; i++) {
		int temp = rand() % 10;
		s1[i] = (char) temp + 48;
		char character[1];
		character[0] = s1[i];
		//printf("%c ", s1[i]);
		fputs(character, fp);
	}

	//printf("\n");

	fputs("\n", fp);

	//Populate s2

	for(int i = 0; i < l2; i++) {
		int temp = rand() % 10;
		s2[i] = (char) temp + 48;
		char character[1];
		character[0] = s2[i];
		//printf("%c ", s2[i]);
		fputs(character, fp);
	}

	//printf("\n");
 
	fputs("\n", fp);
	fclose(fp); //Close the file

	if(!writeToFile) {
		remove(filename);
	}

	return 0;
}

//Writes output from the program to a file!
void writeToOutputFile(struct retValues s, char string[]) {
	if(s.argFlags[0]) {
		FILE *fp;
		fp = fopen(s.outputFile, "a");
		if(fp == NULL) {
			printf("\nError opening output file!");
			return;
		}
		else {
			fputs(string, fp);
			//fputs("\n", fp);
			fclose(fp);
		}
	}
	else {
		return;
	}
}

//Define the struct that we are going to return at the end of the function
struct retValues flagStruct;


//Main function for testing purposes ONLY!
struct retValues checkArgs(int argc, char const *argv[], char test1[], char test2[]) {

	//Setup a bunch of helper variables for the utility file as a whole
	int count;
	int gensequence = 0; // Indexes below writted here denote its position in the struct's binary array
	int writeToFile = 0; //0
	int readFromFile = 0; //1
	//int tandem = 0; //2
	//int palindrome = 0; //3
	//int lcs = 0; //4
	//int lcps = 0; //5
	//int lcts = 0; //6

	// Fill the struct's array with zeroes
	for(int i = 0; i < 7; i++) {
		flagStruct.argFlags[i] = 0;
	} 

	// Default file name. We may or may not use this in the final product
	char filename[] = "default.txt";

	// If there ARE any arguments to begin with
	if(argc > 1) {

		// Loop through all of the arguments passed into the function and deal with them
		for(count = 0; count < argc; count++) {
			//Generate random sequence cases!
			if(strcmp(argv[count], "-g") == 0) {
				gensequence = 1;
				//printf("Gensequence: %d\n", gensequence);
				//printf("Count: %d argv[count] = %s\n", count, argv[count]);
				if((++count) < argc && (strcmp(argv[count], "-o") == 0)) {
					//printf("Count: %d argv[count] = %s\n", count, argv[count]);
					writeToFile = 1;
					if((++count) < argc) {
						strcpy(filename, argv[count]);
					}
				}
				//count++;
			}
			//Case for reading from an input file!
			else if(strcmp(argv[count], "-i") == 0) {
				readFromFile = 1;
				flagStruct.argFlags[1] = 1;
				if((++count) < argc) {
					strcpy(filename, argv[count]);
					strcpy(flagStruct.inputFile, argv[count]);
				}
			}

			//Case for tandem;
			else if(strcmp(argv[count], "-t") == 0) {
				//tandem = 1;
				flagStruct.argFlags[2] = 1;
			}

			//Case for palindrome;
			else if(strcmp(argv[count], "-p") == 0) {
				//palindrome = 1;
				flagStruct.argFlags[3] = 1;
			}

			//Case for LCS;
			else if(strcmp(argv[count], "-c") == 0) {
				//lcs = 1;
				flagStruct.argFlags[4] = 1;
			}

			//Case for LCPS;
			else if(strcmp(argv[count], "-cp") == 0) {
				//lcps = 1;
				flagStruct.argFlags[5] = 1;
			}

			//Case for LCTS;
			else if(strcmp(argv[count], "-ct") == 0) {
				//lcts = 1;
				flagStruct.argFlags[6] = 1;
			}

			else if(strcmp(argv[count], "-o") == 0) {
				writeToFile = 1;
				if((++count) < argc) {
					strcpy(flagStruct.outputFile, argv[count]);
					flagStruct.argFlags[0] = 1;
				}
			}
			//Invalid case!!
			else {
				if(count != 0) {
					printf("Invalid argument entered!\nValid arguments:\n");
					printf("-g: To generate a instance consisting of two sequences over the digit alphabet\n");
					printf("-c: To compute an LCS for the two sequences\n");
					printf("-t: To compute an LTS for the input sequence\n");
					printf("-p: To compute an LPS for the input sequence\n");
					printf("-ct: To compute an LCTS for the two input sequences\n");
					printf("-cp: To compute an LCPS for the two input sequences\n");
					printf("-i inputfilename: To read in sequence(s) from the file <inputfilename>\n");
					printf("-o outputfilename: To write all the results into the file <outputfilename>\n");
					flagStruct.validStruct = 0;
					return flagStruct;
				}
			}
		}
	}
	else {
		printf("Invalid argument entered!\nValid arguments:\n");
		printf("-g: To generate a instance consisting of two sequences over the digit alphabet\n");
		printf("-c: To compute an LCS for the two sequences\n");
		printf("-t: To compute an LTS for the input sequence\n");
		printf("-p: To compute an LPS for the input sequence\n");
		printf("-ct: To compute an LCTS for the two input sequences\n");
		printf("-cp: To compute an LCPS for the two input sequences\n");
		printf("-i inputfilename: To read in sequence(s) from the file <inputfilename>\n");
		printf("-o outputfilename: To write all the results into the file <outputfilename>\n");
		flagStruct.validStruct = 0;
		return flagStruct;
	}

	//Testing print statement to make sure values are in their intended states!

	//printf("\ngensequence: %d - writeToFile: %d - filename: %s\n\n", gensequence, writeToFile, filename);

	//Tests for printing out the data inside the struct I am going to return
	/*
	printf("The struct int array: ");
	for(int i = 0; i < 7; i++) {
		printf("%d ", flagStruct.argFlags[i]);
	}
	printf("\nThe input file name (length: %ld) is: %s", strlen(flagStruct.inputFile), flagStruct.inputFile);
	printf("\nThe output file name (length: %ld) is: %s\n", strlen(flagStruct.outputFile), flagStruct.outputFile);
	*/

	if(gensequence) { // The -g tag case
		generateSequence(test1, test2, writeToFile, filename);
		printf("Sequence 1: %s\n", test1);
		printf("Sequence 2: %s\n", test2);

	}
	if(readFromFile) { // The -i tag case
		if(readInputFile(test1, test2, filename, flagStruct) == -1) {
			flagStruct.validStruct = 0;
			return flagStruct;
		}
	}
	// Case for NOT reading input from a file
	else if(!gensequence && !readFromFile){
		if(flagStruct.argFlags[4] || flagStruct.argFlags[5] || flagStruct.argFlags[6])
			getUserInput(test1, test2, flagStruct);
		else {
			bool validInput = false;
			while(validInput == false) {
				printf("\nEnter the input sequence: ");
				fgets(test1, MAX_LENGTH, stdin);
				test1[strlen(test1) - 1] = '\0'; //Null terminator
				if(checkValidInput(test1, flagStruct)) {
					validInput = true;
				}
			}
		//Check valid inputs for the entered sequences
		}
	}

	flagStruct.validStruct = 1;
	return flagStruct;
}

/*
int main(int argc, char const *argv[])
{
	return 0;
}
*/