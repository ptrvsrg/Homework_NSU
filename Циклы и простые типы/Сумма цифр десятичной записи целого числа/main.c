#include <stdio.h>
#include <math.h>
#pragma warning(disable : 4996)

int SumDigits(int x)
{
	int y = fabs(x);
	if (y < 10)
	{
		return y;
	}
	else
	{
		return y % 10 + SumDigits(y / 10);
	}
}

void main()
{
	int x;
	scanf("%d", &x);
	printf("The sum is %d", SumDigits(x));
}