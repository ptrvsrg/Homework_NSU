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

    return CheckNonDecreasing(list->Next);
}

void PrintList(TList list)
{
    if(!IsEmptyList(list))
    {
        printf("%d ", list->Value);
        PrintList(list->Next);
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
    if(!IsEmptyList(*list))
    {
        PopFront(list);
        FreeList(list);
    }
}

void FilterList(TList* list, TList filter)
{
    if(IsEmptyList(filter))
    {
        FreeList(list);
        *list = NULL;
    }

    if(!IsEmptyList(*list))
    {
        if((*list)->Value < filter->Value)
        {
            PopFront(list);
            FilterList(list, filter);
        }
        else if((*list)->Value > filter->Value)
        {
            FilterList(list, filter->Next);
        }
        else
        {
            FilterList(&((*list)->Next), filter);
        }
    }
}

int main()
{
    TValue arrayList [] = { 0, 1, 2, 5, 8, 9 };
    TValue arrayFilter [] = { 1, 4, 8 };

    TList list = ConvertArrayToList(sizeof(arrayList) / sizeof(*arrayList), arrayList);
    TList filter = ConvertArrayToList(sizeof(arrayFilter) / sizeof(*arrayFilter), arrayFilter);

    assert(CheckNonDecreasing(list));
    assert(CheckNonDecreasing(filter));

    PrintList(list);
    printf("\n");
    
    FilterList(&list, filter);
    PrintList(list);
    printf("\n");

    FreeList(&list);
    FreeList(&filter);

    return 0;
}