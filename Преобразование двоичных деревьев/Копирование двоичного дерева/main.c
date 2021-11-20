#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

struct TbinTree
{
    TValue Value;
    struct TbinTree* Left;
    struct TbinTree* Right;
};

typedef struct TbinTree* TBinTree;

TBinTree CreateTree(TValue value, TBinTree left, TBinTree right)
{
    TBinTree tree;
    tree = malloc(sizeof(*tree));
    assert(tree);

    tree->Value = value;
    tree->Left = left;
    tree->Right = right;

    return tree;
}

void ArrayToBinTree(size_t size, TValue* array, TBinTree* tree)
{
    if (size == 0) 
    {
        return;
    }

    *tree = CreateTree(array[size / 2], NULL, NULL);

    ArrayToBinTree(size / 2, array, &(*tree)->Left);
    ArrayToBinTree(size - (size / 2 + 1), array + size / 2 + 1, &(*tree)->Right);
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

TBinTree CopyTree(TBinTree tree)
{
    if(!tree)
    {
        return NULL;
    }

    TBinTree copyTree = CreateTree(tree->Value, CopyTree(tree->Left), CopyTree(tree->Right));
}

int main()
{
    TBinTree tree;
    TValue array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ArrayToBinTree(sizeof(array) / sizeof(*array), array, &tree);

    TBinTree copy = CopyTree(tree);

    DestroyTree(&tree);
    DestroyTree(&copy);
}