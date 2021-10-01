#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1
};

void GenerateMultByConst(unsigned int Multiplier, unsigned int Position)
{
	if (Position == 0)
	{
		printf("void GenerateMultBy%d(unsigned int x)\n{\n\treturn ", Multiplier);
	}

	if (Multiplier == 0)
	{
		printf("0;");
	}
	else if (Multiplier < (1 << Position))
	{
		printf(";\n}\n");
	}
	else
	{
		if ((Multiplier & 1 << Position) != 0)
		{
			if (Position == 0)
			{
				printf("x");
			}
			else
			{
				printf(" + (x << %d)", Position);
			}
		}

		GenerateMultByConst(Multiplier, Position + 1);
	}
}

int main()
{
	unsigned int Multiplier;

	if (scanf("%u", &Multiplier) == EOF)
	{
		return FAILURE;
	}

	system("cls");

	GenerateMultByConst(Multiplier, 0);

	return SUCCESS;
}