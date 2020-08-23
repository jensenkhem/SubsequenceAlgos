#include "main.h"
#include <time.h>
#define MAX_LENGTH 10000

int main(int argc, char const *argv[]) {

	char sequence1[MAX_LENGTH];
	char sequence2[MAX_LENGTH];
	struct retValues flagStruct = checkArgs(argc, argv, sequence1, sequence2);

	if(!validateStruct(flagStruct)) {
		printf("Exiting...\n");
		return -1;
	}

	//Rest of main code goes here!

	//Determine which functions to run based on the arguments entered!

	//Compute an LTS with the first sequence
	if(flagStruct.argFlags[2]) {
		LTS(sequence1, flagStruct);
		printf("\n");
	}

	//Compute an LPS with the first sequence
	if(flagStruct.argFlags[3]) {
		LPS(sequence1, flagStruct);
		printf("\n");
	}

	//Compute an LCS with the two sequences!
	if(flagStruct.argFlags[4]) {
		time_t startTime = time(NULL);
		LCS(sequence1, sequence2, false, false, false, flagStruct);
		printf("Time average: %g sec.\n", difftime(time(NULL), startTime));
		printf("\n");
	}
	//Compute an LCPS with the two sequences!
	if(flagStruct.argFlags[5]) {
		LCPS(sequence1, sequence2, flagStruct);
		printf("\n");
	}

	//Compute an LCTS with the two sequences!
	if(flagStruct.argFlags[6]) {
		LCTS(sequence1, sequence2, flagStruct);
		printf("\n");
	}


	return 0;
}


