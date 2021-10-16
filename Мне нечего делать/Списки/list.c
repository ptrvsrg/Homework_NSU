#include "list.h"

TList CreateList()
{
    return NULL;
}

bool IsEmptyList(TList list)
{
    return list == NULL;
}

TItem GetBeginList(TList list)
{
    return list;
}

TItem GetNextItem(TItem item)
{
    assert(!IsEmptyList(item));
    return item->Next;
}

size_t SizeList(TList list)
{
    size_t size = 0;

    while(!IsEmptyList(list))
    {
        ++size;
        list = GetNextItem(list);
    }

    return size;
}

TItem GetEndList(TList list)
{
    if(IsEmptyList(list))
    {
        return NULL;
    }
    else
    {
        for(size_t i = 0; i < SizeList(list) - 1; ++i)
        {
            list = GetNextItem(list);
        }

        return list;
    }
}

TItem GetIndexItem(size_t index, TList list)
{
    assert(!IsEmptyList(list));

    for(size_t i = 0; i < index; ++i)
    {
        list = GetNextItem(list);
    }

    return list;
}

TValue GetValueItem(TItem item)
{
    assert(!IsEmptyList(item));
    return item->Value;
}

void SetValueItem(TValue value, TItem item)
{
    assert(!IsEmptyList(item));
    item->Value = value;
}

TItem InsertList(size_t index, TValue value, TList* list)
{
    TItem newItem = malloc(sizeof(*newItem));
    assert(newItem != NULL);

    SetValueItem(value, newItem);

    if(index == 0)
    {
        TList savedList = *list;
        *list = newItem;
        newItem->Next = savedList;
    }
    else
    {
        TItem item = GetIndexItem(index - 1, *list);
        newItem->Next = GetNextItem(item);
        item->Next = newItem;
    }

    return newItem;
}

TItem PushFrontList(TValue value, TList* list)
{
    return InsertList(0, value, list);
}

TItem PushBackList(TValue value, TList* list)
{
    return InsertList(SizeList(*list), value, list);
}

TValue EraseList(size_t index, TList* list)
{
    assert(!IsEmptyList(*list));
    TItem removeItem = NULL;

    if(index == 0)
    {
        removeItem = *list;
        *list = GetNextItem(*list);
    }
    else
    {
        TItem item = GetIndexItem(index - 1, *list);
        removeItem = GetNextItem(item);
        item->Next = GetNextItem(item->Next);
    }

    TValue value = GetValueItem(removeItem);
    free(removeItem);

    return value;
}

TValue PopFrontList(TList* list)
{
    return EraseList(0, list);
}

TValue PopBackList(TList* list)
{
    return EraseList(SizeList(*list) - 1, list);
}

void PrintList(TList list)
{
    while(!IsEmptyList(list))
    {
        assert(printf("%d ", GetValueItem(list)) > 0);
        list = GetNextItem(list);
    }
}

void ScanList(size_t size, TList* list)
{
    for(size_t i = 0; i < size; ++i)
    {
        TValue value;
        assert(scanf("%d", &value) != EOF);
        PushBackList(value, list);
    }
}

void FreeList(TList* list)
{
    while(!IsEmptyList(*list))
    {
        PopFrontList(list);
    }
}

void SwapLists(TList* list1, TList* list2)
{
    TList buffer = *list1;
    *list1 = *list2;
    *list2 = buffer;
}