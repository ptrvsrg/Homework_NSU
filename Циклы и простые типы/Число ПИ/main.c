#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

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

int main(void)
{
	int x;
	if (scanf("%d", &x) != 1)
    {
        return 1;
    }

	printf("PI is %lf", PI(x));
    return 0;
}