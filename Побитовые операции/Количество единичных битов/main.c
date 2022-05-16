#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1,
	UNSIGNED_INT_SIZE = 32
};

void PrintBits(unsigned int Number)
{
    printf("%u = ", Number);

	for (int i = 0; i < UNSIGNED_INT_SIZE; i++)
	{
		if (i % 8 == 0)
		{
			printf(" ");
		}

		printf("%d", ((1 << (UNSIGNED_INT_SIZE - 1) & Number) != 0) ? 1 : 0);
		Number <<= 1;
	}
}

int PopulationCount(unsigned int Number, unsigned int Mask, unsigned int Size)
{
	if (Number == 0)
	{
		return 0;
	}
	else if (((Number - 1) & Number) == 0)
	{
		return 1;
	}
	else
	{
		Size /= 2;

		unsigned int Mask1 = Mask << Size & Mask;
		unsigned int Mask2 = Mask >> Size & Mask;
		unsigned int Number1 = Number & Mask1;
		unsigned int Number2 = Number & Mask2;
 
		return PopulationCount(Number1, Mask1, Size) + PopulationCount(Number2, Mask2, Size);
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	unsigned int Number;

	if (scanf("%u", &Number) == EOF)
	{
		return FAILURE;
	}
    
	PrintBits(Number);
	printf("\nCount of single bits is %d", PopulationCount(Number, ~0, UNSIGNED_INT_SIZE));

	return SUCCESS;
}