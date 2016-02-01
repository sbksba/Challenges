#include <stdlib.h>
#include <stdio.h>

int cmp (const void * a, const void * b)
{
	int aa = *(int*)a;
	int bb = *(int*)b;
	return aa<bb?-1:aa>bb?1:0;
}

int main(int argc, char **argv)
{
	// Read input : number of participants, price of the gift, budgets
	int N, price;
	scanf("%d\n%d\n", &N, &price);

	int budgets[N];
	int totalBudget = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d\n", &budgets[i]);
		totalBudget += budgets[i];
	}

	if (totalBudget < price)
		printf("IMPOSSIBLE\n");
	else {
		/* sorts budgets, then starting from the lower budgets
           each particpant contributes (price left) / (number of participants left)
           or if he hasn't enough money, everything he has*/
		qsort(budgets, N , sizeof(int), cmp);
		int contribution;

		for (int i = 0; i < N; i++) {
			contribution = (budgets[i] >= price/(N-i)) ? price/(N-i) : budgets[i] ;
			printf("%d\n", contribution);
			price -= contribution;
		}
	}
	return EXIT_SUCCESS;
}
