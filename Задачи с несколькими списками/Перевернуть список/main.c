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
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ArrayToList(sizeof(array) / sizeof(*array), array, &list);
    PrintList(list);
    printf("\n");
    ReverseList(&list);
    PrintList(list);
    printf("\n");

    FreeList(&list);

    return 0;
}