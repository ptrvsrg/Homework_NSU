#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TList* TList;

struct TList
{
    int Value;
    TList Next;
};

TList CreateList(void)
{
    return NULL;
}

bool IsEmptyList(TList list)
{
    return list == NULL;
}

void InputList(size_t listSize, TList* list)
{
	if(listSize == 0)
    {
        (*list) = NULL;
    }
    else
    {
        TList new = malloc(sizeof(*new));
        assert(!IsEmptyList(new));

        int control = scanf("%d", &(new->Value));
        assert(control != EOF);

        (*list) = new;
        InputList(listSize - 1, &((*list)->Next));
    }
}

void OutputList(TList list)
{
    if(!IsEmptyList(list))
    {
        printf("%d ", list->Value);
        OutputList(list->Next);
    }
}

void DestroyList(TList* list) 
{
    if(!IsEmptyList(*list))
    {
        DestroyList(&((*list)->Next));
        free(*list);
    }
}

TList MergeLists(TList list1, TList list2)
{
    if(IsEmptyList(list1))
    {
        return list2;
    }
    else if(IsEmptyList(list2))
    {
        return list1;
    }
    else if(list1->Value < list2->Value)
    {
        list1->Next = MergeLists(list1->Next, list2);
        return list1;
    }
    else
    {
        list2->Next = MergeLists(list1, list2->Next);
        return list2;
    }
}

void SplitList(TList list, TList* low, TList* high) 
{
    TList first = CreateList();
    TList second = CreateList();
 
    if (IsEmptyList(list) || IsEmptyList(list->Next))
    {
        (*low) = list;
        (*high) = NULL;
        return;
    }
 
    second = list;
    first = list->Next;
 
    while (!IsEmptyList(first)) 
    {
        first = first->Next;
        if (!IsEmptyList(first)) 
        {
            first = first->Next;
            second = second->Next;
        }
    }
 
    (*low) = list;
    (*high) = second->Next;
    second->Next = NULL;
}

void MergeSort(TList* list) 
{
    TList low = CreateList();
    TList high = CreateList();

    if (IsEmptyList(*list) || IsEmptyList((*list)->Next)) 
    {
        return;
    }

    SplitList(*list, &low, &high);
    MergeSort(&low);
    MergeSort(&high);
    (*list) = MergeLists(low, high);
}

int main(void)
{
	int listSize = 0;
	int control = scanf("%d", &listSize);
    assert(control != EOF);

	TList list = CreateList();
	InputList(listSize, &list);

	MergeSort(&list);
    
	OutputList(list);
	DestroyList(&list);
    
	return EXIT_SUCCESS;
}