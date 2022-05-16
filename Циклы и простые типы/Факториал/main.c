#include <stdio.h>
#pragma warning(disable : 4996)

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
	scanf("%d", &x);

	if (x < 0)
	{
		printf("Bad input");
		return 1;
	}

	printf("The factorial is %d", Factorial(x));
	return 0;
}