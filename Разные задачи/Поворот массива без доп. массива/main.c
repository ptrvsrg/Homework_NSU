#include <stdio.h>

int GCD(int a, int b)
{
    int max = (a >= b) ? a : b;
    int min = (a < b) ? a : b;

    if (min == 0)
    {
        return min;
    }
    else if (max % min == 0)
    {
        return min;
    }
    
   return GCD(max % min, min);
}

void MoveArray(int shift, int arraySize, int* array)
{
    shift %= arraySize;
    int count = GCD(shift, arraySize);

    for (int i = 0; i < count; ++i)
    {
        int nextIndex = (i + shift) % arraySize;
        int buffer = 0;

        while(i != nextIndex)
        {
            buffer = array[nextIndex];
            array[nextIndex] = array[i];
            array[i] = buffer;

            nextIndex = (nextIndex + shift) % arraySize;
        }
    }
    
}

void PrintArray(int arraySize, int* array)
{
    for (int i = 0; i < arraySize; ++i)
    {
        printf("%d ", array[i]);
    }
}

int main(void)
{
    int array[] = { 0, 1, 2, 3, 4, 5 };
    int arraySize = sizeof(array) / sizeof(*array);

    PrintArray(arraySize, array);
    printf("\n");

    MoveArray(655, arraySize, array);
    PrintArray(arraySize, array);

    return 0;
}