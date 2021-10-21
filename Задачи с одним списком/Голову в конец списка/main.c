#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

struct Tlist
{
    TValue Value;
    struct Tlist* Next;    
};

typedef struct Tlist* TList;

TList PushFront(TValue value, TList* list)
{
    TList new = malloc(sizeof(*new));
    assert(new != NULL);

    new->Value = value;
    new->Next = *list;
    (*list) = new;

    return *list;
}

void PushBack(TValue value, TList list)
{
    if(!list)
    {
        PushFront(value, &list);
        return;
    }

    while(list->Next)
    {
        list = list->Next;
    }

    list->Next = PushFront(value, &(list->Next));
}

void ArrayToList(size_t arraySize, int array[], TList* list)
{
    for(size_t i = 0; i < arraySize; ++i)
    {
        PushFront(array[arraySize - 1 - i], list);
    }
}

bool CheckNonDecreasing(TList list)
{
    if(!list || !list->Next)
    {
        return true;
    }

    if(list->Value > list->Next->Value)
    {
        return false;
    }

    CheckNonDecreasing(list->Next);
}

void PrintList(TList list)
{
    if(list)
    {
        printf("%d ", list->Value);
        PrintList(list->Next);
    }
}

TValue PopFront(TList* list)
{
    TList removeElem = *list;
    TValue value = removeElem->Value;
    *list = (*list)->Next;
    free(removeElem);
    return value;
}

void FreeList(TList* list) 
{
    if(*list)
    {
        PopFront(list);
        FreeList(list);
    }
}

void Rotate(TList* list)
{
    TValue value = PopFront(list);
    PushBack(value, *list);
}

int main(void)
{
    TList list = NULL;

    int array [] = { 1, 2, 3, 4 };

    ArrayToList(sizeof(array) / sizeof(*array), array, &list);

    assert(CheckNonDecreasing(list));

    PrintList(list);
    printf("\n");

    Rotate(&list);
    PrintList(list);
    printf("\n");

    FreeList(&list);

    return 0;
}