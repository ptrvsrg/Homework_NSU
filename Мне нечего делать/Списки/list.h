#pragma

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
typedef struct TList* TItem;

TList CreateList();
bool IsEmptyList(TList list);
TItem GetBeginList(TList list);
TItem GetNextItem(TItem item);
size_t SizeList(TList list);
TItem GetEndList(TList list);
TItem GetIndexItem(size_t index, TList list);
TValue GetValueItem(TItem item);
void SetValueItem(TValue value, TItem item);
TItem InsertList(size_t index, TValue value, TList* list);
TItem PushFrontList(TValue value, TList* list);
TItem PushBackList(TValue value, TList* list);
TValue EraseList(size_t index, TList* list);
TValue PopFrontList(TList* list);
TValue PopBackList(TList* list);
void PrintList(TList list);
void ScanList(size_t size, TList* list);
void FreeList(TList* list);
void SwapLists(TList* list1, TList* list2);