#include <stdio.h>
#include <math.h>
#pragma warning(disable : 4996)

double PI(int n)
{
	double sum = 0;

	if (n >= 1)
	{
		for (int i = 1; i <= n; i++)
			sum += 1.0 / (i * i);

		return sqrt(6 * sum);
	}
	else
	{
		return 0;
	}
}

void main()
{
	int x;
	scanf("%d", &x);
	printf("PI is %lf", PI(x));
}