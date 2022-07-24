#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define UNUSED(x) (void)(x);

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

int ConvertBinarySearchTreeToArray(const TBinSearchTree tree, TValue* array, int count) 
{
    if (IsEmptyTree(tree)) 
    {
        return count;
    } 
    else 
    {
        count = ConvertBinarySearchTreeToArray(tree->Left, array, count);

        array[count] = tree->Value;
        ++count;

        return ConvertBinarySearchTreeToArray(tree->Right, array, count);
    }
}

void PrintArray(int arraySize, const int* array)
{
    for(int i = 0; i < arraySize; ++i)
    {
        printf("%d ", array[i]);
    }
}

int main(void)
{
    TBinSearchTree tree = NULL;
    TValue array1[] = { 9, 6, 4, 11, 15 };

    ConvertArrayToBinarySearchTree(sizeof(array1) / sizeof(*array1), array1, &tree);

    int arraySize1 = SizeTree(tree);
    TValue* array2 = calloc(arraySize1, sizeof(*array2));
    assert(array2 != NULL);

    int arraySize2 = ConvertBinarySearchTreeToArray(tree, array2, 0);
    UNUSED(arraySize2);
    assert(arraySize1 == arraySize2);

    PrintTree(tree);
    printf("\n");
    PrintArray(arraySize1, array2);
    printf("\n");

    free(array2);
    DestroyTree(&tree);
    return EXIT_SUCCESS;
}