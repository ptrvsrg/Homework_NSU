#include <stdio.h>
#include <string.h>

void Swap(char* a, char* b)
{
    char buffer = *a;
    *a = *b;
    *b = buffer;
}

void ReverseArray(int begin, int end, char* array)
{
    for (int i = 0; i < (end - begin) / 2; ++i)
    {
        Swap(array + begin + i, array + end - 1 - i);
    }
}

int SearchSpace(int begin, int end, const char* string)
{
    for (int i = begin; i < end; ++i)
    {
        if (string[i] == ' ')
        {
            return i;
        }
    }
    
    return end;
}

void ReverseString(char* string)
{
    int length = (int)strlen(string);
    int begin = 0;
    int end = 0;

    ReverseArray(0, length, string);

    while (end < length)
    {
        end = SearchSpace(begin, length, string);
        ReverseArray(begin, end, string);
        begin = end + 1;
    }
}

int main(void)
{
    char string[] = "white sail lonely";

    printf("%s\n", string);
    ReverseString(string);
    printf("%s\n", string);

    return 0;
}