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

void FreeList(TList* list) 
{
    if(!IsEmptyList(*list))
    {
        FreeList(&((*list)->Next));
        free(*list);
    }
}

TList ReverseList(TList list)
{
    TList result = NULL;

    while(!IsEmptyList(list))
    {
        PushFront(list->Value, &result);
        list = list->Next;
    }

    return result;
}

int main(void)
{
    
    TValue array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    TList list = ConvertArrayToList(sizeof(array) / sizeof(*array), array);
    PrintList(list);
    printf("\n");
    PrintList(ReverseList(list));
    printf("\n");
    FreeList(&list);

    return 0;
}