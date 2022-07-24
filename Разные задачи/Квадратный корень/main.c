#include <stdio.h>

float Fabs(float a)
{
    return (a >= 0) ? a : -a;
}

float Sqrt(float arg, float eps)
{
    float x = 1;
    float epsilon = 0;

    do
    {
        float newX = x / 2 + arg / (2 * x);
        epsilon = Fabs(x - newX);
        x = newX;
    } while (eps <= epsilon);
    
    return x;
}

int main(void)
{
    printf("%f", Sqrt(0.04F, 0.01F));
}