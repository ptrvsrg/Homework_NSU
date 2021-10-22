#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void PrintArray(size_t row, size_t column, const float array[row][column])
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

void FillRandomValues(size_t row, size_t column, float array[row][column])
{
	srand(time(NULL));

	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < column; j++)
		{
			array[i][j] = (float)rand() / (float)rand();
		}
	}
}

float SumElementOfArray(size_t row, size_t column, const float array[row][column])
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
	float array[3][4];

	FillRandomValues(3, 4, array);
	PrintArray(3, 4, array);

	printf("\nSum is %f\n", SumElementOfArray(3, 4, array));

	return 0;
}