#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

struct Tlist
{
    TValue Value;
    struct Tlist* Next;
};

typedef struct Tlist* TList;

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

void DeleteNth(size_t n, TList* list)
{
    assert(!IsEmptyList(*list));

    if(n == 0)
    {
        PopFront(list);
    }
    else
    {
       DeleteNth(n - 1, &((*list)->Next));
    }
}

int main(void)
{
    int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    TList list = ConvertArrayToList(sizeof(array) / sizeof(*array), array);

    PrintList(list);
    printf("\n");

    DeleteNth(2, &list);

    PrintList(list);
    printf("\n");

    FreeList(&list);

    return 0;
}