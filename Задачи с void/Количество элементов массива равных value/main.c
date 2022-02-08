#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool IsEqual(const void* x1, const void* x2)
{
    const int* y1 = x1;
    const int* y2 = x2;
    return (*y1) == (*y2);
}

int Count(const void* array, int count, int size, const void* value, bool (*f)(const void*, const void*))
{
    const char* newArray = array;
    int countElem = 0;

    for(int i = 0; i < count; ++i)
    {
        if(f(value, &newArray[i * size]))
        {
            ++countElem;
        }
    }

    return countElem;
}

int main(void)
{
    int array[] = {
        0, 1, 0, 2, 0, 3, 0
    };

    int value = 0;
    printf("%d\n", Count(array, 7, sizeof(*array), &value, IsEqual));

    return EXIT_SUCCESS;
}