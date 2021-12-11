#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

int Max(int a, int b)
{
    return (a >= b) ? a : b;
}

struct TbinTree
{
    TValue Value;
    struct TbinTree* Left;
    struct TbinTree* Right;
};

typedef struct TbinTree* TBinTree;

bool IsEmptyTree(TBinTree tree)
{
    return tree == NULL;
}

TBinTree CreateLeaf(TValue value)
{
    TBinTree tree = malloc(sizeof(*tree));
    assert(!IsEmptyTree(tree));

    tree->Value = value;
    tree->Left = NULL;
    tree->Right = NULL;

    return tree;
}

TBinTree ConvertArrayToBinaryTree(int size, TValue* array)
{
    if (size <= 0) 
    {
        return NULL;
    }
    else 
    {
        int middle = size / 2;
        TBinTree tree = CreateLeaf(array[middle]);
        tree->Left = ConvertArrayToBinaryTree(middle, array);
        tree->Right = ConvertArrayToBinaryTree(size - middle - 1, array + middle + 1);
        return tree;
    }
}

int CalcDepth(TBinTree tree)
{
    if(IsEmptyTree(tree))
    {
        return 0;
    }

    return 1 + Max(CalcDepth(tree->Left), CalcDepth(tree->Right));
}

TValue CalcMax(TBinTree tree)
{
    assert(!IsEmptyTree(tree));

    TValue maxValue = tree->Value;

    if(tree->Left)
    {
        maxValue = Max(maxValue, CalcMax(tree->Left));
    }
    if(tree->Right)
    {
        maxValue = Max(maxValue, CalcMax(tree->Right));
    }

    return maxValue;
}

TValue CalcSum(TBinTree tree)
{
    if(IsEmptyTree(tree))
    {
        return 0;
    }

    return tree->Value + CalcSum(tree->Left) + CalcSum(tree->Right);
}

void DestroyTree(TBinTree* tree)
{
    if(!IsEmptyTree(*tree))
    {
        DestroyTree(&(*tree)->Left);
        DestroyTree(&(*tree)->Right);
        free(*tree);
    }
}

int main()
{
    TValue array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    TBinTree tree = ConvertArrayToBinaryTree(sizeof(array) / sizeof(*array), array);

    printf("Depth is %d\n", CalcDepth(tree));
    printf("Sum is %d\n", CalcSum(tree));
    printf("Max value is %d", CalcMax(tree));

    DestroyTree(&tree);
}