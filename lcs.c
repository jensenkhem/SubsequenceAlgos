#include "lcs.h"
//#define MAX_LENGTH 10000

// Longest common subsequence code!
int LCS(char sequence1[], char sequence2[], bool lps, bool lts, bool donelts, struct retValues s) {

	int rows = strlen(sequence1) + 1;
	int columns = strlen(sequence2) + 1;
	int *length_table[rows];

	//Allocate memory for the LCS function length table!
	for(int i = 0; i < rows; i++) {
		length_table[i] = (int*)calloc(columns, sizeof(int));
	}

	//Initialize all starting values of the table as zeroes, with one extra row and column

	int aboveValue, leftValue;

	for(int i = 0; i < strlen(sequence1); i++) {
		for(int j= 0; j < strlen(sequence2); j++) {
			//If the two letters are the same, add one to the maximum and store in the table
			if(sequence1[i] == sequence2[j]) {
				length_table[i + 1][j + 1] = length_table[i][j] + 1;
			}
			else {
				// Set the spot in the length table to the max of table[i - 1][j] and table[i][j - 1]
				aboveValue = length_table[i][j + 1];
				leftValue = length_table[i + 1][j];
				if(aboveValue >= leftValue) length_table[i + 1][j + 1] = aboveValue;
				else {
					length_table[i + 1][j + 1] = leftValue;
				}
			}
		}
	}

	// Now print the character representation of the LCS

	//i = row position, j = column position --> Starting from the end of the length table
	if(!lts || donelts) {
		int i = rows - 1;
		int j = columns - 1;

		int counter = length_table[i][j]; // Set starting index to the max length of the LCS

		char lcs[counter + 1]; //Create a character array with enough size to fit the LCS + null terminator

		while(i > 0 && j > 0) {
			//If the current character is the same in sequence1/2, add it to the lcs array and move diagnolly left in length table
			if(sequence1[i - 1] == sequence2[j - 1]) { 
				lcs[counter] = sequence1[i - 1];
				counter--;
				i-=1;
				j-=1;
			}

			//If the characters arent the same, move in direction of max value

			else if(length_table[i][j-1] < length_table[i-1][j]) i-=1; 

			else j -= 1;

		}



		//Print the LCS from the character array
		if(!lps && !donelts) {
			printf("# an LCS (length = %d) is:\n", length_table[rows - 1][columns- 1]);
			char tempWords1[100] = "# an LCS (length = ";
			char tempWords2[100] = ") is: ";
			char temp[5];
			sprintf(temp, "%d", length_table[rows - 1][columns- 1]);
			strcat(tempWords1, temp);
			strcat(tempWords1, tempWords2);
			writeToOutputFile(s, tempWords1);
			writeToOutputFile(s, "\n");
		}
		else if(lps && length_table[rows - 1][columns- 1]  < 2 && !donelts) {
			printf("# an LPS (length = 0) for the first sequence is:\n");
			writeToOutputFile(s, "# an LPS (length = 0) for the first sequence is: ");
			writeToOutputFile(s, "\n");
			writeToOutputFile(s, "\n");
			//Free allocatted memory
			for(int i = 0; i < rows; i++) {
				free(length_table[i]);
			}
			return 0;
		}
		else if(donelts) {
			printf("# an LTS (length = %d) for the first sequence is:\n", length_table[rows - 1][columns- 1] * 2);
			char tempWords1[100] = "# an LTS (length = ";
			char tempWords2[100] = ") for the first sequence is: ";
			char temp[5];
			sprintf(temp, "%d", length_table[rows - 1][columns- 1] * 2);
			strcat(tempWords1, temp);
			strcat(tempWords1, tempWords2);
			writeToOutputFile(s, tempWords1);
			writeToOutputFile(s, "\n");
			if(length_table[rows - 1][columns- 1] == 0) {
				printf("\n");
				writeToOutputFile(s, "\n");
				for(int i = 0; i < rows; i++) {
					free(length_table[i]);
				}
				return 0;
			}
			char ltsHalf1[sizeof(lcs)];
			for(int i = 1; i < sizeof(lcs); i++) {
				printf("%c", lcs[i]);
				ltsHalf1[i - 1] = lcs[i];
			}
			for(int i = 1; i < sizeof(lcs); i++) {
				printf("%c", lcs[i]);
				ltsHalf1[i - 1] = lcs[i];
			}
			writeToOutputFile(s, ltsHalf1);
			writeToOutputFile(s, ltsHalf1);
			writeToOutputFile(s, "\n");
			writeToOutputFile(s, "\n");
			/*
			char lcsOutput[sizeof(lcs)];
			for(int i = 1; i < sizeof(lcs); i++) {
				printf("%c", lcs[i]);
				lcsOutput[i - 1] = lcs[i];
			}
			
			writeToOutputFile(s, lcsOutput);
			
			char ltsHalf2[sizeof(lcs)];
			for(int i = 1; i < sizeof(lcs); i++) {
				printf("%c", lcs[i]);
				ltsHalf2[i - 1] = lcs[i];
			}
			*/
			printf("\n");

			int last = length_table[rows - 1][columns - 1];

			for(int i = 0; i < rows; i++) {
				free(length_table[i]);
			}

			return last;

		}
		else {
			printf("# an LPS (length = %d) for the first sequence is:\n", length_table[rows - 1][columns- 1]);
			char tempWords1[100] = "# an LPS (length = ";
			char tempWords2[100] = ") for the first sequence is: ";
			char temp[5];
			sprintf(temp, "%d", length_table[rows - 1][columns- 1]);
			strcat(tempWords1, temp);
			strcat(tempWords1, tempWords2);
			writeToOutputFile(s, tempWords1);
			writeToOutputFile(s, "\n");
		}

		// Check if the LCS length is zero! -> If so, print nothing and terminate the program

		if(length_table[rows - 1][columns- 1] == 0) {
			printf("\n");
			writeToOutputFile(s, "\n");
			for(int i = 0; i < rows; i++) {
				free(length_table[i]);
			}
			return 0;
		}

		char lcsOutput[sizeof(lcs)];
		for(int i = 1; i < sizeof(lcs); i++) {
			printf("%c", lcs[i]);
			lcsOutput[i - 1] = lcs[i];
		}
		lcsOutput[sizeof(lcs) - 1] = '\0';

		//for(int j = 0; j < sizeof(lcs))
		//printf("\nLCS OUTPUT: %s\n", lcsOutput);

		writeToOutputFile(s, lcsOutput);
		writeToOutputFile(s, "\n");
		writeToOutputFile(s, "\n");

		printf("\n");
		int last = length_table[rows - 1][columns - 1];
		for(int i = 0; i < rows; i++) {
			free(length_table[i]);
		}
		return last;
	}
	int last = length_table[rows - 1][columns - 1];
	for(int i = 0; i < rows; i++) {
		free(length_table[i]);
	}
	return last;
}



