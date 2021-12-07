#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int Max(int X, int Y)
{
    return X >= Y ? X : Y;
}

typedef int TValue;

struct TAVLtree
{
    TValue Value;
    int Depth;
    struct TAVLtree* Left;
    struct TAVLtree* Right;
};

typedef struct TAVLtree* TAVLTree;

bool IsEmpty(TAVLTree tree)
{
    return tree == NULL;
}

TAVLTree CreateLeaf(TValue value, TAVLTree left, TAVLTree right)
{
    TAVLTree new = malloc(sizeof(*new));
    assert(!IsEmpty(new));

    new->Depth = 1;
    new->Value = value;
    new->Left = left;
    new->Right = right;

    return new;
}

int GetDepth(TAVLTree tree)
{
    return !IsEmpty(tree) ? tree->Depth : 0;
}

int DepthDifference(TAVLTree tree)
{
    return GetDepth(tree->Right) - GetDepth(tree->Left);
}

void FixDepth(TAVLTree tree)
{
    tree->Depth = Max(GetDepth(tree->Left), GetDepth(tree->Right)) + 1;
}

TAVLTree RotateRight(TAVLTree tree)
{
    TAVLTree buffer = tree->Left;
    tree->Left = buffer->Right;
    buffer->Right = tree;

    FixDepth(tree);
    FixDepth(buffer);

    return buffer;
}

TAVLTree RotateLeft(TAVLTree tree)
{
    TAVLTree buffer = tree->Right;
    tree->Right = buffer->Left;
    buffer->Left = tree;

    FixDepth(tree);
    FixDepth(buffer);

    return buffer;
}

TAVLTree Balance(TAVLTree tree)
{
    FixDepth(tree);
    
    if(DepthDifference(tree) == 2)
    {
        if(DepthDifference(tree->Right) < 0)
        {
            tree->Right = RotateRight(tree->Right);
        }
        return RotateLeft(tree);
    }
    else if(DepthDifference(tree) == -2)
    {
        if(DepthDifference(tree->Left) > 0)
        {
            tree->Left = RotateLeft(tree->Left);
        }
        return RotateRight(tree);
    }

    return tree;
}

void Insert(TValue value, TAVLTree* tree)
{
    if(IsEmpty(*tree)) 
    {
        *tree = CreateLeaf(value, NULL, NULL);
    }
    else if(value < (*tree)->Value)   
    {
        Insert(value, &(*tree)->Left);
    }
    else
    {
        Insert(value, &(*tree)->Right);
    }

    *tree = Balance(*tree);
}

TAVLTree FindMin(TAVLTree tree)
{
    return !IsEmpty(tree->Left) ? FindMin(tree->Left) : tree;
}

void Remove(TValue value, TAVLTree* tree)
{
    if(IsEmpty(*tree))
    {}
    else if (value < (*tree)->Value)
    {
        Remove(value, &(*tree)->Left);
    }
    else if (value > (*tree)->Value)
    {
        Remove(value, &(*tree)->Right);
    }
    else if(!IsEmpty((*tree)->Left) && !IsEmpty((*tree)->Right))
    {
        (*tree)->Value = FindMin((*tree)->Right)->Value;
        Remove((*tree)->Value, &(*tree)->Right);
    }
    else
    {   
        TAVLTree remove = *tree;
        *tree = (!IsEmpty((*tree)->Left)) ? (*tree)->Left : (*tree)->Right;
        free(remove);
    }

    *tree = Balance(*tree);
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

void HelpPrintTree(char* tab, bool checkLeft, bool checkNextRight, TAVLTree tree)
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

void Print(TAVLTree tree)
{
    char tab[1000] = { 0 };
    HelpPrintTree(tab, true, tree->Right, tree);
}

void ConvertArrayToTree(size_t arraySize, TValue* array, TAVLTree* tree)
{
    for(size_t i = 0; i < arraySize; ++i)
    {
        Insert(array[i], tree);
    }
}

int main(void)
{
    TAVLTree tree = NULL;
    TValue array[] = { 1, 2, z};

    ConvertArrayToTree(sizeof(array) / sizeof(*array), array, &tree);
    Print(tree);
}