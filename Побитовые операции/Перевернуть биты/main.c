#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef unsigned char byte;

enum
{
	SUCCESS = 0,
	FAILURE = 1,
	BYTE_SIZE = 8
};

void PrintBits(unsigned int Symbol)
{
	printf("%d = ", Symbol);
	unsigned int Mask = ~0;
	Mask <<= 1;
	Mask >>= 1;
	Mask++;

	for (int i = 0; i < BYTE_SIZE * sizeof(unsigned int); i++)
	{
		printf("%d", ((Mask & Symbol) != 0) ? 1 : 0);
		Symbol <<= 1;

		if ((i % 4) == 3)
		{
			printf(" ");
		}

		if ((i % 8) == 7)
		{
			printf("  ");
		}
	}
}

byte ReverseBitsOfByte(byte Symbol, byte Mask, int Size)
{
	Size /= 2;

	byte Mask1 = Mask << Size & Mask;
	byte Mask2 = Mask >> Size & Mask;
	byte Symbol1 = (Symbol & Mask1) >> Size;
	byte Symbol2 = (Symbol & Mask2) << Size;

	if (((Mask - 1) & Mask) == 0)
	{
		return Symbol1 | Symbol2;
	}
	else
	{
		return ReverseBitsOfByte(Symbol1, Mask2, Size) | ReverseBitsOfByte(Symbol2, Mask1, Size);
	}
}

void GetArray(unsigned int object, byte Array[])
{
	unsigned int Mask = 255;

	for (int i = sizeof(object) - 1; i >= 0; i--)
	{
		Array[i] = ReverseBitsOfByte((byte)(object & Mask), ~0, BYTE_SIZE);
		object >>= 8;
	}
}

void ReverseArray(byte Array[])
{
	int ArraySize = sizeof(Array);
	byte Buffer;

	for (int i = 0; i < ArraySize / 2; i++)
	{
		Buffer = Array[i];
		Array[i] = Array[ArraySize - 1 - i];
		Array[ArraySize - 1 - i] = Buffer;
	}
}

unsigned int GetUnsignedInt(byte Array[])
{
	unsigned int Mask = 255;
	unsigned int Symbol = 0;

	for (int i = sizeof(Array) - 1; i >= 0; i--)
	{
		Symbol += Array[i] | Mask;
		Mask <<= 8;
	}

	return Symbol;
}

unsigned int ReverseBits(unsigned int Symbol)
{
	byte Array[sizeof(unsigned int)];
	GetArray(Symbol, Array);
	ReverseArray(Array);
	return GetUnsignedInt(Array);
}

int main()
{
	unsigned int Symbol;

	if (scanf("%d", &Symbol) == EOF)
	{
		return FAILURE;
	}

	PrintBits(Symbol);
	printf("\n");
	PrintBits(ReverseBits(Symbol));

	return SUCCESS;
}