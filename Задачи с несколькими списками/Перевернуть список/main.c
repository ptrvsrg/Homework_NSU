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

void PrintList(TList list)
{
    if(list != NULL)
    {
        printf("%d ", list->Value);
        PrintList(list->Next);
    }
}

void FreeList(TList* list) 
{
    if(list != NULL)
    {
        FreeList(&((*list)->Next));
        free(list);
    }
}

void ReverseList(TList* list)
{
    TList result = CreateList();

    while (*list != NULL)
    {
        TList buffer = (*list)->Next;
        (*list)->Next = result;
        result = *list;
        (*list) = buffer;
    }

    (*list) = result;
}

int main(void)
{
    TList list = CreateList();
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ArrayToList(9, array, &list);
    PrintList(list);
    printf("\n");
    ReverseList(&list);
    PrintList(list);
    printf("\n");

    FreeList(&list);
}