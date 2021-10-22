#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

struct TList
{
    TValue Value;
    struct TList* Next;    
};

typedef struct TList* TList;

TList PushFront(TValue value, TList* list)
{
    TList new = malloc(sizeof(*new));
    assert(new != NULL);
    
    new->Value = value;
    new->Next = *list;
    (*list) = new;

    return *list;
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

void FilterList(TList* list, TList filter)
{
    if(!filter)
    {
        FreeList(list);
        *list = NULL;
    }

    if(*list)
    {
        if((*list)->Value < filter->Value)
        {
            PopFront(list);
            FilterList(list, filter);
        }
        else if((*list)->Value > filter->Value)
        {
            FilterList(list, filter->Next);
        }
        else
        {
            FilterList(&((*list)->Next), filter);
        }
    }
}

int main()
{
    TList list = NULL;
    TList filter = NULL;

    TValue arrayList [] = { 0, 1, 2, 5, 8, 9 };
    TValue arrayFilter [] = { 1, 4, 8 };

    ArrayToList(sizeof(arrayList) / sizeof(*arrayList), arrayList, &list);
    ArrayToList(sizeof(arrayFilter) / sizeof(*arrayFilter), arrayFilter, &filter);

    assert(CheckNonDecreasing(list));
    assert(CheckNonDecreasing(filter));

    PrintList(list);
    printf("\n");
    
    FilterList(&list, filter);
    PrintList(list);
    printf("\n");

    FreeList(&list);
    FreeList(&filter);

    return 0;
}