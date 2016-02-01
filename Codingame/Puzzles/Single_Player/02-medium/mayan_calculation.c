#include <stdlib.h>
#include <stdio.h>

/* digit is a 2-dim array of size H x W representing 1 of the 20 mayan digits.
   digits is a 2-dim array of size H x 20*W representing the 20 mayan digits.
   This function compares 'digit' with each of the 20 digits and returns
   the matching decimal value.*/
int mayanDigitToInt(char** digit, char** digits, int W, int H)
{
	int isIdentical = 0;
	int i = 0;
	while (i < 20 && !isIdentical) {
		/* we assum 'digit' to be the i-th digit of 'digits' and look
		   for a difference to refute this hypothesis*/
		isIdentical = 1;
		for (int y = 0; y < H && isIdentical; y++)
			for (int x = 0; x < W && isIdentical; x++)
				if (digits[y][i*W + x] != digit[y][x]) {
					isIdentical = 0;
					i++;
				}
	}
	return i;
}

/* number is a 2-dim array of size numberH x > representing a mayan number
   digits is a 2-dim array of size H x 20*W representing the 20 mayan digits.
   This functions converts number into its decimal value*/
long mayanNumberToLong(char** number, int numberH, char** digits, int W, int H)
{
	long result = 0;
	for (int i = 0; i < numberH/H; i++)
		result += mayanDigitToInt(number + i*H, digits, W, H) * pow(20, numberH/H - (i+1));
	return result;
}

/* digits is a 2-dim array of size H x 20*W representing the 20 mayan digits.
   This function converts 'digit' into its mayan representation and prints it.*/
void printAsMayanDigit(int digit, char** digits, int W, int H)
{
	for (int y = 0; y < H; y ++) {
		fwrite(&digits[y][digit*W], W, sizeof(char), stdout);
		printf("\n");
	}
}

/* digits is a 2-dim array of size H x 20*W representing the 20 mayan digits.
   This function prints the mayan representation of 'number' recursively,
   using printAsMayanDigit*/
void printAsMayanNumber(long number, char** digits, int W, int H)
{
	if(number != 0) {
		printAsMayanNumber(number/20, digits, W, H);
		printAsMayanDigit(number%20, digits, W, H);
	}
}

// Frees a dynamically allocated 2-dimensionnal array of dimension dim1 xsmthing
void free2DArray(char **array, int dim1)
{
	for (int i = 0; i < dim1; i++)
		free(array[i]);
	free(array);
}

int main(int argc, char **argv)
{
	int W, H;
	scanf("%d %d\n", &W, &H);

	// reads the 20 mayan digits
	char** digits = malloc(H * sizeof(*digits));
	for (int i = 0; i < H; i++) {
		digits[i] = malloc(20 * W * sizeof(**digits));
		gets(digits[i]);
	}

	// read first mayan number
	int nb1H;
	scanf("%d\n", &nb1H);
	char **nb1 = malloc(nb1H * sizeof(*nb1));
	for (int i = 0; i < nb1H; i++) {
		nb1[i] = malloc(W * sizeof(**nb1));
		gets(nb1[i]);
	}
	long decimalNb1 = mayanNumberToLong(nb1, nb1H, digits, W, H);


	// reads second mayan number
	int nb2H;
	scanf("%d\n", &nb2H);
	char **nb2 = malloc(nb2H * sizeof(*nb2));
	for (int i = 0; i < nb2H; i++) {
		nb2[i] = malloc(W * sizeof(**nb2));
		gets(nb2[i]);
	}
	long decimalNb2 = mayanNumberToLong(nb2, nb2H, digits, W, H);

	// reads the operation to perform
	char operation;
	scanf("%c\n", &operation);

	// performs operation
	long result = 0;
	switch(operation) {
        case '*':
		result = decimalNb1 * decimalNb2; break;
        case '/':
		result = decimalNb1 / decimalNb2; break;
        case '+':
		result = decimalNb1 + decimalNb2; break;
        case '-':
		result = decimalNb1 - decimalNb2; break;
	}

	// prints result
	if (result == 0)
		printAsMayanDigit(0, digits, W, H);
	else
		printAsMayanNumber(result, digits, W, H);

	// frees memory
	free2DArray(digits, H);
	free2DArray(nb1, nb1H);
	free2DArray(nb2, nb2H);

	return EXIT_SUCCESS;
}
