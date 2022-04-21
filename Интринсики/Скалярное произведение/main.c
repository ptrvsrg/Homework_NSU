#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>

float* ExpandArray(const float* array, int count)
{
    int countIter = (count + 3) / 4;

    float* expandedArray = calloc(countIter * 4, sizeof(expandedArray));
    assert(expandedArray != NULL);

    for (int i = 0; i < count; ++i)
    {
        expandedArray[i] = array[i];
    }
    
    return expandedArray;
}

float ScalarProduct(float* vector1, float* vector2, int count)
{
    int countIter = (count + 3) / 4;

    float* expandVector1 = ExpandArray(vector1, count);
    float* expandVector2 = ExpandArray(vector2, count);

    __m128 sum = _mm_setzero_ps();

    for (int i = 0; i < countIter; ++i)
    {
        __m128 coord1 = _mm_loadu_ps(expandVector1 + 4*i);
        __m128 coord2 = _mm_loadu_ps(expandVector2 + 4*i);
        __m128 mult = _mm_mul_ps(coord1, coord2);  
        sum = _mm_add_ps(mult, sum);
    }
    
    float arrayMult[4];
    _mm_store_ps(arrayMult, sum);

    free(expandVector1);
    free(expandVector2);

    return arrayMult[0] + arrayMult[1] + arrayMult[2] + arrayMult[3];
}

int main(void)
{
    float vector1[5] = { 1, 2, 4, 4, 5 };
    float vector2[5] = { 5, 4, 3, 2, 1 };

    float result = ScalarProduct(vector1, vector2, 5);

    printf("Scalar product is %.f\n", result);

    return 0;
}