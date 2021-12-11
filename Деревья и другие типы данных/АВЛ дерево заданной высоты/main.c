#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

struct TBinSearchtree
{
    TValue Value;
    struct TBinSearchtree* Left;
    struct TBinSearchtree* Right;
};

typedef struct TBinSearchtree* TBinSearchTree;

bool IsEmptyTree(const TBinSearchTree tree)
{
    return tree == NULL;
}

TBinSearchTree CreateLeaf(TValue value)
{
    TBinSearchTree new = malloc(sizeof(*new));
    assert(!IsEmptyTree(new));

    new->Value = value;
    new->Left = NULL;
    new->Right = NULL;

    return new;
}

TBinSearchTree CreateMinTreeByHeight(int height, TValue* minValue)
{
    if(height <= 0)
    {
        return NULL;
    }

    TBinSearchTree left = CreateMinTreeByHeight(height - 2, minValue);
    TBinSearchTree tree = CreateLeaf(*minValue);
    ++(*minValue);
    tree->Left = left;
    tree->Right = CreateMinTreeByHeight(height - 1, minValue);

    return tree;
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

int main(void)
{
    int minValue = 1;
    TBinSearchTree tree = CreateMinTreeByHeight(5, &minValue);
    PrintTree(tree);
    DestroyTree(&tree);
}