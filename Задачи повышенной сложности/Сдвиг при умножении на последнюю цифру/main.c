#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int64_t GenerateNumber(int64_t lastDigit)
{
    int64_t position = 1;
    int64_t number = 0;
    int64_t result = 0;
    int64_t digit = 0;
    
    do
    {
        if (number < 0)
        {
            return -1;
        }

        number = result * 10 + lastDigit;
        result = (number * lastDigit) % (position * 10);
        digit = (number * lastDigit) / position;
        position *= 10;
    } while (digit != lastDigit);
    
    return number;
}

int64_t main(void)
{
    for (int64_t i = 0; i < 10; ++i)
    {
        int64_t number = GenerateNumber(i);

        if (number == -1)
        {
            printf("No such number\n");
        }
        else
        {
            printf("%lld * %lld = %lld\n", number, i, number * i);
        }
    }
    
    return EXIT_SUCCESS;
}