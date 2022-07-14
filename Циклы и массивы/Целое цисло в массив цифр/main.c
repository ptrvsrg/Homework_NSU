#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1
};

void GetArrayOfDigits(int Number, int** Array, int* SizeOfArray)
{
	*SizeOfArray = 0;

	do
	{
		++(*SizeOfArray);
	} while (Number >= pow(10, *SizeOfArray));

	*Array = (int*)malloc(sizeof(int) * (*SizeOfArray));

	for (int i = 0; i < *SizeOfArray; i++)
	{
		(*Array)[i] = Number % 10;
		Number /= 10;
	}
}

void PrintArray(int* Array, int SizeOfArray)
{
	for (int i = 0; i < SizeOfArray; i++)
	{
		printf("Array[%d] = %d\n", i, Array[i]);
	}
}

int main()
{
	int Number;

	if (scanf("%d", &Number) == EOF)
	{
		return FAILURE;
	}
	
	int* Array, SizeOfArray;
	GetArrayOfDigits(Number, &Array, &SizeOfArray);
	PrintArray(Array, SizeOfArray);

	return SUCCESS;
}