#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool IsLess(const void* x1, const void* x2)
{
    const int* y1 = x1;
    const int* y2 = x2;
    return (*y1) < (*y2);
}

bool IsAscending(const void* array, int count, int size, bool (*f)(const void*, const void*))
{
    const char* newArray = array;

    for(int i = 0; i < count - 1; ++i)
    {
        if(f(&newArray[(i + 1) * size], &newArray[i * size]))
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int array[] = {
        0, 0, 1, 2
    };

    printf("%s\n", IsAscending(array, 4, sizeof(*array), IsLess) ? "YES" : "NO");

    return EXIT_SUCCESS;
}