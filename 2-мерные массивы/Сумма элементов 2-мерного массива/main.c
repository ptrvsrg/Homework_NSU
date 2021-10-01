#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1
};

void PrintArray(int row, int column, const int array[row][column])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			printf("%d ", array[i][j]);
		}

		printf("\n");
	}
}

void FillRandomValues(int row, int column, int array[row][column])
{
	srand(time(NULL));

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			array[i][j] = rand() % 100;
		}
	}
}

int SumElementOfArray(int row, int column, const int array[row][column])
{
	int sum = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			sum += array[i][j];
		}
	}

	return sum;
}

int main()
{
	int array[3][4];

	FillRandomValues(3, 4, array);
	PrintArray(3, 4, array);

	printf("\nSum is %d\n", SumElementOfArray(3, 4, array));

	return SUCCESS;
}