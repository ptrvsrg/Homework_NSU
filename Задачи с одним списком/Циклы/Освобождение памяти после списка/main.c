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

void Push(unsigned int value, TList* list)
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
        Push(digit, list);
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

void Remove(TList* list)
{
    TList removeElem = *list;
    *list = (*list)->Next;
    free(removeElem);
}

void FreeList(TList* list) 
{
    while(*list)
    {
        Remove(list);
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
