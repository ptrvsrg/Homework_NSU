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

TValue PopNext(TList list)
{
    assert(list->next);

    TList removeElem = list->Next;
    TValue value = removeElem->Value;
    list->Next = list->Next->Next;
    free(removeElem);

    return value;
}

TList GetNth(size_t n, TList list)
{
    for(size_t i = 0; i < n; ++i)
    {
        list = list->Next;
    }

    return list;
}

void DeleteNth(size_t n, TList* list)
{
    if(n == 0)
    {
        PopFront(list);
    }
    else
    {
       PopNext(GetNth(n-1, *list));
    }
}

int main(void)
{
    TList list = NULL;
    int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ArrayToList(sizeof(array) / sizeof(*array), array, &list);
    PrintList(list);
    printf("\n");
    DeleteNth(5, &list);
    PrintList(list);
    printf("\n");
    FreeList(&list);

    return 0;
}