#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

struct TbinSearchTree
{
    TValue Value;
    struct TbinSearchTree* Left;
    struct TbinSearchTree* Right;
};

typedef struct TbinSearchTree* TBinSearchTree;

TBinSearchTree CreateTree()
{
    return NULL;
}

bool IsEmptyTree(TBinSearchTree tree)
{
    return tree == NULL;
}

void DestroyTree(TBinSearchTree* tree)
{
    if(!IsEmptyTree(*tree))
    {
        DestroyTree(&(*tree)->Left);
        DestroyTree(&(*tree)->Right);
        free(*tree);
        *tree = NULL;
    }
}

void InsertTree(TValue value, TBinSearchTree* tree)
{
    if(IsEmptyTree(*tree))
    {
        *tree = malloc(sizeof(**tree));
        assert(*tree != NULL);

        (*tree)->Value = value;
        (*tree)->Left = NULL;
        (*tree)->Right = NULL;

        return;
    }

    InsertTree(value, (value <= (*tree)->Value) ? &(*tree)->Left : &(*tree)->Right);
}

void ArrayToTree(size_t arraySize, TValue* array, TBinSearchTree* tree)
{
    for(size_t i = 0; i < arraySize; ++i)
    {
        InsertTree(array[i], tree);
    }
}

TBinSearchTree FindMaxTree(TBinSearchTree tree)
{
    if(IsEmptyTree(tree))
    {
        return tree;
    }
    else if(IsEmptyTree(tree->Right))
    {
        return tree;
    }

    return FindMaxTree(tree->Right);
}

TBinSearchTree FindSecondMaxTree(TBinSearchTree tree)
{
    if(IsEmptyTree(tree))
    {
        return NULL;
    }
    else if(IsEmptyTree(tree->Right) && !IsEmptyTree(tree->Left))
    {
        return FindMaxTree(tree->Left);
    }
    else if(IsEmptyTree(tree->Right->Right) && IsEmptyTree(tree->Right->Left))
    {
        return tree;
    }

    return FindSecondMaxTree(tree->Right);
}

void PrintTree(TBinSearchTree tree)
{
    if(IsEmptyTree(tree))
    {
        return;
    }

    PrintTree(tree->Left);
    printf("%d ", tree->Value);
    PrintTree(tree->Right);
}

int main(void)
{
    TBinSearchTree tree = CreateTree();
    TValue array[] = { 8, 4, 7, 1 };

    ArrayToTree(sizeof(array) / sizeof(*array), array, &tree);

    PrintTree(tree);
    printf("\n");
    printf("Second max is %d\n", FindSecondMaxTree(tree)->Value);
    DestroyTree(&tree);

    return EXIT_SUCCESS;
}