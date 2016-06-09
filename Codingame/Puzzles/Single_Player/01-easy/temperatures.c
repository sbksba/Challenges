#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

/*
  Write a program that prints the temperature closest to 0 among input data.
  If two numbers are equally close to zero, positive integer has to be
  considered closest to zero (for instance, if the temperatures are -5 and 5,
  then display 5).
  INPUT         OUTPUT
  5
  1 -2 -8 4 5   -1
*/
int main()
{
	int N;
	scanf("%d\n", &N);

	if (N == 0)
		printf("0");
	else {
		char str[10000];
		fgets(str,10000,stdin);
		char *iter = str;

		int T, len, min=INT_MAX;
		/* Search the temperature of minimum absolute valueReads
		   Note a subtilty of the exercice : a temperature T>0 is prefered over -T*/
		while (sscanf(iter, "%d%n", &T, &len) == 1) {
			if (abs(T) < abs(min) || (T == -min && T > 0))
				min = T;
			iter+=len;
		}

		printf("%d", min);
	}
	return 0;
}
