#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/
int main()
{

	// Coordinates of the light and Thor
	int lX, lY, tX, tY;
	scanf("%d%d%d%d", &lX, &lY, &tX, &tY);

	for (;;) {
		if (tY < lY) {
			printf("S");
			tY++;
		}
		else if (tY > lY) {
			printf("N");
			tY--;
		}

		if (tX < lX) {
			printf("E");
			tX++;
		}
		else if (tX > lX) {
			printf("W");
			tX--;
		}
		printf("\n");
	}

	return 0;
}
