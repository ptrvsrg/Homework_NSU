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
    if(list != NULL)
    {
        printf("%d ", list->Value);
        PrintList(list->Next);
    }
}

void FreeList(TList* list) 
{
    if(*list != NULL)
    {
        FreeList(&((*list)->Next));
        free(*list);
    }
}

void ReverseList(TList* list)
{
    if (*list == NULL || (*list)->Next == NULL)
    {
        return;
    }

    TList current, next, result = NULL;
    current = *list;

    while(current != NULL)
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
    int array[] = { 1, 2, 3, 4 };

    ArrayToList(sizeof(array) / sizeof(*array), array, &list);
    PrintList(list);
    printf("\n");
    ReverseList(&list);
    PrintList(list);
    printf("\n");

    FreeList(&list);
}