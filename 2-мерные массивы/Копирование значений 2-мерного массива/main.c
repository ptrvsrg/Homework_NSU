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

int ArrayCopy(int row1, int column1, const int array1[row1][column1], int row2, int column2, int array2[row2][column2])
{
	if (row1 == row2 && column1 == column2)
	{
		for (int i = 0; i < row1; i++)
		{
			for (int j = 0; j < column1; j++)
			{
				array2[i][j] = array1[i][j];
			}
		}

		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

int main()
{
	int array1[3][4];
	int array2[3][4];
	int array3[5][5];

	FillRandomValues(3, 4, array1);
	printf("First matrix: \n");
	PrintArray(3, 4, array1);

	if (ArrayCopy(3, 4, array1, 3, 4, array2) == FAILURE)
	{
		printf("\nBad matrix!\n");
		return FAILURE;
	}
	else
	{
		printf("\nCopied matrix:\n");
		PrintArray(3, 4, array2);
	}

	if (ArrayCopy(3, 4, array1, 5, 5, array3) == FAILURE)
	{
		printf("\nBad matrix!\n");
		return FAILURE;
	}
	else
	{
		printf("\nCopied matrix:\n");
		PrintArray(5, 5, array3);
	}

	return SUCCESS;
}