#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define UNUSED(x) (void)(x)
#define SUCCESS_JUMP 1
static jmp_buf position;

//////////////////////////////////////// STATE TYPE ////////////////////////////////////////

typedef enum
{
    DELETED = -1,
    IMPOSSIBLE,
    POSSIBLE
} TState;

//////////////////////////////////////// SCAN / PRINT ////////////////////////////////////////

void PrintInt(void* value)
{
    int* newValue = value;
    printf("%d ", *newValue);
}

void ScanInt(void* value)
{
    int* newValue = value;
    int control = scanf("%d", newValue);
    UNUSED(control);
    assert(control == 1);
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

void PopBackVector(TVector* vector)
{
    assert(vector->Count != 0);
    --vector->Count;
}

void PrintVector(TVector vector, void (*Print)(void*))
{
    for (int i = 0; i < vector.Count; ++i)
    {
        Print((char*)vector.Array + i * vector.Size);
    }
}

void DestroyVector(TVector* vector)
{
    free(vector->Array);
    vector->Count = 0;
    vector->Max = 0;
    vector->Size = 0;
}

//////////////////////////////////////// CACHE ////////////////////////////////////////

TVector CreateCache(TVector stone)
{
    int* array = stone.Array;
    int maxJump = array[stone.Count - 1];

    TVector cache = CreateVector(sizeof(TState), maxJump * maxJump);
    cache.Count = maxJump * maxJump;

    bool* visitedTable = calloc(maxJump, sizeof(visitedTable));
    assert(visitedTable != NULL);

    for (int i = 0; i < stone.Count; ++i)
    {
        visitedTable[array[i] - 1] = true;
    }

    for (int i = 0; i < maxJump; ++i)
    {
        if (visitedTable[i] == false)
        {
            for (int j = 0; j < maxJump; ++j)
            {
                TState status = DELETED;
                int index = (i * maxJump + j) * cache.Size;
                AssignVector(sizeof(TState), &status, (char*)cache.Array + index);
            }
        }
    }
    
    free(visitedTable);

    return cache;
}

//////////////////////////////////////// JUMP ////////////////////////////////////////

bool IsJumpPossible(int stoneCoord, int jumpLen, int maxJump, TVector cache, TVector path);
bool Jump(int stoneNum, int jumpLen, int maxJump, TVector cache, TVector path);

bool IsJumpPossible(int stoneCoord, int jumpLen, int maxJump, TVector cache, TVector path)
{
    if (stoneCoord <= 0 || stoneCoord > maxJump || jumpLen <= 0 || jumpLen > maxJump)
    {
        return false;
    }
    
    TState* array = cache.Array;
    int index = maxJump * (stoneCoord - 1) + jumpLen - 1;
    
    if (array[index] == IMPOSSIBLE)
    {
        array[index] = POSSIBLE;
        return Jump(stoneCoord, jumpLen, maxJump, cache, path);
    }

    return array[index] == POSSIBLE;
}

bool Jump(int stoneNum, int jumpLen, int maxJump, TVector cache, TVector path)
{
    PushBackVector(&stoneNum, &path);

    if (stoneNum == maxJump)
    {
        PrintVector(path, PrintInt);
        longjmp(position, SUCCESS_JUMP);
    }
    
    int countPossibleJump = 0;

    countPossibleJump += IsJumpPossible(stoneNum - (jumpLen - 1), jumpLen - 1, maxJump, cache, path);
    countPossibleJump += IsJumpPossible(stoneNum - jumpLen, jumpLen, maxJump, cache, path);
    countPossibleJump += IsJumpPossible(stoneNum - (jumpLen + 1), jumpLen + 1, maxJump, cache, path);
    countPossibleJump += IsJumpPossible(stoneNum + (jumpLen - 1), jumpLen - 1, maxJump, cache, path);
    countPossibleJump += IsJumpPossible(stoneNum + jumpLen, jumpLen, maxJump, cache, path);
    countPossibleJump += IsJumpPossible(stoneNum + (jumpLen + 1), jumpLen + 1, maxJump, cache, path);

    PopBackVector(&path);

    return countPossibleJump != 0;
}

//////////////////////////////////////// MAIN ////////////////////////////////////////

int main(void)
{
    int stoneCount = 0;
    int control = scanf("%d", &stoneCount);
    UNUSED(control);
    assert(control == 1);
    
    TVector stone = ScanVector(sizeof(int), stoneCount, ScanInt);
    TVector cache = CreateCache(stone);

    int maxJump = ((int*)stone.Array)[stone.Count - 1];
    TVector path = CreateVector(sizeof(int), maxJump * maxJump);

    if (setjmp(position) == 0)
    {
        if (Jump(1, 1, maxJump, cache, path) == false)
        {
            printf("No solutions\n");
        }
    }

    DestroyVector(&stone);
    DestroyVector(&cache);
    DestroyVector(&path);

    return EXIT_SUCCESS;
}