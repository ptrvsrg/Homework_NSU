#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MASK 0b10000000U
#define MAX_MASK 0b11111111U
#define BYTE_SIZE 8

typedef unsigned char byte_t;

void PrintBits(byte_t a)
{
    for (int i = 0; i < sizeof(byte_t) * BYTE_SIZE; ++i)
    {
        printf("%d", ((a & MASK) != 0) ? 1 : 0);
        a <<= 1;
    }
}

byte_t ChangeBits(byte_t x, byte_t y, int m)
{
    if (m < 0 || m > sizeof(byte_t) * BYTE_SIZE)
    {
        fprintf(stderr, "Wrong \"m\" value\n");
        exit(EXIT_FAILURE);
    }

    return (x >> m << m) | (y >> (sizeof(byte_t) * BYTE_SIZE - m));
}

byte_t InvertBits(byte_t y, int n)
{
    byte_t shiftedY = y << (sizeof(byte_t) * BYTE_SIZE - n);
    return  (MAX_MASK >> (sizeof(byte_t) * BYTE_SIZE - n)) ^ 
            (y >> n << n) ^
            (shiftedY >> (sizeof(byte_t) * BYTE_SIZE - n));
}

int main(int argc, char *argv[])
{
    byte_t x = 0;
    byte_t y = 0;
    int m = 0;
    int n = 0;
    
    if (argc == 1)
    {
        if (scanf("%hhu", &x) != 1 || scanf("%hhu", &y) != 1 || scanf("%d", &m) != 1 || scanf("%d", &n) != 1)
        {
            fprintf(stderr, "Read error\n");
            return EXIT_FAILURE;
        }
    }
    else if (argc == 5)
    {
        x = (byte_t)atoi(argv[1]);
        y = (byte_t)atoi(argv[2]);
        m = atoi(argv[3]);
        n = atoi(argv[4]);
    }
    else
    {
        fprintf(stderr, "Args error\n");
        return EXIT_FAILURE;
    }

    printf("x\t");
    PrintBits(x);
    printf("\t");
    PrintBits(ChangeBits(x, y, m));
    printf("\n");

    printf("y\t");
    PrintBits(y);
    printf("\t");
    
    PrintBits(InvertBits(y, n));
    printf("\n");

    return EXIT_SUCCESS;
}