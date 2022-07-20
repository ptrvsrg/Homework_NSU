#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int Factorial(int x)
{
	if (x == 0)
	{
		return 1;
	}
	else
	{
		return x * Factorial(x - 1);
	}
}

int main()
{
	int x;
	if (scanf("%d", &x) != 1 || x < 0)
	{
		printf("Bad input");
		return 1;
	}

	printf("The factorial is %d", Factorial(x));
	return 0;
}