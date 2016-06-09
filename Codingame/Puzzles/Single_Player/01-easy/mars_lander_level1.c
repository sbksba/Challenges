#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

/*
  INPUT
  
  Initialization input

  6         (surfaceN) Surface made of 6 points
  0 1500    (landX landY)
  1000 2000 (landX landY)
  2000 500  (landX landY) Start of flat ground
  3500 500  (landX landY) End of flat ground
  5000 1500 (landX landY)
  6999 1000 (landX landY)

  
  Input for turn 1                                               Output for turn 1
  2500 2500 0 0 500 0 0 (X Y hSpeed vSpeed fuel rotate power)    0 3

  Input for turn 2                                               Output for turn 2
  2500 2499 0 -3 499 0 1 (X Y hSpeed vSpeed fuel rotate power)   0 3

  Input for turn 3                                               Output for turn 3
  2500 2495 0 -4 497 0 2 (X Y hSpeed vSpeed fuel rotate power)   0 2
*/

int main()
{
	int N;
	scanf("%d\n", &N);

	int surfaceX[N];
	int surfaceY[N];
	for (int i = 0; i < N; i++)
		scanf("%d %d\n", &surfaceX[i], &surfaceY[i]);

	while (1) {
		int X, Y, dX, dY, fuel, rotate, power;
		scanf("%d %d %d %d %d %d %d", &X, &Y, &dX, &dY, &fuel, &rotate, &power);

		// Finds landing altitude by Looking for 2 consecutive points w/ same Y
		int groundY = -1;
		for (int i = 0; (i < N && groundY == -1); i++)
			if (surfaceX[i] <= X && X <= surfaceX[i+1])
				groundY = surfaceY[i];

		/* Finds out if it is safe to start braking only next turn, by
		   simulating it and analyzing vertical speed at landing
		   If it is safe, waits, else starts braking*/
		double vdY = (double)dY;
		double vY = (double)Y;
		for (double i = 0.0; i <= 4; i++) {
			vdY += i - 3.711;
			vY += vdY;
		}
		while (vY > groundY && vdY < 0) {
			vdY += 0.289; // 4-3.711;
			vY += vdY;
		}
		printf((vdY >= 0 || vdY > -40.0) ? "0 0\n" : "0 4\n");
	}
	return 0;
}
