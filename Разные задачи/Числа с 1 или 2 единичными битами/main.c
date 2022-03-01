#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define UINT_BITS_SIZE 8*sizeof(unsigned int)

void PrintBits(unsigned int Number)
{
    printf("%u = ", Number);

	for (int i = 0; i < UINT_BITS_SIZE; i++)
	{
		if (i % 8 == 0)
		{
			printf(" ");
		}

		printf("%d", ((1 << (UINT_BITS_SIZE - 1) & Number) != 0) ? 1 : 0);
		Number <<= 1;
	}
}

typedef struct
{
    int Count;
    int Max;
    unsigned int* Array;
} TVector;

TVector CreateVector(int max)
{
    TVector vector = { 0, max, NULL };

    vector.Array = calloc(max, sizeof(*vector.Array));
    assert(vector.Array != NULL);

    return vector;
}

void PushVector(unsigned int value, TVector* vector)
{
    assert(vector->Count != vector->Max);
    vector->Array[vector->Count] = value;
    ++vector->Count;
}

void PrintVector(TVector vector)
{
    for (int i = 0; i < vector.Count; ++i)
    {
        PrintBits(vector.Array[i]);
        printf("\n");
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

TVector SpecialNumber(int n)
{
    TVector vector = CreateVector(n);
    if (n == 0)
    {
        return vector;
    }
    
    PushVector(0, &vector);
    int upperBit = 0;
    int index = 1;

    while (index < n)
    {
        for (int lowerBit = -1; lowerBit < upperBit; ++lowerBit, ++index)
        {
            if (index == n)
            {
                break;
            }

            int number = 1 << upperBit;
            number += (lowerBit == -1) ? 0 : (1 << lowerBit);
            PushVector(number, &vector);
        }

        ++upperBit;
    }
    
    
    return vector;
}

int main(void)
{
    TVector vector = SpecialNumber(100);
    PrintVector(vector);
    DestroyVector(&vector);
    return EXIT_SUCCESS;
}