#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
	int road; // the length of the road before the gap.
	scanf("%d", &road);
	int gap; // the length of the gap.
	scanf("%d", &gap);
	int platform; // the length of the landing platform.
	scanf("%d", &platform);

	// game loop
	while (1) {
		int speed; // the motorbike's speed.
		scanf("%d", &speed);
		int coordX; // the position on the road of the motorbike.
		scanf("%d", &coordX);

		// Write an action using printf(). DON'T FORGET THE TRAILING \n
		// To debug: fprintf(stderr, "Debug messages...\n");

		// if the bike has passed the gap, or going faster than needed to jump over it
		if (coordX >= road+gap || speed > gap+1)
			printf("SLOW\n");
		// if the bike isn't going fast enough to jump over the gap
		else if (speed <= gap)
			printf("SPEED\n");
		// if the bike can land after the gap by jumping
		else if (coordX+speed >= road+gap)
			printf("JUMP\n");
		else
			printf("WAIT\n");


		//printf("SPEED\n"); // A single line containing one of 4 keywords: SPEED, SLOW, JUMP, WAIT.
	}

	return 0;
}
