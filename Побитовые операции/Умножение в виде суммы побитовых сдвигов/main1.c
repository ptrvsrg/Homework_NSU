#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1
};

void GenerateMultByConst(unsigned int Multiplier)
{
    static unsigned int Position = 0;

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
			printf("(x << %d)", Position);

            if(Multiplier >= (1 << Position + 1))
            {
                printf(" + ");
            }
		}

        ++Position;
		GenerateMultByConst(Multiplier);
	}
}

int main()
{
	unsigned int Multiplier;

	if (scanf("%u", &Multiplier) == EOF)
	{
		return FAILURE;
	}

	//system("cls");

	GenerateMultByConst(Multiplier);

	return SUCCESS;
}