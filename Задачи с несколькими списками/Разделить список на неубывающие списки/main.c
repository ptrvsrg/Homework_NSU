#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct TList
{
    int Value;
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
    if(*list)
    {
        FreeList(&((*list)->Next));
        free(*list);
    }
}

TList SplitList(TList* list) 
{
    TList first = NULL;
    TList second = *list;
    int lastValue;

    if(second)
    {
        do
        {
            lastValue = second->Value;
            first = second;
            second = second->Next;

            if (!second)
            {
                break;
            }
        } while (lastValue <= second->Value);
    }
    
    if (first)
    {
        first->Next = NULL;
    }
    
    return second; 
}

TList MergeLists(TList list1, TList list2)
{
    if (list1)
    {
        list1->Next = MergeLists(list1->Next, list2);
        return list1;
    }
    else if(list2)
    {
        list2->Next = MergeLists(list1, list2->Next);
        return list2;
    }
    else
    {
        if (list1 == NULL)
        {
            return list2;
        }
        else if (list2 == NULL)
        {
            return list1;
        }
    }
}

TList SplitByIncrease(TList* list)
{
    TList first = NULL;
    TList second = NULL;
    TList buffer = NULL;

    while(*list)
    {
        buffer = SplitList(list);
        first = MergeLists(first, *list);
        *list = buffer;

        if(*list)
        {
            buffer = SplitList(list);
            second = MergeLists(second, *list);
            *list = buffer;
        }
    }

    *list = second;
    return first;
}

int main(void)
{
    TList list = NULL;
    int array[] = { 4, 3, 2, 1, 2, 3, 1 };

    ArrayToList(sizeof(array) / sizeof(*array), array, &list);
    PrintList(list);
    printf("\n");
    PrintList(SplitByIncrease(&list));    
    printf("\n");
    PrintList(list);
    printf("\n");  

    FreeList(&list);

    return 0;
}