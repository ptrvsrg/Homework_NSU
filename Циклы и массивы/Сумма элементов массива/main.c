#include <stdio.h>

int SumOfArrayElements(int* Array, int SizeOfArray)
{
	if (SizeOfArray == 1)
	{
		return Array[0];
	}
	else
	{
		return Array[SizeOfArray - 1] + SumOfArrayElements(Array, SizeOfArray - 1);
	}
}

int main()
{
	int Array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int SizeOfArray = sizeof(Array) / sizeof(*Array);
	printf("Sum of array elements is %d", SumOfArrayElements(Array, SizeOfArray));
	return 0;
}