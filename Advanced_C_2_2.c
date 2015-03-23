

#include <stdio.h>


char * S[9] = {"Faint signals, barely perceptible", "Very weak signals", "Weak signals", "Fair signals", "Fairly good signals", "Good signals", "Moderately strong signals", "Strong signals", "Extremely strong signals"};
char * R[5] = {"unreadable", "barely readable, occasional words distinguishable", "readable with considerable difficulty", "readable with practically no difficulty", "perfectly readable"};

int main(int argc, char const *argv[])
{
	char s[2];
	scanf("%s", s);
	printf("%s, %s.\n", S[s[1] - 49], R[s[0] - 49]);

	return 0;
}