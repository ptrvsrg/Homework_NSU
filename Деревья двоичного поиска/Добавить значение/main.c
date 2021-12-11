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

bool IsEmptyTree(TBinSearchTree tree)
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
    TValue array[] = { 1, 2, 4, 7, 9 };

    TBinSearchTree tree = ConvertArrayToBinarySearchTree(sizeof(array) / sizeof(*array), array);

    PrintTree(tree);
    printf("\n");
    InsertTree(5, &tree);
    PrintTree(tree);
    DestroyTree(&tree);

    return EXIT_SUCCESS;
}