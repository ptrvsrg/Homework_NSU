#include <stdio.h>
#include <xmmintrin.h>

void TransposeMatrix4x4(const float* matrix, float* result)
{
    __m128 abcd = _mm_loadu_ps(matrix);
    __m128 efgh = _mm_loadu_ps(matrix + 4);
    __m128 ijkl = _mm_loadu_ps(matrix + 8);
    __m128 mnop = _mm_loadu_ps(matrix + 12);

    __m128 abij = _mm_movelh_ps(abcd, ijkl);
    __m128 efmn = _mm_movelh_ps(efgh, mnop);
    __m128 cdkl = _mm_movehl_ps(ijkl, abcd);
    __m128 ghop = _mm_movehl_ps(mnop, efgh);

    __m128 aebf = _mm_unpacklo_ps(abij, efmn);
    __m128 imjn = _mm_unpackhi_ps(abij, efmn);
    __m128 cgdh = _mm_unpacklo_ps(cdkl, ghop);
    __m128 kolp = _mm_unpackhi_ps(cdkl, ghop);

    __m128 aeim = _mm_movelh_ps(aebf, imjn);
    __m128 bfjn = _mm_movehl_ps(imjn, aebf);
    __m128 cgko = _mm_movelh_ps(cgdh, kolp);
    __m128 dhlp = _mm_movehl_ps(kolp, cgdh);

    _mm_storeu_ps(result, aeim);
    _mm_storeu_ps(result + 4, bfjn);
    _mm_storeu_ps(result + 8, cgko);
    _mm_storeu_ps(result + 12, dhlp);
}

void PrintMatrix4x4(float* matrix)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            printf("%.f ", matrix[4*i+j]);
        }

        printf("\n");
    }
}

int main(void)
{
    float matrix[16] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    };
    PrintMatrix4x4(matrix);
    printf("\n");

    float result[16];
    TransposeMatrix4x4(matrix, result);
    PrintMatrix4x4(result);

    return 0;
}