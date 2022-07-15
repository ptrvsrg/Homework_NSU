#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void PrintArray(int row, int column, const float array[row][column])
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

int GetNumberOfNullRow(int row, int column, const float array[row][column])
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
	float array1[3][4] = { 
		{1, 2, 3, 4}, 
		{0, 0, 0, 0}, 
		{4, 3, 2, 1} 
	};

	float array2[5][2] = { 
		{1, 2}, 
		{0, 0}, 
		{4, 3}, 
		{0, 0}, 
		{0, 0} 
	};

	PrintArray(3, 4, array1);
	printf("Number of null rows is %d\n\n", GetNumberOfNullRow(3, 4, array1));

	PrintArray(5, 2, array2);
	printf("Number of null rows is %d\n", GetNumberOfNullRow(5, 2, array2));

	return 0;
}