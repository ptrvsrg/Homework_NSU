#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int Count;
    int* Array;
} TVector;

TVector CreateVector(int count, int* array)
{
    TVector vector = { count, array };
    return vector;
}

bool CheckSameValuesVector(TVector vector)
{
    for (int i = 0; i < vector.Count - 1; ++i)
    {
        if (vector.Array[i] != vector.Array[i + 1])
        {
            return false;
        }   
    }
    
    return true;
}

bool CheckArithmeticProgression(TVector vector)
{
    if (CheckSameValuesVector(vector) || vector.Count <= 2)
    {
        return true;
    }
    
    int min = INT_MAX;
    int beforeMin = INT_MAX;

    for (int i = 0; i < vector.Count; ++i)
    {
        if (vector.Array[i] == min || vector.Array[i] == beforeMin)
        {
            return false;
        }
        else if (vector.Array[i] < min)
        {
            beforeMin = min;
            min = vector.Array[i];
        }
        else if (vector.Array[i] < beforeMin)
        {
            beforeMin = vector.Array[i];
        }
    }
    
    int firstElem = min;
    int difference = beforeMin - min;

    bool* checkArray = calloc(vector.Count, sizeof(*checkArray));
    assert(checkArray != NULL);

    for (int i = 0; i < vector.Count; ++i)
    {
        int index = (vector.Array[i] - firstElem) / difference;

        if (index >= vector.Count || checkArray[index])
        {
            return false;
        }
        
        checkArray[index] = true;
    }
    
    return true;
}

int main(void)
{
    int array1[] = { 6, 12, 0, 8, 2 };
    TVector vector1 = CreateVector(sizeof(array1) / sizeof(*array1), array1);
    
    int array2[] = { 0, 3, 6, 9, 12 };
    TVector vector2 = CreateVector(sizeof(array2) / sizeof(*array2), array2);
    
    int array3[] = { 0, 0, 0, 0, 0 };
    TVector vector3 = CreateVector(sizeof(array3) / sizeof(*array3), array3);
    
    int array4[] = { 0, 0, 1, 0, 0 };
    TVector vector4 = CreateVector(sizeof(array4) / sizeof(*array4), array4);

    printf("\"In the vector1 is arithmetic progression\" is %s\n", CheckArithmeticProgression(vector1) ? "true" : "false");
    printf("\"In the vector2 is arithmetic progression\" is %s\n", CheckArithmeticProgression(vector2) ? "true" : "false");
    printf("\"In the vector3 is arithmetic progression\" is %s\n", CheckArithmeticProgression(vector3) ? "true" : "false");
    printf("\"In the vector4 is arithmetic progression\" is %s\n", CheckArithmeticProgression(vector4) ? "true" : "false");

    return EXIT_SUCCESS;
}