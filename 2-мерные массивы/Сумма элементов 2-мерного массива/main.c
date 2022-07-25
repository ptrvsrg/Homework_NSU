#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 3
#define COLUMN 2 

void PrintArray(size_t row, size_t column, float array[ROW][COLUMN])
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < column; j++)
		{
			printf("%f ", array[i][j]);
		}

		printf("\n");
	}
}

void FillRandomValues(size_t row, size_t column, float array[ROW][COLUMN])
{
	srand((unsigned int)time(NULL));

	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < column; j++)
		{
			array[i][j] = (float)rand() / (float)rand();
		}
	}
}

float SumElementOfArray(size_t row, size_t column, float array[ROW][COLUMN])
{
	float sum = 0.0;

	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < column; j++)
		{
			sum += array[i][j];
		}
	}

	return sum;
}

int main(void)
{
	float array[ROW][COLUMN];

	FillRandomValues(ROW, COLUMN, array);
	PrintArray(ROW, COLUMN, array);

	printf("\nSum is %f\n", SumElementOfArray(ROW, COLUMN, array));

	return 0;
}