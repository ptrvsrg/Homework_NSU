#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Tlist
{
    unsigned int Value;
    struct Tlist* Next;
};

typedef struct Tlist* TList;

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

TList ReverseList(TList list)
{
    TList result = NULL;

    while(list)
    {
        Push(list->Value, &result);
        list = list->Next;
    }

    return result;
}

int main(void)
{
    TList list = NULL;
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ArrayToList(sizeof(array) / sizeof(*array), array, &list);
    PrintList(list);
    printf("\n");
    PrintList(ReverseList(list));
    printf("\n");

    FreeList(&list);

    return 0;
}