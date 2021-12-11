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

TBinSearchTree ConvertArrayToBinarySearchTree(int size, TValue* array)
{
    if (size <= 0) 
    {
        return NULL;
    }
    else 
    {
        int middle = size / 2;
        TBinSearchTree tree = CreateLeaf(array[middle]);
        tree->Left = ConvertArrayToBinarySearchTree(middle, array);
        tree->Right = ConvertArrayToBinarySearchTree(size - middle - 1, array + middle + 1);
        return tree;
    }
}

void PrintTree(const TBinSearchTree tree)
{
    if(!IsEmptyTree(tree))
    {
        PrintTree(tree->Left);
        printf("%d ", tree->Value);
        PrintTree(tree->Right);
    }
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

TList CreateList(TValue value)
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
    TList new = CreateList(value);
    new->Next = *list;
    *list = new;
}

void ConvertBinarySearchTreeToIncreasingList(const TBinSearchTree tree, TList* list)
{
    if(IsEmptyTree(tree))
    {
        return;
    }

    ConvertBinarySearchTreeToIncreasingList(tree->Right, list);
    PushList(tree->Value, list);
    ConvertBinarySearchTreeToIncreasingList(tree->Left, list);
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
    TValue array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    TBinSearchTree tree = ConvertArrayToBinarySearchTree(sizeof(array) / sizeof(*array), array);
    TList list = NULL;
    ConvertBinarySearchTreeToIncreasingList(tree, &list);

    PrintTree(tree);
    printf("\n");

    PrintList(list);
    printf("\n");

    DestroyTree(&tree);
    DestroyList(&list);
    return EXIT_SUCCESS;
}