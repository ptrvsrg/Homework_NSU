#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct TList
{
    int Value;
    struct TList* Next;    
};

typedef struct TList* TList;

TList CreateList()
{
    return NULL;
}

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

void CheckNonDecreasing(TList list)
{
    if(list == NULL || list->Next == NULL)
    {
        return;
    }
    
    assert(list->Value <= list->Next->Value);
    CheckNonDecreasing(list->Next);
}

void PrintList(TList list)
{
    if(list != NULL)
    {
        printf("%d ", list->Value);
        PrintList(list->Next);
    }
}

void Remove(TList* list)
{
    TList removeElem = *list;
    *list = (*list)->Next;
    free(removeElem);
}

void FreeList(TList* list) 
{
    if(*list != NULL)
    {
        Remove(list);
        FreeList(list);
    }
}

bool FindList(int value, TList list)
{
    while(list)
    {
        if(list->Value > value)
        {
            return false;
        }
        else if(list->Value == value)
        {
            return true;
        }

        list = list->Next;
    }

    return false;
}

void FilterList(TList* list, TList filter)
{
    if(*list && filter)
    {
        if(!FindList((*list)->Value, filter))
        {
            Remove(list);
            FilterList(list, filter);
        }
        else
        {
            FilterList(&((*list)->Next), filter);
        }
    }
}

int main()
{
    TList list = CreateList();
    TList filter = CreateList();

    int array1 [] = { 0, 1, 2, 5, 8, 9 };
    int array2 [] = { 1, 8 };

    ArrayToList(sizeof(array1) / sizeof(*array1), array1, &list);
    ArrayToList(sizeof(array2) / sizeof(*array2), array2, &filter);

    CheckNonDecreasing(list);
    CheckNonDecreasing(filter);

    PrintList(list);
    printf("\n");
    FilterList(&list, filter);
    PrintList(list);
    printf("\n");

    FreeList(&list);
    FreeList(&filter);

    return 0;
}