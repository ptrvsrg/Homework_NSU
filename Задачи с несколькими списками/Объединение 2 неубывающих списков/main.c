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

TList MergeLists(TList list1, TList list2)
{
    if(!list1)
    {
        return list2;
    }
    else if(!list2)
    {
        return list1;
    }
    else if(list1->Value < list2->Value)
    {
        list1->Next = MergeLists(list1->Next, list2);
        return list1;
    }
    else
    {
        list2->Next = MergeLists(list1, list2->Next);
        return list2;
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

int main()
{
    TList list1 = NULL;
    TList list2 = NULL;

    TValue array1 [] = { 1, 2, 5, 8, 9 };
    TValue array2 [] = { 0, 3, 8 };

    ArrayToList(sizeof(array1) / sizeof(*array1), array1, &list1);
    ArrayToList(sizeof(array2) / sizeof(*array2), array2, &list2);

    assert(CheckNonDecreasing(list1));
    assert(CheckNonDecreasing(list2));

    PrintList(MergeLists(list1, list2));
    printf("\n");

    FreeList(&list1);
    FreeList(&list2);

    return 0;
}