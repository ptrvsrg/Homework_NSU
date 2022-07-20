#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int FindMin(int begin, int end, int* array)
{
    int min = INT_MAX;

    for (int i = begin; i <= end; ++i)
    {
        if (array[i] < min)
        {
            min = array[i];
        }    
    }
    
    return min;
}

int FindMax(int begin, int end, int* array)
{
    int max = INT_MIN;

    for (int i = begin; i <= end; ++i)
    {
        if (array[i] > max)
        {
            max = array[i];
        }    
    }
    
    return max;
}

int FindOneMissingNumber(int begin, int end, int* array, int min, int max)
{
    int arithProgressSum = (min + max) * (max - min + 1) / 2;

    for (int i = begin; i <= end; ++i)
    {
        arithProgressSum -= array[i];
    }
    
    return arithProgressSum;
}

bool FindMissingNumber(int* missingNumber, int begin, int end, int* array)
{
    int min = FindMin(begin, end, array);
    int max = FindMax(begin, end, array);

    int countMissingNumber = (max - min) - (end - begin);

    if (countMissingNumber == 0)
    {
        return false;
    }
    else if (countMissingNumber == 1)
    {
        *missingNumber = FindOneMissingNumber(begin, end, array, min, max);
        return true;
    }
    else if(end - begin == 1)
    {
        *missingNumber = min + 1;
        return true;
    }
    
    int newIndex = (begin + end) / 2;
    if (FindMissingNumber(missingNumber, newIndex, end, array))
    {
        return true;
    }
    if (FindMissingNumber(missingNumber, begin, newIndex, array))
    {
        return true;
    }

    return false;
}

int main(void)
{
    int array[] = {
        1, 2, 3, 4, 5, 6
    };
    
    int arrayCount = sizeof(array) / sizeof(*array);

    int missingNumber = 0;

    if (FindMissingNumber(&missingNumber, 0, arrayCount - 1, array))
    {
        printf("%d\n", missingNumber);
    }
    else
    {
        printf("No missing number\n");
    }

    return EXIT_SUCCESS;
}