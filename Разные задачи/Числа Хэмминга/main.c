#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int Min(int a, int b, int c)
{
    return (a <= b) ? (a <= c) ? a : c : (b <= c) ? b : c;
}

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

void GenerateNumber(int* index, int base, TVector vector)
{
    while (vector.Array[(*index)] * base <= vector.Array[vector.Count - 1])
    {
        ++(*index);
    }
}

TVector HammingNumber(int n)
{
    TVector vector = CreateVector(n);
    if (n == 0)
    {
        return vector;
    }
    
    PushVector(1, &vector);
    int index2 = 0;
    int index3 = 0;
    int index5 = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        GenerateNumber(&index2, 2, vector);
        GenerateNumber(&index3, 3, vector);
        GenerateNumber(&index5, 5, vector);
        PushVector(Min(2*vector.Array[index2], 3* vector.Array[index3], 5* vector.Array[index5]), &vector);
    }
    
    return vector;
}

int main(void)
{
    TVector vector = HammingNumber(20);
    PrintVector(vector);
    DestroyVector(&vector);
    return EXIT_SUCCESS;
}