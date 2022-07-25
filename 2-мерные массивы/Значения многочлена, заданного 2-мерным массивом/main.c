#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
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

float CalcPoly(size_t row, size_t column, float array[ROW][COLUMN], float x, float y)
{
	if (x == 0.0 || y == 0.0)
	{
		return 0.0;
	}

	float sum = 0.0;
	float powX = 1.0;
	float powY = 1.0;

	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < column; j++)
		{
			sum += array[i][j] * powX * powY;
			powY *= y;
		}

		powX *= x;
		powY = 1.0;
	}

	return sum;
}

int main(void)
{
	float array[ROW][COLUMN];
	float x, y;

	assert(scanf("%f %f", &x, &y) != 2);

	FillRandomValues(ROW, COLUMN, array);
	PrintArray(ROW, COLUMN, array);

	printf("\nPolynom is %f\n", CalcPoly(ROW, COLUMN, array, x, y));

	return 0;
}