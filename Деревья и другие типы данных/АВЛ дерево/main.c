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
    int Height;
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

    new->Height = 1;
    new->Value = value;
    new->Left = left;
    new->Right = right;

    return new;
}

int GetHeight(TAVLTree tree)
{
    return !IsEmpty(tree) ? tree->Height : 0;
}

int HeightDifference(TAVLTree tree)
{
    return GetHeight(tree->Right) - GetHeight(tree->Left);
}

void FixHeight(TAVLTree tree)
{
    tree->Height = Max(GetHeight(tree->Left), GetHeight(tree->Right)) + 1;
}

TAVLTree RotateRight(TAVLTree tree)
{
    TAVLTree buffer = tree->Left;
    tree->Left = buffer->Right;
    buffer->Right = tree;

    FixHeight(tree);
    FixHeight(buffer);

    return buffer;
}

TAVLTree RotateLeft(TAVLTree tree)
{
    TAVLTree buffer = tree->Right;
    tree->Right = buffer->Left;
    buffer->Left = tree;

    FixHeight(tree);
    FixHeight(buffer);

    return buffer;
}

TAVLTree Balance(TAVLTree tree)
{
    FixHeight(tree);
    
    if(HeightDifference(tree) == 2)
    {
        if(HeightDifference(tree->Right) < 0)
        {
            tree->Right = RotateRight(tree->Right);
        }
        return RotateLeft(tree);
    }
    else if(HeightDifference(tree) == -2)
    {
        if(HeightDifference(tree->Left) > 0)
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
        printf("%d (%d)\n", tree->Value, tree->Height);

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
    TValue array[] = { 3, 9, 5, 1, 0, 6, 4, 8, 7, 2 };

    ConvertArrayToTree(sizeof(array) / sizeof(*array), array, &tree);
    Print(tree);
}