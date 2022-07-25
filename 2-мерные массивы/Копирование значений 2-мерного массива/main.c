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

void ArrayCopy(size_t row, size_t column, float array1[ROW][COLUMN], float array2[ROW][COLUMN])
{
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            array2[i][j] = array1[i][j];
        }
    }
}

int main(void)
{
	float array1[ROW][COLUMN];
	float array2[ROW][COLUMN];

	FillRandomValues(ROW, COLUMN, array1);
	printf("First matrix: \n");
	PrintArray(3, 4, array1);

    printf("\nCopied matrix:\n");
    ArrayCopy(ROW, COLUMN, array1, array2);
    PrintArray(ROW, COLUMN, array2);

	return 0;
}