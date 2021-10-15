#include "list.h"

struct TList
{
    unsigned int Value;
    struct TList* Next;
};

typedef struct TList* TList;
typedef struct TList* TItem;

TList CreateList()
{
    return NULL;
}

bool IsEmptyList(TList list)
{
    return list == NULL;
}

bool IsEmptyItem(TItem item)
{
    return item == NULL;
}

TItem GetBegin(TList list)
{
    return list;
}

TItem GetEnd(TList list)
{
    return NULL;
}

TItem GetNext(TItem item)
{
    assert(!IsEmptyItem(item));
    return item->Next;
}

int GetValue(TItem item)
{
    assert(!IsEmptyItem(item));
    return item->Value;
}

void SetValue(TItem item, int value)
{
    assert(!IsEmptyItem(item));
    item->Value = value;
}

void Remove(TList* list)
{
    TList removeElement = *list;
    *list = (*list)->Next;
    free(removeElement);
}

void FreeList(TList* list) 
{
    if(*list)
    {
        Remove(list);
        FreeList(list);
    }
}

void InsertItem(int value, TItem item, TList* list) //Before
{
    TItem newItem = malloc(sizeof(*newItem));
    assert(!IsEmptyItem(newItem));
    
}

bool FindList(int value, TList list)
{
    while(list)
    {
        if(list->Value > value)
        {
            return false;
        }
        else if(list->Value == value)
        {
            return true;
        }

        list = list->Next;
    }

    return false;
}

void PrintList(TList list)
{
    if(list)
    {
        printf("%d ", list->Value);
        PrintList(list->Next);
    }
}