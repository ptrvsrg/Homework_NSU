#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void PrintArray(size_t row, size_t column, float array[row][column])
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

void ArrayCopy(size_t row1, size_t column1, float array1[row1][column1], size_t row2, size_t column2, float array2[row2][column2])
{
	assert(row1 == row2 && column1 == column2);

    for (size_t i = 0; i < row1; i++)
    {
        for (size_t j = 0; j < column1; j++)
        {
            array2[i][j] = array1[i][j];
        }
    }
}

int main(void)
{
	float array1[3][4];
	float array2[3][4];

	FillRandomValues(3, 4, array1);
	printf("First matrix: \n");
	PrintArray(3, 4, array1);

    printf("\nCopied matrix:\n");
    ArrayCopy(3, 4, array1, 3, 4, array2);
    PrintArray(3, 4, array2);

	return 0;
}