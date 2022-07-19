#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Tlist
{
    int Data;
    struct Tlist* Next;
};

typedef struct Tlist* TList;
typedef struct Tlist* TItem;

TList CreateList(void)
{
    return NULL;
}

bool IsEmptyList(TList list)
{
    return list == NULL;
}

TItem GetLastItem(TList list)
{
    TList firstItem = list;
    while (!IsEmptyList(list) && list->Next == firstItem)
    {
        list = list->Next;
    }
    
    return firstItem;
}

void PushList(int data, TItem item, TList* list)
{
    TItem newItem = malloc(sizeof(*newItem));
    assert(newItem != NULL);
    newItem->Data = data;

    if (IsEmptyList(*list))
    {
        newItem->Next = newItem;
        *list = newItem;
        return;
    }

    newItem->Next = item->Next;
    item->Next = newItem;
}

int PopList(TItem item, TList* list)
{
    assert(!IsEmptyList(*list));

    TItem removedItem = item->Next;
    int returnedData = removedItem->Data;

    if (item == item->Next)
    {
        *list = NULL;
    }
    else
    {
        item->Next = item->Next->Next;
    }

    free(removedItem);
    return returnedData;
}

void PrintList(TList list)
{
    TItem firstItem = list;
    do
    {
        printf("%d ", list->Data);
        list = list->Next;
    } while (firstItem != list);
}

void DestroyList(TList* list)
{
    if (IsEmptyList(*list))
    {
        return;
    }

    TList firstItem = *list;
    do
    {
        TItem nextItem = (*list)->Next;
        free(*list);
        *list = nextItem;
    } while (*list != firstItem);
}

int main(void)
{
    TList list = CreateList();

    PushList(1, list, &list);
    PushList(2, list, &list);
    PushList(3, list, &list);

    PrintList(list);

    printf("\n%d\n", PopList(list->Next, &list));

    PrintList(list);

    DestroyList(&list);

    return EXIT_SUCCESS;
}
