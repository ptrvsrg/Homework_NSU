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

TList SplitList(TList list) 
{
    TList first = NULL;
    TList second = list;

    if(!IsEmptyList(second))
    {
        TValue lastValue;
        
        do
        {
            lastValue = second->Value;
            first = second;
            second = second->Next;
        } while (second && lastValue <= second->Value);
    }
    
    if (!IsEmptyList(first))
    {
        first->Next = NULL;
    }
    
    return second; 
}

TList MergeLists(TList list1, TList list2)
{
    if (!IsEmptyList(list1))
    {
        list1->Next = MergeLists(list1->Next, list2);
        return list1;
    }
    else if(!IsEmptyList(list2))
    {
        list2->Next = MergeLists(list1, list2->Next);
        return list2;
    }
    else if (IsEmptyList(list1))
    {
        return list2;
    }
    else
    {
        return list1;
    }
}

TList SplitByIncrease(TList* list)
{
    TList first = NULL;
    TList second = NULL;
    TList buffer = NULL;

    while(!IsEmptyList(*list))
    {
        buffer = SplitList(*list);
        first = MergeLists(first, *list);
        *list = buffer;

        if(!IsEmptyList(*list))
        {
            buffer = SplitList(*list);
            second = MergeLists(second, *list);
            *list = buffer;
        }
    }

    *list = second;
    return first;
}

int main(void)
{
    
    TValue array[] = { 1, 2, 3, 4, 2, 5, 7, 9, -1, -2, 0 };

    TList list = ConvertArrayToList(sizeof(array) / sizeof(*array), array);

    PrintList(list);
    printf("\n");

    PrintList(SplitByIncrease(&list));    
    printf("\n");
    
    PrintList(list);
    printf("\n");  

    FreeList(&list);

    return 0;
}