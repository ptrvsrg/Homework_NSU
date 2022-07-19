#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Tlist
{
    int Data;
    struct Tlist* Previous;
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

void PushAfterList(int data, TItem item, TList* list)
{
    TItem newItem = malloc(sizeof(*newItem));
    assert(newItem != NULL);

    newItem->Data = data;

    if (*list == NULL)
    {
        newItem->Previous = newItem;
        newItem->Next = newItem;
        *list = newItem;
        return;
    }

    TItem afterItem = item->Next;

    newItem->Previous = item;
    newItem->Next = afterItem;
    item->Next = newItem;
    afterItem->Previous = newItem;
}

void PushBeforeList(int data, TItem item, TList* list)
{
    TItem newItem = malloc(sizeof(*newItem));
    assert(newItem != NULL);

    newItem->Data = data;

    if (*list == NULL)
    {
        newItem->Previous = newItem;
        newItem->Next = newItem;
        *list = newItem;
        return;
    }

    TItem beforeItem = item->Previous;

    newItem->Previous = beforeItem;
    newItem->Next = item;
    beforeItem->Next = newItem;
    item->Previous = newItem;
}

int PopList(TItem removedItem, TList* list)
{
    assert(!IsEmptyList(*list));

    TItem beforeItem = removedItem->Previous;
    TItem afterItem = removedItem->Next;
    int returnedData = removedItem->Data;

    if (removedItem == afterItem)
    {
        *list = NULL;
    }
    else
    {
        beforeItem->Next = afterItem;
        afterItem->Previous = beforeItem;
    }

    free(removedItem);
    return returnedData;
}

void PrintList(TList list)
{
    if (IsEmptyList(list))
    {
        return;
    }

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

    PushAfterList(1, list, &list);
    PushAfterList(2, list, &list);
    PushBeforeList(3, list, &list);

    PrintList(list);

    printf("\n%d\n", PopList(list->Next, &list));

    PrintList(list);

    DestroyList(&list);

    return EXIT_SUCCESS;
}
