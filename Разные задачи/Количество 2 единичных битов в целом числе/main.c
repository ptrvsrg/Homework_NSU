#include <stdbool.h>
#include <stdio.h>

int CountDoubleOneBits(unsigned int number)
{
    bool first = false;
    int count = 0;

    while(number > 0)
    {
        if(number & 1 != 0)
        {
            if(!first)
            {
                first = true;
            }
            else
            {
                ++count;
            }
        }
        else
        {
            first = false;
        }

        number >>= 1;
    }

    return count;
}

int main(void)
{
    printf("%d\n", CountDoubleOneBits(111));
    return 0;
}