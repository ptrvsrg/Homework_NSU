#include <stdio.h>
#include <math.h>
#pragma warning(disable : 4996)

int SumDigitsFractionalPart(int n, float x)
{
	int sum = 0, y = x * pow(10, n);

	for (int i = 0; i < n; i++)
	{
		sum += y % 10;
		y /= 10;
	}

	return sum;
}

void main()
{
	int n;
	float x;
	scanf("%d %f", &n, &x);
	printf("The sum is %d", SumDigitsFractionalPart(n, x));
}