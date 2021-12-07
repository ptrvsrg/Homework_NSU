#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

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

void ConvertArrayToBinarySearchTree(int arraySize, const TValue* array, TBinSearchTree* tree)
{
    for(int i = 0; i < arraySize; ++i)
    {
        InsertTree(array[i], tree);
    }
}

void PrintTree(const TBinSearchTree tree)
{
    if(IsEmptyTree(tree))
    {
        return;
    }

    PrintTree(tree->Left);
    printf("%d ", tree->Value);
    PrintTree(tree->Right);
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
    TList new = malloc(sizeof(*new));
    assert(!IsEmptyList(new));

    new->Value = value;
    new->Next = *list;
    *list = new;
}

void ConvertBinarySearchTreeToList(const TBinSearchTree tree, TList* list)
{
    if(IsEmptyTree(tree))
    {
        return;
    }

    ConvertBinarySearchTreeToList(tree->Right, list);
    PushList(tree->Value, list);
    ConvertBinarySearchTreeToList(tree->Left, list);
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

int main(void)
{
    TBinSearchTree tree = NULL;
    TList list = NULL;
    TValue array[] = { 4, 5, 9, 6, 7, 2, 3, 1, 0, 8 };

    ConvertArrayToBinarySearchTree(sizeof(array) / sizeof(*array), array, &tree);
    ConvertBinarySearchTreeToList(tree, &list);

    PrintTree(tree);
    printf("\n");

    PrintList(list);
    printf("\n");

    DestroyTree(&tree);
    DestroyList(&list);
    return EXIT_SUCCESS;
}