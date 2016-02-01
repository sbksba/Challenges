#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Returns 1 if 'word' is writeable with letters contains in 'letters', 0 else
int writeable(char* word, char* letters)
{
	char copy[strlen(letters)];
	strcpy(copy, letters);

	/* For each letter in word, looks for the letter in copy and replaces it
       by a space. If the letter can't be found, then word is not writeable with
       letters */
	for (int i = 0; word[i] != '\0'; i++) {
		int j = 0;
		while (copy[j] != '\0' && copy[j] != word[i])
			j++;
		if (copy[j] == word[i])
			copy[j] = ' ';
		else
			return 0;
	}
	return 1;
}

// array of 26 integers corresponding to the weight of each letter of the alphabet
int WEIGHTS[] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

// Returns the number of points 'word' earns
int pointCount (char *word, int WEIGHTS[26])
{
	int res = 0;
	for (int i = 0; word[i] != '\0'; i++)
		res += WEIGHTS[word[i]-'a'];
	return res;
}

int main(int argc, char **argv)
{
	// Reading input : the N words of the dictionary, and letters available
	int N;
	scanf("%d\n", &N);
	char dictionary[N][30];
	for (int i = 0; i < N; i++)
		gets(dictionary[i]);
	char letters[8];
	fgets(letters,8,stdin);

	// Searches max pointCount amongst writeable words
	int max = 0;
	int count;
	char *res = NULL;
	for (int i = 0; i < N; i++)
		if (writeable(dictionary[i], letters) && (count = pointCount(dictionary[i], WEIGHTS)) > max) {
			max = count;
			res = dictionary[i];
		}

	printf("%s\n", res);
	return EXIT_SUCCESS;
}
