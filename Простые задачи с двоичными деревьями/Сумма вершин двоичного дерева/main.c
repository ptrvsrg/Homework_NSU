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

TBinTree CreateTree()
{
    return NULL;
}

void ArrayToBinTree(size_t size, TValue* array, TBinTree* tree)
{
    if (size == 0) 
    {
        return;
    }

    *tree = malloc(sizeof(**tree));
    assert(*tree);

    (*tree)->Value = array[size / 2];
    (*tree)->Left = NULL;
    (*tree)->Right = NULL;

    ArrayToBinTree(size / 2, array, &(*tree)->Left);
    ArrayToBinTree(size - (size / 2 + 1), array + size / 2 + 1, &(*tree)->Right);
}

int CalcDepth(TBinTree tree)
{
    if(!tree)
    {
        return 0;
    }

    return 1 + Max(CalcDepth(tree->Left), CalcDepth(tree->Right));
}

TValue CalcMax(TBinTree tree)
{
    assert(tree);

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
    if(!tree)
    {
        return 0;
    }

    return tree->Value + CalcSum(tree->Left) + CalcSum(tree->Right);
}

void DestroyTree(TBinTree* tree)
{
    if(*tree)
    {
        DestroyTree(&(*tree)->Left);
        DestroyTree(&(*tree)->Right);
        free(*tree);
    }
}

int main()
{
    TBinTree tree = CreateTree();
    TValue array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ArrayToBinTree(sizeof(array) / sizeof(*array), array, &tree);

    printf("Depth is %d\n", CalcDepth(tree));
    printf("Sum is %d\n", CalcSum(tree));
    printf("Max value is %d", CalcMax(tree));

    DestroyTree(&tree);
}