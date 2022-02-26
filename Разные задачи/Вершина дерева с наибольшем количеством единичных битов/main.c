#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define UINT_SIZE 8*sizeof(unsigned int)

typedef unsigned int TValue;
typedef struct Tlist* TList;
typedef struct Ttree* TTree;

//////////////////// TREE TYPE ////////////////////

struct Ttree
{
    TValue Value;
    TList Children;
};

bool IsEmptyTree(TTree tree)
{
    return tree == NULL;
}

TTree CreateTree(TValue value, TList list)
{
    TTree tree = malloc(sizeof(*tree));
    assert(!IsEmptyTree(tree));

    tree->Value = value;
    tree->Children = list;

    return tree;
}

//////////////////// TREE LIST TYPE ////////////////////

struct Tlist
{
    TTree Tree;
    TList Next;
};

bool IsEmptyList(TList list)
{
    return list == NULL;
}

TList CreateItem(TTree tree)
{
    TList list = malloc(sizeof(*list));
    assert(!IsEmptyList(list));

    list->Tree= tree;
    list->Next = NULL;

    return list;
}

void PushList(TTree tree, TList* list)
{
    TList new = CreateItem(tree);
    new->Next = *list;
    (*list) = new;
}

TList ConvertArrayToList(int arraySize, TTree* array)
{
    if(arraySize <= 0)
    {
        return NULL;
    }

    TList list = CreateItem(*array);
    list->Next = ConvertArrayToList(arraySize - 1, array + 1);

    return list;
}

//////////////////// SINGLE BITS COUNT ////////////////////

int PopulationCount(TValue Number, TValue Mask, size_t Size)
{
	if (Number == 0)
	{
		return 0;
	}
	else if (((Number - 1) & Number) == 0)
	{
		return 1;
	}
	else
	{
		Size /= 2;

		TValue Mask1 = Mask << Size & Mask;
		TValue Mask2 = Mask >> Size & Mask;
		TValue Number1 = Number & Mask1;
		TValue Number2 = Number & Mask2;

		return PopulationCount(Number1, Mask1, Size) + PopulationCount(Number2, Mask2, Size);
	}
}

//////////////////// FIND MAX VALUE BY SINGLE BITS COUNT ////////////////////

TValue MaxSingleBitsTree(TTree tree);
TValue MaxSingleBitsList(TList list);

TValue Max(TValue a, TValue b)
{
    return (PopulationCount(a, ~0, UINT_SIZE) <= PopulationCount(b, ~0, UINT_SIZE)) ? b : a;
}

TValue MaxSingleBitsTree(TTree tree)
{
    if (IsEmptyTree(tree))
    {
        return 0;
    }
    
    return Max(tree->Value, MaxSingleBitsList(tree->Children));
}

TValue MaxSingleBitsList(TList list)
{
    if (IsEmptyList(list))
    {
        return 0;
    }
    
    return Max(MaxSingleBitsTree(list->Tree), MaxSingleBitsList(list->Next));
}

//////////////////// DESTROY ////////////////////

void DestroyList(TList* list);
void DestroyTree(TTree* tree);

void DestroyList(TList* list) 
{
    if(!IsEmptyList(*list))
    {
        DestroyList(&(*list)->Next);
        DestroyTree(&(*list)->Tree);
        free(*list);
    }
}

void DestroyTree(TTree* tree) 
{
    if(!IsEmptyTree(*tree))
    {
        DestroyList(&(*tree)->Children);
        free(*tree);
    }
}

//////////////////// MAIN ////////////////////

int main(void)
{
    TTree array1[] = {
        CreateTree(1, NULL), 
        CreateTree(2, NULL), 
        CreateTree(3, NULL)
    };
    
    TList list1 = ConvertArrayToList(3, array1);

    TTree array2[] = {
        CreateTree(4, NULL), 
        CreateTree(5, NULL)
    };
    
    TList list2 = ConvertArrayToList(2, array2);

    TTree array3[] = {
        CreateTree(6, list1),
        CreateTree(7, list2)      
    };

    TList list3 = ConvertArrayToList(2, array3);

    TTree tree = CreateTree(8, list3);

    printf("Max value by single bits count is %u", MaxSingleBitsTree(tree));

    DestroyTree(&tree);

    return EXIT_SUCCESS;
}