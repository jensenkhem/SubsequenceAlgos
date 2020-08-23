
#include "lps.h"
// Longest Palindrome subsequence code!
void LPS(char sequence1[], struct retValues s) {
	//Reverse the sequence and store result into another string
	char reversed[strlen(sequence1)];
	int index = 0;
	for(int i = strlen(sequence1) - 1; i >= 0; i--) {
		reversed[index] = sequence1[i];
		index++;
	}
	// Compute the LCS of the original sequence and its reversed self -> LPS
	LCS(sequence1, reversed, true, false, false, s);
	return;
}

void LCPS(char sequence1[], char sequence2[], struct retValues s) {

	//Case for empty string

	if(strlen(sequence1) == 0 || strlen(sequence2) == 0) {
		printf("# an LCPS (length = 0) is:\n");
		writeToOutputFile(s, "# an LCPS (length = 0) is: ");
		writeToOutputFile(s, "\n");
		return;
	}

	//Take the LCS of both sequences and their reversed counterparts
	char reversed1[strlen(sequence1)];
	char reversed2[strlen(sequence2)];
	int index = 0;
	for(int i = strlen(sequence1) - 1; i >= 0; i--) {
		reversed1[index] = sequence1[i];
		index++;
	}
	index = 0;
	for(int i = strlen(sequence2) - 1; i >= 0; i--) {
		reversed2[index] = sequence2[i];
		index++;
	}
	LCS_four(sequence1, reversed1, sequence2, reversed2, false, true, false, s);
	return;
}