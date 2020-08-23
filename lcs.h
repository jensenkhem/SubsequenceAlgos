#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "utility.h"
int LCS(char sequence1[], char sequence2[], bool lps, bool lts, bool donelts, struct retValues s);
int LCS_four(char s1[], char s2[], char s3[], char s4[], bool lts, bool lps, bool donelts, struct retValues s);