#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#ifndef U_H
#define U_H
struct retValues {
	int argFlags[7];
	char inputFile[100];
	char outputFile[100];
	int validStruct;
};

bool checkValidInput(char sequence[], struct retValues s);
bool validateStruct(struct retValues s);
void getUserInput(char sequence1[], char sequence2[], struct retValues s);
int readInputFile(char s1[], char s2[], char filename[], struct retValues s);
int generateSequence(char s1[], char s2[], int writeToFile, char filename[]);
void writeToOutputFile(struct retValues s, char string[]);
struct retValues checkArgs(int argc, char const *argv[], char test1[], char test2[]);
#endif