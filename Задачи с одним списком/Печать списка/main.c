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

bool IsEmpty(TList list)
{
    return list == NULL;
}

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

    while(!IsEmpty(list))
    {
        sum += list->Value;
        list = list->Next;
    }

    return sum;
}

void PrintList(TList list)
{
    while(!IsEmpty(list))
    {
        printf("%d ", list->Value);
        list = list->Next;
    }
}

void FreeList(TList* list) 
{
    TList buffer = NULL;

    while ((*list)->Next) 
    {
        buffer = (*list);
        (*list) = (*list)->Next;
        free(buffer);
    }

    free(*list);
}

int main(void)
{
    TList list = CreateList();
    CreateListOfDigits(461148, &list);
    PrintList(list);
    printf("\n%d\n", SumList(list));
    FreeList(&list);
    return 0;
}