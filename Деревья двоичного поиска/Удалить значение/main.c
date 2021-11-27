#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

TValue Max(TValue first, TValue second)
{
    return (first < second) ? second : first;
}

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

TBinSearchTree FindMinTree(TBinSearchTree tree)
{
    if(IsEmptyTree(tree))
    {
        return tree;
    }
    else if(IsEmptyTree(tree->Left))
    {
        return tree;
    }

    return FindMinTree(tree->Left);
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

TBinSearchTree Find(TValue value, TBinSearchTree tree)
{
    if(IsEmptyTree(tree))
    {
        return NULL;
    }
    else if(tree->Value == value)
    {
        return tree;
    }

    return Find(value, (value <= tree->Value) ? tree->Left : tree->Right);
}

void DeleteTree(TValue value, TBinSearchTree* tree)
{
    if(IsEmptyTree(*tree))
    {
        return;
    }

    if (value < (*tree)->Value)
    {
        DeleteTree(value, &(*tree)->Left);
    }
    else if (value > (*tree)->Value)
    {
        DeleteTree(value, &(*tree)->Right);
    }
    else if(!IsEmptyTree((*tree)->Left) && !IsEmptyTree((*tree)->Right))
    {
        (*tree)->Value = FindMaxTree((*tree)->Left)->Value;
        DeleteTree((*tree)->Value, &(*tree)->Left);
    }
    else
    {   
        TBinSearchTree deleteLeaf = *tree;
        *tree = (!IsEmptyTree((*tree)->Left)) ? (*tree)->Left : (*tree)->Right;
        free(deleteLeaf);
    }
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
    TValue array[] = { 3, 2, 8, 9, 4, 7, 1 };

    ArrayToTree(sizeof(array) / sizeof(*array), array, &tree);

    PrintTree(tree);
    printf("\n");
    DeleteTree(3, &tree);
    PrintTree(tree);

    return EXIT_SUCCESS;
}