#include <stdio.h>
#include <math.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1
};

int NumberToDigitsArray(int* Array, int SizeOfArray)
{
	int Sum = 0;

	for (int i = 0; i < SizeOfArray; i++)
	{
		Sum += Array[i] * pow(10, i);
	}

	return Sum;
}

int main()
{
	int Array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	printf("Number is %d\n", NumberToDigitsArray(Array, sizeof(Array) / sizeof(*Array)));
	return SUCCESS;
}