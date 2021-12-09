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

TList PushBack(TValue value, TList list)
{
    if(!list)
    {
        PushFront(value, &list);
        return list;
    }

    while(list->Next)
    {
        list = list->Next;
    }

    list->Next = PushFront(value, &(list->Next));
    return list->Next;
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
    assert(*list);
    
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

void Rotate(TList* list)
{
    TValue value = PopFront(list);
    PushBack(value, *list);
}

int main(void)
{
    int array [] = { 1, 2, 3, 4 };

    TList list = ConvertArrayToList(sizeof(array) / sizeof(*array), array);

    assert(CheckNonDecreasing(list));

    PrintList(list);
    printf("\n");

    Rotate(&list);
    PrintList(list);
    printf("\n");

    FreeList(&list);

    return 0;
}