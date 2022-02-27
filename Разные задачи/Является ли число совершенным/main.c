#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int Count;
    int Max;
    int* Array;
} TVector;

TVector CreateVector(int max)
{
    TVector vector = { 0, max, NULL };

    vector.Array = calloc(max, sizeof(*vector.Array));
    assert(vector.Array != NULL);

    return vector;
}

void PushVector(int value, TVector* vector)
{
    assert(vector->Count != vector->Max);
    vector->Array[vector->Count] = value;
    ++vector->Count;
}

void PrintVector(TVector vector)
{
    for (int i = 0; i < vector.Count; ++i)
    {
        printf("%d ", vector.Array[i]);
    }
}

void DestroyVector(TVector* vector)
{
    free(vector->Array);
    vector->Count = 0;
    vector->Max = 0;
}

bool IsPerfect(int num) 
{
    int sum = 0;
    for (int div = 1; div <= num / 2; ++div) 
    {
        if (num % div == 0) 
        {
            sum += div;
        }

        if (sum > num)
        {
            return false;
        }
    }

    return sum == num;
}

TVector PerfectNumber(int n)
{
    TVector vector = CreateVector(n);

    int index = 0;
    for (int i = 0; index != n && i < 16; ++i)
    {
        int number = (1 << i) * ((1 << (i + 1)) - 1);
        if (IsPerfect(number))
        {
            PushVector(number, &vector);
            ++index;
        }
    }
    
    return vector;
}

int main(void)
{
    PrintVector(PerfectNumber(5));
    return EXIT_SUCCESS;
}