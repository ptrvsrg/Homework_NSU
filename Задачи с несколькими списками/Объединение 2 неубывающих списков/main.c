#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

struct TList
{
    TValue Value;
    struct TList* Next;    
};

typedef struct TList* TList;

bool IsEmptyList(TList list)
{
    return list == NULL;
}

TList CreateItem(TValue value)
{
    TList new = malloc(sizeof(*new));
    assert(!IsEmptyList(new));

    new->Value = value;
    new->Next = NULL;
    
    return new;
}

TList PushFront(TValue value, TList* list)
{
    TList new = CreateItem(value);
    new->Next = *list;
    (*list) = new;

    return *list;
}

TList ConvertArrayToList(size_t arraySize, TValue* array)
{
    if (arraySize == 0)
    {
        return NULL;
    }

    TList list = CreateItem(*array);
    list->Next = ConvertArrayToList(arraySize - 1, array + 1);

    return list;
}

bool CheckNonDecreasing(TList list)
{
    if(IsEmptyList(list) || IsEmptyList(list->Next))
    {
        return true;
    }
    
    if(list->Value > list->Next->Value)
    {
        return false;
    }

    CheckNonDecreasing(list->Next);
}

TList MergeLists(TList list1, TList list2)
{
    if(IsEmptyList(list1))
    {
        return list2;
    }
    else if(IsEmptyList(list2))
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
    if(!IsEmptyList(list))
    {
        printf("%d ", list->Value);
        PrintList(list->Next);
    }
}

void FreeList(TList* list) 
{
    if(!IsEmptyList(*list))
    {
        FreeList(&((*list)->Next));
        free(*list);
    }
}

int main()
{
    TValue array1 [] = { 1, 2, 5, 8, 9 };
    TValue array2 [] = { 0, 3, 8 };

    TList list1 = ConvertArrayToList(sizeof(array1) / sizeof(*array1), array1);
    TList list2 = ConvertArrayToList(sizeof(array2) / sizeof(*array2), array2);

    assert(CheckNonDecreasing(list1));
    assert(CheckNonDecreasing(list2));

    PrintList(MergeLists(list1, list2));
    printf("\n");

    FreeList(&list1);
    FreeList(&list2);

    return 0;
}