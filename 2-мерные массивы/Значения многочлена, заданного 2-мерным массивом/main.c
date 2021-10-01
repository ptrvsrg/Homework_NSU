#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1
};

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

void FillRandomValues(int row, int column, float array[row][column])
{
	srand(time(NULL));

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			array[i][j] = (float)rand() / (float)rand();
		}
	}
}

float CalcPoly(int row, int column, const float array[row][column], float x, float y)
{
	if (x == 0.0 || y == 0.0)
	{
		return 0.0;
	}

	float sum = 0.0;
	float powX = 1.0;
	float powY = 1.0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			sum += array[i][j] * powX * powY;
			powY *= y;
		}

		powX *= x;
		powY = 1.0;
	}

	return sum;
}

int main()
{
	float array[2][3];
	float x, y;

	if (scanf("%f %f", &x, &y) == EOF)
	{
		return FAILURE;
	}

	FillRandomValues(2, 3, array);
	PrintArray(2, 3, array);

	printf("\nPolynom is %f\n", CalcPoly(2, 3, array, x, y));

	return SUCCESS;
}