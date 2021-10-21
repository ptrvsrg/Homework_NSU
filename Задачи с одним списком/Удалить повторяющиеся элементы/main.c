#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

struct Tlist
{
    TValue Value;
    struct Tlist* Next;    
};

typedef struct Tlist* TList;

void PushFront(TValue value, TList* list)
{
    TList new = malloc(sizeof(*new));
    assert(new != NULL);
    new->Value = value;
    new->Next = *list;
    (*list) = new;
}

void ArrayToList(size_t arraySize, TValue array[], TList* list)
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

void RemoveDupicate(TList* list)
{
    if(*list && (*list)->Next)
    {
        if((*list)->Value == (*list)->Next->Value)
        {
            PopFront(list);
            RemoveDupicate(list);
        }
        else
        {
            RemoveDupicate(&((*list)->Next));
        }
    }
}

int main(void)
{
    TList list = NULL;

    TValue array [] = { 1, 2, 2, 5, 8, 8, 9 };

    ArrayToList(sizeof(array) / sizeof(*array), array, &list);

    assert(CheckNonDecreasing(list));

    PrintList(list);
    printf("\n");
    RemoveDupicate(&list);
    PrintList(list);
    printf("\n");

    FreeList(&list);

    return 0;
}