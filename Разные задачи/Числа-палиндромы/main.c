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

int DigitCount(int num)
{
    int count = 0;
    while (num > 0)
    {
        num /= 10;
        ++count;
    }
    
    return count;
}

bool IsPalindromeNumber(int number)
{
    int length = DigitCount(number);
    int num = number;
    int reverseNum = 0;

    for (int i = 0; i < length; ++i)
    {
        reverseNum *= 10;
        reverseNum += number % 10;
        number /= 10;
    }

    return num == reverseNum;
}

TVector PalindromeNumber(int n)
{
    TVector vector = CreateVector(n);

    int count = 0;
    for (int i = 0; count < n; ++i)
    {
        if (IsPalindromeNumber(i) && IsPalindromeNumber(i*i))
        {
            PushVector(i, &vector);
            ++count;
        }
    }
    
    return vector;
}

int main(void)
{
    TVector vector = PalindromeNumber(20);
    PrintVector(vector);
    DestroyVector(&vector);
    return EXIT_SUCCESS;
}