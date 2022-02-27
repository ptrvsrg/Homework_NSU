#include <stdio.h>

int DividerCount(int number)
{
    int power2 = 0;

    while (number & 1 == 0) 
    {
        number >>= 1;
        ++power2;
    }

    return 2 * (power2 + 1);    
}

void isPerfect(int divider, int* sum, int num) 
{
    if (divider == 0)
    {
        /* code */
    }
    
    if (num % divider == 0)
    {
        *sum += divider;
        --divider;
    }
}

int main(void)
{

}