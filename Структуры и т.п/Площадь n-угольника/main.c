#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

enum
{
    SUCCESS = 0,
    FAILURE = -1
};

typedef struct TPoint2D
{
    float X;
    float Y;
} TPoint2D;

float Fabs(float x)
{
    return (x >= 0) ? x : -x;
}

TPoint2D GetVector(TPoint2D pointA, TPoint2D pointB)
{
    TPoint2D AB;
    AB.X = pointB.X - pointA.X;
    AB.Y = pointB.Y - pointA.Y;
    return AB;
}

float VectorProduct(TPoint2D vectorAB, TPoint2D vectorBC)
{
    return vectorAB.X * vectorBC.Y - vectorAB.Y * vectorBC.X;
}

bool ConvexCheck(size_t arraySize, TPoint2D* array)
{
    for(size_t i = 0; i < arraySize - 2; ++i)
    {
        if(VectorProduct(GetVector(array[i], array[i + 1]), GetVector(array[i + 1], array[i + 2])) > 0)
        {
            return false;
        }
    }

    return true;
}

float GaussArea(size_t arraySize, TPoint2D* array)
{
    if(arraySize >= 0 && arraySize <= 2)
    {
        return 0.0;
    }
    
    assert(ConvexCheck(arraySize, array));

    float sum = 0.0;

    for(int i = 0; i < arraySize - 1; i++)
    {
        sum += array[i + 1].X * array[i].Y - array[i + 1].Y * array[i].X;
    }

    sum += array[0].X * array[arraySize - 1].Y - array[0].Y * array[arraySize - 1].X;
    sum /= 2;

    return sum;
}

float AreaByTriangulation(size_t arraySize, TPoint2D* array)
{
    if(arraySize >= 0 && arraySize <= 2)
    {
        return 0.0;
    }
    
    assert(ConvexCheck(arraySize, array));

    float sum = 0.0;

    for(int i = 1; i < arraySize - 1; i++)
    {
        sum += Fabs(VectorProduct(GetVector(array[0], array[i]), GetVector(array[0], array[i + 1])));
    }

    sum /= 2;

    return sum;
}

int main()
{
    TPoint2D array[] = {
        {2, 0},
        {0, 0},
        {0, 2},
        {2, 2},
        {4, 1}
    };
    printf("Area Gauss is %.f\n", GaussArea(sizeof(array) / sizeof(*array), array));
    printf("Area by triangulation is %.f\n", AreaByTriangulation(sizeof(array) / sizeof(*array), array));
    return SUCCESS;
}
