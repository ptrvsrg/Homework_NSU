#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int Fabs(int a)
{
    return (a >= 0) ? a : -a;
}

int SumDigits(int x)
{
	int y = Fabs(x);
	if (y < 10)
	{
		return y;
	}
	else
	{
		return y % 10 + SumDigits(y / 10);
	}
}

int main()
{
	int x;
	if (scanf("%d", &x) != 1)
    {
        return 1;
    }

	printf("The sum is %d", SumDigits(x));
    return 0;
}