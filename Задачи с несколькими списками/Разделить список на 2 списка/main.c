#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct TList
{
    unsigned int Value;
    struct TList* Next;
};

typedef struct TList* TList;

void Push(int value, TList* list)
{
    TList new = malloc(sizeof(*new));
    assert(new != NULL);
    new->Value = value;
    new->Next = *list;
    (*list) = new;
}

void ArrayToList(size_t arraySize, int array[], TList* list)
{
    for(size_t i = 0; i < arraySize; ++i)
    {
        Push(array[arraySize - 1 - i], list);
    }
}

void PrintList(TList list)
{
    if(list)
    {
        printf("%d ", list->Value);
        PrintList(list->Next);
    }
}

void FreeList(TList* list) 
{
    if(*list)
    {
        FreeList(&((*list)->Next));
        free(*list);
    }
}

size_t LengthList(TList list)
{
    if(!list)
    {
        return 0;
    }
    else
    {
        return 1 + LengthList(list->Next);
    }
}

TList SplitList(TList* list) 
{
    TList first = NULL;
    TList second = *list;
    size_t length = LengthList(*list);

    for(size_t i = 0; i < length / 2; ++i)
    {
        first = second;
        second = second->Next;
    }
    
    if (first)
    {
        first->Next = NULL;
    }
    
    return second; 
  }

int main(void)
{
    TList list = NULL;
    int array[] = { 0, 1, 2, 3, 4 };

    ArrayToList(sizeof(array) / sizeof(*array), array, &list);
    PrintList(list);
    printf("\n");
    PrintList(SplitList(&list));
    printf("\n");
    PrintList(list);
    printf("\n");

    FreeList(&list);

    return 0;
}