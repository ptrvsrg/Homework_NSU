#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1,
	BYTE_SIZE = 8,
    INT_BYTE = 4
};

void Swap(char* A, char* B)
{
	char Buffer = *A;
	*A = *B;
	*B = Buffer;
}

void PrintBits(unsigned int Symbol)
{
	printf("%u =", Symbol);
    unsigned int Mask = ~0;
	Mask >>= 1;
	Mask = ~Mask;

	for (int i = 0; i < BYTE_SIZE * INT_BYTE; ++i)
	{
		if (i % BYTE_SIZE == 0)
		{
			printf(" ");
		}

		printf("%d", ((Mask & Symbol) != 0) ? 1 : 0);
		Symbol <<= 1;
	}
}

unsigned char* IntToCharArray(unsigned int number)
{
    unsigned char Mask = ~0;
    unsigned char* Array = malloc(4 * sizeof(*Array));

    for(int i = INT_BYTE - 1; i >= 0; i--)
    {
        Array[i] = Mask & number;
        number >>= BYTE_SIZE;
    }

    return Array;
}

unsigned int CharArrayToInt(unsigned char* Array)
{
    unsigned int Number = 0;

    for(size_t i = 0; i < INT_BYTE; ++i)
    {
        Number <<= BYTE_SIZE;
        Number |= Array[i];
    }

    return Number;
}

unsigned char ReverseCharBits(unsigned char Symbol, unsigned char Mask, int Size)
{
	Size /= 2;

	unsigned char Mask1 = Mask << Size & Mask;
	unsigned char Mask2 = Mask >> Size & Mask;
	unsigned char Symbol1 = (Symbol & Mask1) >> Size;
	unsigned char Symbol2 = (Symbol & Mask2) << Size;

	if (((Mask - 1) & Mask) == 0)
	{
		return Symbol1 | Symbol2;
	}
	else
	{
		return ReverseCharBits(Symbol1, Mask2, Size) | ReverseCharBits(Symbol2, Mask1, Size);
	}
}

void ReverseArray(unsigned char* Array)
{
    for(size_t i = 0; i < INT_BYTE / 2; ++i)
    {
        Swap(&(Array[i]), &(Array[INT_BYTE - 1 - i]));
    }
}

unsigned int ReverseIntBits(unsigned int Number)
{
    unsigned char* Array = IntToCharArray(Number);

    for(size_t i = 0; i < INT_BYTE; ++i)
    {
        Array[i] = ReverseCharBits(Array[i], ~0, BYTE_SIZE);
    }

    ReverseArray(Array);
    return CharArrayToInt(Array);
}

int main()
{
	unsigned int Number;

	if (scanf("%d", &Number) == EOF)
	{
		return FAILURE;
	}

	PrintBits(Number);
	printf("\n");
	PrintBits(ReverseIntBits(Number));
    printf("\n");

    system("pause");
	return SUCCESS;
}