#include <stdio.h>
#include <stdlib.h>

void MaxPartialSum(int* array, int arrayCount, int* leftIndex, int* rightIndex)
{
    int answer = array[0];
	int sum = 0;
	int minSum = 0;
	int minPosition = -1;
	*leftIndex = 0;
	*rightIndex = 0;

    for (int i = 0; i < arrayCount; ++i) 
    {
        sum += array[i];
    
        int current = sum - minSum;
        if (current > answer) 
        {
            answer = current;
            *leftIndex = minPosition + 1;
            *rightIndex = i;
        }
    
        if (sum < minSum) 
        {
            minSum = sum;
            minPosition = i;
        }
    }
}

int main(void)
{
    int array[] = { -7, 2, -3, 3, -1, 5, -2, 7 };

    int leftIndex = 0;
    int rightIndex = 0;

    MaxPartialSum(array, sizeof(array) / sizeof(*array), &leftIndex, &rightIndex);

    printf("Interval with maximum partial sum is [ %d, %d ]\n", leftIndex, rightIndex);

    return EXIT_SUCCESS;
}