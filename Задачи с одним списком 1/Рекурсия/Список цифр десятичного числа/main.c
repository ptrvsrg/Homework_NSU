#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int TValue;

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

void CreateListOfDigits(unsigned int number, TList* list)
{
    if(number < 10)
    {
        PushFront(number, list);
    }
    else
    {
        PushFront(number % 10, list);
        CreateListOfDigits(number / 10, list);
    }
}

int SumList(TList list)
{
    if(!list)
    {
        return 0;
    }
    else
    {
        return list->Value + SumList(list->Next);
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

int main(void)
{
    TList list = NULL;
    CreateListOfDigits(461148, &list);
    PrintList(list);
    printf("\n%d\n", SumList(list));
    FreeList(&list);
    return 0;
}