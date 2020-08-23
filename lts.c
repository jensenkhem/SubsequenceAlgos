#include "lts.h"

// Longest tanddem subsequence code!!
void LTS(char sequence[], struct retValues s) {

	//Base cases

	if(strlen(sequence) == 0) {
		printf("# an LTS (length = 0) for the first sequence is:\n");
		return;
	}

	if(strlen(sequence) == 2) {
		if(sequence[0] == sequence[1]) {
			printf("# an LTS (length = 2) for the first sequence is: \n%c%c\n", sequence[0], sequence[1]);
			writeToOutputFile(s, "# an LTS (length = 2) for the first sequence is: ");
			writeToOutputFile(s, "\n");
			writeToOutputFile(s, sequence);
			writeToOutputFile(s, "\n");
			//writeToOutputFile(s, sequence);
			return;
		}
		else {
			printf("# an LTS (length = 0) for the first sequence is:\n");
			return;
		}
	}

	int pivot = 1;
	//printf("This is my pivot: %d\n", pivot);
	int l = strlen(sequence);
	
	//int leftDone = 0;
	//int rightDone = 0;
	int currentMax = 0;
	int maxPivot = 0;
	
	while(pivot < l - 1) {

		char firstHalf[pivot];
		char secondHalf[l - pivot];

		strncpy(firstHalf, sequence, pivot);
		firstHalf[pivot] = '\0';
		strncpy(secondHalf, &sequence[pivot], l - pivot);
		secondHalf[l - pivot] = '\0';

		int templcs = LCS(firstHalf, secondHalf, false, true, false, s);

		if(templcs > currentMax) {
			maxPivot = pivot;
			currentMax = templcs;
		}

		pivot++;

	}

	//Print out the LTS by calculating the LCS of the ideal pivot!
	pivot = maxPivot;
	char firstHalf[pivot];
	char secondHalf[l - pivot];
	strncpy(firstHalf, sequence, pivot);
	firstHalf[pivot] = '\0';
	strncpy(secondHalf, &sequence[pivot], l - pivot);
	secondHalf[l - pivot] = '\0';

	LCS(firstHalf, secondHalf, false, true, true, s);

	return;
}

void LCTS(char sequence1[], char sequence2[], struct retValues s) {
	//Base cases

	if(strlen(sequence1) == 0 || strlen(sequence2) == 0) {
		printf("# an LCTS (length = 0) is:\n");
		writeToOutputFile(s, "# an LCTS (length = 0) is: ");
		writeToOutputFile(s, "\n");
		return;
	}

	int pivot1 = 1;
	int pivot2 = 1;
	//printf("This is my pivot: %d\n", pivot);
	int l1 = strlen(sequence1);
	int l2 = strlen(sequence2);
	
	int currentMax = 0; //Max value for the actual LCTS len
	int maxPivot1 = 1;	// Pivot(s) that nets this max value
	int maxPivot2 = 1;

	while(pivot1 < l1 - 1) {
		pivot2 = 1;
		while(pivot2 < l2 - 1) {
			// Split each sequence into two subsequences divided at the respective pivot

			/*
			printf("\nMAX PIVOT1: %d", maxPivot1);
			printf("\nMAX PIVOT2: %d", maxPivot2);
			printf("\nCURRENT PIVOT1: %d", pivot1);
			printf("\nCURRENT PIVOT2: %d", pivot2);
			*/
			char firstHalf1[pivot1];
			char secondHalf1[l1 - pivot1];
			char firstHalf2[pivot2];
			char secondHalf2[l2 - pivot2];
			// First sequence
			strncpy(firstHalf1, sequence1, pivot1);
			firstHalf1[pivot1] = '\0';
			strncpy(secondHalf1, &sequence1[pivot1], l1 - pivot1);
			secondHalf1[l1 - pivot1] = '\0';
			// Second sequence
			strncpy(firstHalf2, sequence2, pivot2);
			firstHalf2[pivot2] = '\0';
			strncpy(secondHalf2, &sequence2[pivot2], l2 - pivot2);
			secondHalf2[l2 - pivot2] = '\0';

			int templcs = LCS_four(firstHalf1, secondHalf1, firstHalf2, secondHalf2, true, false, false, s);
			//printf("\nLCS LEN: %d\n", templcs);

			if(templcs > currentMax) {
				maxPivot1 = pivot1;
				maxPivot2 = pivot2;
				currentMax = templcs;
			}
			pivot2++;
		}
		pivot1++;
	}

	//Print out the LCTS by calculating the LCS_four of the ideal pivots!

	//Partition the first sequence at the max pivot for that sequence
	char firstHalf1[maxPivot1];
	char secondHalf1[l1 - maxPivot1];
	strncpy(firstHalf1, sequence1, maxPivot1);
	firstHalf1[maxPivot1] = '\0';
	strncpy(secondHalf1, &sequence1[maxPivot1], l1 - maxPivot1);
	secondHalf1[l1 - maxPivot1] = '\0';

	//Partition the second sequence at the max pivot for that sequence
	char firstHalf2[maxPivot2];
	char secondHalf2[l2 - maxPivot2];
	strncpy(firstHalf2, sequence2, maxPivot2);
	firstHalf2[maxPivot2] = '\0';
	strncpy(secondHalf2, &sequence2[maxPivot2], l2 - maxPivot2);
	secondHalf2[l2 - maxPivot2] = '\0';

	//LCS(firstHalf, secondHalf, false, true, true, s);
	LCS_four(firstHalf1, secondHalf1, firstHalf2, secondHalf2, true, false, true, s);

	return;	
}
