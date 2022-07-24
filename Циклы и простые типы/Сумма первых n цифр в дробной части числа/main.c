#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int SumDigitsFractionalPart(int n, float x)
{
	int sum = 0;
    int y = (int)(x * pow(10, n));

	for (int i = 0; i < n; i++)
	{
		sum += y % 10;
		y /= 10;
	}

	return sum;
}

int main(void)
{
	int n;
	float x;
	if (scanf("%d %f", &n, &x) != 2)
    {
        return 1;
    }

	printf("The sum is %d", SumDigitsFractionalPart(n, x));
    return 0;
}