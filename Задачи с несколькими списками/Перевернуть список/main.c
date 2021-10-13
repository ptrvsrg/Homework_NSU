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

TList ReverseList(TList list, TList resultList)
{
    TList bufferList;
    if(list->Next == NULL) 
    {
        list->Next = resultList;
        return list;
    } 
    else 
    {
        bufferList = ReverseList(list->Next, list);
        list->Next = resultList;
        resultList = bufferList;
        return resultList;
    }
}

int main(void)
{
    TList list = CreateList();
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ArrayToList(9, array, &list);
    PrintList(list);
    printf("\n");
    PrintList(ReverseList(list, NULL));
    printf("\n");

    FreeList(list);
}