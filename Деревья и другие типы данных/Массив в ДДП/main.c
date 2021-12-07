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

int SizeTree(const TBinSearchTree tree)
{
    if (IsEmptyTree(tree))
    {
        return 0;
    }

    return 1 + SizeTree(tree->Left) + SizeTree(tree->Right);
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

void PrintArray(int arraySize, int* array)
{
    for(int i = 0; i < arraySize; ++i)
    {
        printf("%d ", array[i]);
    }
}

TBinSearchTree ConvertArrayToBinarySearchTree(TValue array[], int left, int right)
{
    if (left > right) 
    {
        return NULL;
    }
    else 
    {
        int middle = (left + right) / 2;
        TBinSearchTree tree = CreateLeaf(array[middle]);
        tree->Left = ConvertArrayToBinarySearchTree(array, left, middle - 1);
        tree->Right = ConvertArrayToBinarySearchTree(array, middle + 1, right);
        return tree;
    }
}

int main(void)
{
    
    TValue array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int arraySize = sizeof(array) / sizeof(*array);

    TBinSearchTree tree = ConvertArrayToBinarySearchTree(array, 0, arraySize - 1);

    PrintArray(arraySize, array);
    printf("\n");
    PrintTree(tree);
    printf("\nLeft size = %d\n", SizeTree(tree->Left));
    printf("Right size = %d\n", SizeTree(tree->Right));

    DestroyTree(&tree);
    return EXIT_SUCCESS;
}