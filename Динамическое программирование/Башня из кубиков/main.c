#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define IMPOSSIBLE -1
#define MAX_CUBE_COUNT 1000

//////////////////////////////////////// ADDITIONAL FUNCTION ////////////////////////////////////////

int Min(int a, int b)
{
    return (a <= b) ? a : b;
}

int Max(int a, int b)
{
    return (a <= b) ? b : a;
}

int SumArithmeticProgression(int index1, int index2, int count)
{
    return (index1 + index2) * count / 2;
}

int GetIndexTriangleMatrix(int row, int column, int size)
{
    int min = Min(row, column);
    int max = Max(row, column);

    return SumArithmeticProgression(size, size - min + 1, min) + (max - min);
}

bool CompareInt(void* a, void* b)
{
    return *((int*)a) < *((int*)b);
}

//////////////////////////////////////// VECTOR TYPE ////////////////////////////////////////

typedef struct
{
    int Count;
    int Max;
    int Size;
    void* Array;
} TVector;

TVector CreateVector(int size, int max)
{
    TVector vector = { 0, max, size, NULL };

    vector.Array = calloc(max, size);
    assert(vector.Array != NULL);

    return vector;
}

void AssignVector(int size, void* src, void* dest)
{
    for (int i = 0; i < size; ++i)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

void PushBackVector(void* value, TVector* vector)
{
    assert(vector->Count != vector->Max);
    int index = vector->Count * vector->Size;

    AssignVector(vector->Size, value, (char*)vector->Array + index);
    
    ++vector->Count;
}

TVector ScanVector(int size, int count, void (*Scan)(void*))
{
    TVector vector = CreateVector(size, count);

    void* value = malloc(size);
    assert(value != NULL);

    for (int i = 0; i < count; ++i)
    {
        Scan(value);
        PushBackVector(value, &vector);
    }

    free(value);
    return vector;
}

void* FindMax(TVector vector, bool (*Compare)(void*, void*))
{
    char* vectorArray = vector.Array;
    char* max = vectorArray;

    for (int i = 1; i < vector.Count; ++i)
    {
        if (Compare(max, vectorArray + i * vector.Size))
        {
            max = vectorArray + i * vector.Size;
        }
    }

    return max;
}

void DestroyVector(TVector* vector)
{
    free(vector->Array);
    vector->Count = 0;
    vector->Max = 0;
    vector->Size = 0;
}

//////////////////////////////////////// CUBE TYPE ////////////////////////////////////////

typedef struct
{
    int X;
    int Y;
    int Z;
} TCube;

void ScanCube(void* value)
{
    TCube* newValue = value;
    int control = scanf("%d%d%d", &newValue->X, &newValue->Y, &newValue->Z);
    assert(control == 3);
}

bool CompareTCube(void* a, void* b)
{
    TCube* cube1 = (TCube*)a;
    TCube* cube2 = (TCube*)b;
    return Max(cube1->X, Max(cube1->Y, cube1->Z)) < Max(cube2->X, Max(cube2->Y, cube2->Z));
}

int GetCubeHeight(int x, int y, TVector cubes)
{
    int height = 0;
    TCube* cubeArray = cubes.Array;

    for (int i = 0; i < cubes.Count; ++i)
    {
        if ((cubeArray[i].X == x && cubeArray[i].Y == y) || (cubeArray[i].Y == x && cubeArray[i].X == y))
        {
            height = Max(height, cubeArray[i].Z);
        }

        if ((cubeArray[i].X == x && cubeArray[i].Z == y) || (cubeArray[i].Z == x && cubeArray[i].X == y))
        {
            height = Max(height, cubeArray[i].Y);
        }

        if ((cubeArray[i].Z == x && cubeArray[i].Y == y) || (cubeArray[i].Y == x && cubeArray[i].Z == y))
        {
            height = Max(height, cubeArray[i].X);
        }
    }

    return height;
}

//////////////////////////////////////// CACHE ////////////////////////////////////////

TVector CreateCache(TVector cubes, int size)
{
    TVector cache = CreateVector(sizeof(int), SumArithmeticProgression(1, size, size));
    cache.Count = SumArithmeticProgression(1, size, size);

    int* cacheArray = cache.Array;

    for (int i = 0; i < cache.Count; ++i)
    {
        cacheArray[i] = IMPOSSIBLE;
    }
    
    TCube* cubeArray = cubes.Array;

    for (int i = 0; i < cubes.Count; ++i)
    {
        int x = cubeArray[i].X - 1;
        int y = cubeArray[i].Y - 1;
        int z = cubeArray[i].Z - 1;

        int index1 = GetIndexTriangleMatrix(x, y, size);
        int index2 = GetIndexTriangleMatrix(x, z, size);
        int index3 = GetIndexTriangleMatrix(y, z, size);

        cacheArray[index1] = 0;
        cacheArray[index2] = 0;
        cacheArray[index3] = 0;
    }

    return cache;
}

//////////////////////////////////////// MAX CUBE TOWER HEIGHT ////////////////////////////////////////

void MaxCubeTowerHeight(int x, int y, int height, int size, TVector cubes, TVector cache)
{
    int* cacheArray = cache.Array;
    int minIndex = Min(x, y);
    int maxIndex = Max(x, y);
    
    for (int i = 0; i < maxIndex && i < size; ++i)
    {
        for (int j = 0; j <= i && j < minIndex; ++j)
        {
            if (i == x - 1 && j == y - 1)
            {
                break;
            }

            int index = GetIndexTriangleMatrix(i, j, size);

            if (cacheArray[index] != IMPOSSIBLE)
            {
                int z = GetCubeHeight(i + 1, j + 1, cubes);

                if (cacheArray[index] < height + z)
                {
                    cacheArray[index] = height + z;
                    MaxCubeTowerHeight(i + 1, j + 1, height + z, size, cubes, cache);
                }
            }
        }
    }
}

//////////////////////////////////////// MAIN ////////////////////////////////////////

int main(void)
{
    FILE* in = freopen("in.txt", "r", stdin);
    assert(in != NULL);

    int cubeCount = 0;
    int control = scanf("%d", &cubeCount);
    assert(control == 1);

    if (cubeCount >= MAX_CUBE_COUNT)
    {
        printf("Bad cube count\n");
        return EXIT_FAILURE;
    }
    
    TVector cubes = ScanVector(sizeof(TCube), cubeCount, ScanCube);

    TCube* maxCube = FindMax(cubes, CompareTCube);
    int size = Max(maxCube->X, Max(maxCube->Y, maxCube->Z));

    TVector cache = CreateCache(cubes, size);

    MaxCubeTowerHeight(size + 1, size + 1, 0, size, cubes, cache);

    int* maxHeight = FindMax(cache, CompareInt);
    printf("Max height is %d\n", *maxHeight);

    fclose(in);
    DestroyVector(&cubes);
    DestroyVector(&cache);

    return EXIT_SUCCESS;
}