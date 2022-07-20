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

void RemoveDuplicate(TList* list)
{
    if(!IsEmptyList(*list) && !IsEmptyList((*list)->Next))
    {
        if((*list)->Value == (*list)->Next->Value)
        {
            PopFront(list);
            RemoveDuplicate(list);
        }
        else
        {
            RemoveDuplicate(&((*list)->Next));
        }
    }
}

int main(void)
{
    TValue array [] = { 1, 2, 2, 5, 8, 8, 9 };

    TList list = ConvertArrayToList(sizeof(array) / sizeof(*array), array);

    assert(CheckNonDecreasing(list));

    PrintList(list);
    printf("\n");
    
    RemoveDuplicate(&list);
    PrintList(list);
    printf("\n");

    FreeList(&list);

    return 0;
}