int LCS_four(char s1[], char s2[], char s3[], char s4[], bool lts, bool lps, bool donelts, struct retValues s) {

	// Get the lengths of the 4 sequences
	int d1 = strlen(s1) + 1;
	int d2 = strlen(s2) + 1;
	int d3 = strlen(s3) + 1;
	int d4 = strlen(s4) + 1;

	//Allocate memory for the table
	int *length_table[d1][d2][d3];

	for(int i = 0; i < d1; i++) {
		for(int j = 0; j < d2; j++) {
			for(int k = 0; k < d3; k++) {
				length_table[i][j][k] = (int*)calloc(d4, sizeof(int));
			}
		}
	}

	// Main loops for Dynamic programming LCS
	for(int i = 0; i < strlen(s1); i++) {
		for(int j = 0; j < strlen(s2); j++) {
			for(int k = 0; k < strlen(s3); k++) {
				for(int l = 0; l < strlen(s4); l++) {
					if(s1[i] == s2[j] && s2[j] == s3[k] && s3[k] == s4[l]) {
						length_table[i + 1][j + 1][k + 1][l + 1] = length_table[i][j][k][l] + 1;
					}
					
					else {
						// Set the spot in the length table to the max of all 4 directions
						int val1 = length_table[i][j + 1][k + 1][l + 1];
						int val2 = length_table[i + 1][j][k + 1][l + 1];
						int val3 = length_table[i + 1][j + 1][k][l + 1];
						int val4 = length_table[i + 1][j + 1][k + 1][l];

						if(val1 >= val2 && val1 >= val3 && val1 >= val4) 
							length_table[i + 1][j + 1][k + 1][l + 1] = val1;

						else if(val2 >= val1 && val2 >= val3 && val2 >= val4) 
							length_table[i + 1][j + 1][k + 1][l + 1] = val2;

						else if(val3 >= val2 && val3 >= val1 && val3 >= val4) 
							length_table[i + 1][j + 1][k + 1][l + 1] = val3;

						else if(val4 >= val1 && val4 >= val2 && val4 >= val3) 
							length_table[i + 1][j + 1][k + 1][l + 1] = val4;
					}
				}
			}
		}
	}

	// Here we would do the backtracking to get the actual lcs!
	int i = d1 - 1;
	int j = d2 - 1;
	int k = d3 - 1;
	int l = d4 - 1;

	int lcsLen = length_table[i][j][k][l];
	if(lts && !donelts) {
		//Free memory
		for(int i = 0; i < d1; i++) {
			for(int j = 0; j < d2; j++) {
				for(int k = 0; k < d3; k++) {
					free(length_table[i][j][k]);
				}
			}
		}
		return lcsLen;
	}

	int counter = length_table[i][j][k][l];

	char lcs[counter + 1]; //Create a character array with enough size to fit the LCS + null terminator

		while(i > 0 && j > 0 && k > 0 && l > 0) {
			int val1 = length_table[i-1][j][k][l];
			int val2 = length_table[i][j-1][k][l];
			int val3 = length_table[i][j][k-1][l];
			int val4 = length_table[i][j][k][l-1];
			//If the current character is the same in sequence1/2/3/4, add it to the lcs array and move diagnolly left in length table
			if(s1[i - 1] == s2[j - 1] && s2[j - 1] == s3[k - 1] && s3[k - 1] == s4[l - 1]) { 
				lcs[counter] = s1[i - 1];
				counter--;
				i-=1;
				j-=1;
				k-=1;
				l-=1;
			}

			//If the characters arent the same, move in direction of max value

			else if(val1 >= val2 && val1 >= val3 && val1 >= val4) i-=1;
			else if(val2 >= val1 && val2 >= val3 && val2 >= val4) j-=1;
			else if(val3 >= val2 && val3 >= val1 && val3 >= val4) k-=1;
			else if(val4 >= val2 && val4 >= val3 && val4 >= val1) l-=1;

		}

		lcs[sizeof(lcs)] = '\0';

		//Case for LCPS

		if(s.argFlags[5] && lps) {
			printf("# an LCPS (length = %d) is:\n", lcsLen);
			
			char tempWords1[100] = "# an LCPS (length = ";
			char tempWords2[100] = ") is: ";
			char temp[5];
			sprintf(temp, "%d", lcsLen);
			strcat(tempWords1, temp);
			strcat(tempWords1, tempWords2);
			writeToOutputFile(s, tempWords1);
			writeToOutputFile(s, "\n");

			char* lcsOutput = lcs + 1;
			for(int index = 1; index < strlen(lcs); index++) {
				printf("%c", lcs[index]);
			}

			writeToOutputFile(s, lcsOutput);
			writeToOutputFile(s, "\n");
			writeToOutputFile(s, "\n");
			printf("\n");
	
		}

		//Case for LCTS

		if(s.argFlags[6] && lts && donelts) {
			printf("# an LCTS (length = %d) is:\n", (lcsLen * 2));
			
			char tempWords1[100] = "# an LCTS (length = ";
			char tempWords2[100] = ") is: ";
			char temp[5];
			sprintf(temp, "%d", lcsLen * 2);
			strcat(tempWords1, temp);
			strcat(tempWords1, tempWords2);
			writeToOutputFile(s, tempWords1);
			writeToOutputFile(s, "\n");

			char* lcsOutput = lcs + 1;
			for(int index = 1; index < strlen(lcs); index++) {
				printf("%c", lcs[index]);
			}
			for(int index = 1; index < strlen(lcs); index++) {
				printf("%c", lcs[index]);
			}

			writeToOutputFile(s, lcsOutput); //First half
			writeToOutputFile(s, lcsOutput); //Second half
			writeToOutputFile(s, "\n");
			writeToOutputFile(s, "\n");
			printf("\n");
		}

	//Free memory
	for(int i = 0; i < d1; i++) {
		for(int j = 0; j < d2; j++) {
			for(int k = 0; k < d3; k++) {
				free(length_table[i][j][k]);
			}
		}
	}
	return 1;

}