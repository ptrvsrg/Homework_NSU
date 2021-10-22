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

void ReverseList(TList* list)
{
    if (!(*list) || !(*list)->Next)
    {
        return;
    }

    TList current = *list;
    TList next;
    TList result = NULL;

    while(current)
    {
        next = current->Next;
        current->Next = result;
        result = current;
        current = next;
    }

    *list = result;
}

int main(void)
{
    TList list = NULL;
    TValue array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ArrayToList(sizeof(array) / sizeof(*array), array, &list);
    PrintList(list);
    printf("\n");
    ReverseList(&list);
    PrintList(list);
    printf("\n");
    FreeList(&list);

    return 0;
}