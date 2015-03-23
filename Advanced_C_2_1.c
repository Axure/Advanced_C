#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// substring match


// utilize strcpy

char * deleteSubstring(char * mainString, char * substring) {

	char * indexPointer;

	int secondLength = strlen(substring);

	char * newString = (char*)malloc(sizeof(char) * strlen(mainString));

	int doneLength = 0;

	while ((indexPointer = strstr(mainString, substring)) != NULL) {
		// printf("%s\n", mainString);

		memcpy(newString + doneLength, mainString, indexPointer - mainString);
		doneLength += indexPointer - mainString;

		mainString = indexPointer + secondLength;

	}
	// Copy the remaining

	memcpy(newString + doneLength, mainString, strlen(mainString));
	return newString;
}


int main(int argc, char const *argv[])
{
	char *s1 = (char*)malloc(80 * sizeof(char));
	char *s2 = (char*)malloc(80 * sizeof(char));
	scanf("%s", s1);
	scanf("%s", s2);
	// printf("%s %s\n", s1, s2);
	printf("%s\n", deleteSubstring(s1, s2));

	free(s1);
	free(s2);


	return 0;
}