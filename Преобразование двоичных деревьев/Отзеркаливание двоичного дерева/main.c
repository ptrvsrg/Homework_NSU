#define _CRT_SECURE_NO_WARNINGS
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

TBinTree CreateTree(TValue value, TBinTree left, TBinTree right)
{
    TBinTree tree = NULL;
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

void Swap(TBinTree* tree1, TBinTree* tree2)
{
    TBinTree buffer = *tree1;
    *tree1 = *tree2;
    *tree2 = buffer;
}

void MirrorTree(TBinTree* tree)
{
    if(!(*tree))
    {
        return;
    }

    Swap(&(*tree)->Left, &(*tree)->Right);
    MirrorTree(&(*tree)->Left);
    MirrorTree(&(*tree)->Right);
}

void PrintTabulation(char* tab, bool checkLeft, bool checkNextRight)
{
    if (*tab != '\0')
    {
        if (!checkLeft || !checkNextRight)
        {
            printf("%s%c%c%c%c ", tab + 5, 192, 196, 196, 196);
        }
        else
        {
            printf("%s%c%c%c%c ", tab + 5, 195, 196, 196, 196); 
        }
    }
}

void HelpPrintTree(char* tab, bool checkLeft, bool checkNextRight, TBinTree tree)
{
    if(tree)
    {
        PrintTabulation(tab, checkLeft, checkNextRight);
        printf("%d\n", tree->Value);

        char newTab[1000] = { 0 };
        
        if (!checkLeft)
        {
            sprintf(tab, "%s     ", tab);
            sprintf(newTab, "%s", tab);
        }
        else
        {
            sprintf(tab, "%s%c    ", tab, 179);
            sprintf(newTab, "%s", tab);
        }
        
        HelpPrintTree(tab, true, tree->Right, tree->Left);
        HelpPrintTree(newTab, false, tree->Right, tree->Right);
    }
}

void PrintTree(TBinTree tree)
{
    char tab[1000] = { 0 };
    HelpPrintTree(tab, true, tree->Right, tree);
}

int main()
{
    TBinTree tree;
    TValue array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ArrayToBinTree(sizeof(array) / sizeof(*array), array, &tree);

    PrintTree(tree);
    MirrorTree(&tree);
    PrintTree(tree);

    DestroyTree(&tree);
}