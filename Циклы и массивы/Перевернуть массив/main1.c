#include <stdio.h>

void Swap(int* Number1, int* Number2)
{
	int Buffer = *Number1;
	*Number1 = *Number2;
	*Number2 = Buffer;
}

int* ReverseArray(int Array[], int SizeOfArray)
{
	for (int i = 0; i < SizeOfArray / 2; i++)
	{
		Swap(&Array[SizeOfArray - i - 1], &Array[i]);
	}

	return Array;
}

void PrintArray(int* Array, int SizeOfArray)
{
	for (int i = 0; i < SizeOfArray; i++)
	{
		printf("Array[%d] = %d\n", i, Array[i]);
	}
}

int main()
{
	int Array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int SizeOfArray = sizeof(Array) / sizeof(*Array);
	PrintArray(Array, SizeOfArray);
	printf("\n\n");
	PrintArray(ReverseArray(Array, SizeOfArray), SizeOfArray);
	return 0;
}