#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

////////////////////////////////  LIST  ////////////////////////////////

struct Tlist 
{
    TValue Value;
    struct Tlist* Next;
};

typedef struct Tlist* TList;

bool IsEmptyList(const TList list)
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

TValue PopList(TList* list)
{
    assert(!IsEmptyList(*list));

    TValue top = (*list)->Value;
    TList removeList = *list;
    *list = (*list)->Next;
    free(removeList);
    return top;
}

void PushList(TValue value, TList* list)
{
    TList new = CreateItem(value);
    new->Next = *list;
    *list = new;
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

void PrintList(const TList list)
{
    if(IsEmptyList(list))
    {
        return;
    }

    printf("%d ", list->Value);
    PrintList(list->Next);
}

void DestroyList(TList* list) 
{
    while (!IsEmptyList(*list)) 
    {
        PopList(list);
    }
}

////////////////////////////////  BINARY TREE  ////////////////////////////////

struct TbinSearchTree
{
    TValue Value;
    struct TbinSearchTree* Left;
    struct TbinSearchTree* Right;
};

typedef struct TbinSearchTree* TBinSearchTree;

bool IsEmptyTree(const TBinSearchTree tree)
{
    return tree == NULL;
}

TBinSearchTree CreateLeaf(TValue value)
{
    TBinSearchTree tree = malloc(sizeof(*tree));
    assert(!IsEmptyTree(tree));

    tree->Value = value;
    tree->Left = NULL;
    tree->Right = NULL;

    return tree;
}

void InsertTree(TValue value, TBinSearchTree* tree)
{
    if(IsEmptyTree(*tree))
    {
        *tree = CreateLeaf(value);
        return;
    }

    InsertTree(value, value <= (*tree)->Value ? &(*tree)->Left : &(*tree)->Right);
}

TBinSearchTree ConvertDecreasingListToBinarySearchTree(int listSize, TList* list)
{
    if(listSize == 0)
    {
        return NULL;
    }

    int newSize = listSize / 2;
    TBinSearchTree tree = CreateLeaf(0);
    tree->Right = ConvertDecreasingListToBinarySearchTree(newSize, list);
    tree->Value = PopList(list);
    tree->Left = ConvertDecreasingListToBinarySearchTree(listSize - newSize - 1, list);

    return tree;
}

void DestroyTree(TBinSearchTree* tree)
{
    if(!IsEmptyTree(*tree))
    {
        DestroyTree(&(*tree)->Left);
        DestroyTree(&(*tree)->Right);
        free(*tree);
    }
}

void PrintTree(const TBinSearchTree tree)
{
    if (IsEmptyTree(tree))
    {
        return;
    }

    PrintTree(tree->Left);
    printf("%d ", tree->Value);
    PrintTree(tree->Right);
}

int main(void)
{
    TValue array[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    int arraySize = sizeof(array) / sizeof(*array);

    TList list = ConvertArrayToList(arraySize, array);
    PrintList(list);
    printf("\n");

    TBinSearchTree tree = ConvertDecreasingListToBinarySearchTree(arraySize, &list);
    PrintTree(tree);
    printf("\n");

    DestroyTree(&tree);
    DestroyList(&list);
    return EXIT_SUCCESS;
}