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

TList CreateList()
{
    return NULL;
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

void CheckNonDecreasing(TList list)
{
    if(list == NULL || list->Next == NULL)
    {
        return;
    }
    
    assert(list->Value <= list->Next->Value);
    CheckNonDecreasing(list->Next);
}

TList MergeLists(TList list1, TList list2)
{
    if(list1 == NULL)
    {
        return list2;
    }
    else if(list2 == NULL)
    {
        return list1;
    }
    else if(list1->Value < list2->Value)
    {
        list1->Next = MergeLists(list1->Next, list2);
        return list1;
    }
    else
    {
        list2->Next = MergeLists(list1, list2->Next);
        return list2;
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

int main()
{
    TList list1 = CreateList();
    TList list2 = CreateList();

    CreateListOfDigits(135, &list1);
    CreateListOfDigits(17, &list2);

    CheckNonDecreasing(list1);
    CheckNonDecreasing(list2);

    PrintList(MergeLists(list1, list2));
    printf("\n");

    FreeList(&list1);
    FreeList(&list2);

    return 0;
}