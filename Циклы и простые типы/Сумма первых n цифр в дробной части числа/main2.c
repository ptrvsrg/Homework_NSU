#include <stdio.h>
#include <math.h>
#pragma warning(disable : 4996)

int SumDigitsFractionalPart(int n, char* Number)
{
	int i = 0;
	while (Number[i] != '.')
	{

	}
}

int main()
{
	int n;
	char Number[100];
	if (scanf("%s %d", Number, &n) == EOF)
		return 1;
	printf("The sum is %d", SumDigitsFractionalPart(n, Number));
	return 0;
}