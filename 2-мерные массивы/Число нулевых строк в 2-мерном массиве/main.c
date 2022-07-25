#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ROW 3
#define COLUMN 2

void PrintArray(int row, int column, const float array[ROW][COLUMN])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			printf("%f ", array[i][j]);
		}

		printf("\n");
	}
}

int GetNumberOfNullRow(int row, int column, const float array[ROW][COLUMN])
{
	int nullRow = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (array[i][j] != 0.0)
			{
				break;
			}
			else if (j == column - 1)
			{
				nullRow++;
			}
		}
	}

	return nullRow;
}

int main()
{
	const float array1[ROW][COLUMN] = { 
		{ 1, 2 }, 
		{ 0, 0 }, 
		{ 4, 3 } 
	};

	PrintArray(ROW, COLUMN, array1);
	printf("Number of null rows is %d\n\n", GetNumberOfNullRow(ROW, COLUMN, array1));

	return 0;
}