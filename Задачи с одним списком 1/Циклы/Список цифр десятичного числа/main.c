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
    do
    {
        unsigned int digit = number % 10;
        number /= 10;
        PushFront(digit, list);
    } while (number != 0);
}

int SumList(TList list)
{
    int sum = 0;

    while(list)
    {
        sum += list->Value;
        list = list->Next;
    }

    return sum;
}

void PrintList(TList list)
{
    while(list)
    {
        printf("%d ", list->Value);
        list = list->Next;
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
    while(*list)
    {
        PopFront(list);
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
