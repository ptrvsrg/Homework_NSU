#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

struct TAVLtree
{
    TValue Value;
    struct TAVLtree* Left;
    struct TAVLtree* Right;
};

typedef struct TAVLtree* TAVLTree;

bool IsEmpty(const TAVLTree tree)
{
    return tree == NULL;
}

TAVLTree CreateLeaf(TValue value)
{
    TAVLTree new = malloc(sizeof(*new));
    assert(!IsEmpty(new));

    new->Value = value;
    new->Left = NULL;
    new->Right = NULL;

    return new;
}
TAVLTree CreateMinTreeByHeight(int height, TValue* minValue)
{
    if(height <= 0)
    {
        return NULL;
    }

    TAVLTree left = CreateMinTreeByHeight(height - 2, minValue);
    TAVLTree tree = CreateLeaf(*minValue);
    ++(*minValue);
    tree->Left = left;
    tree->Right = CreateMinTreeByHeight(height - 1, minValue);

    return tree;
}

void DestroyTree(TAVLTree* tree)
{
    if(*tree)
    {
        DestroyTree(&(*tree)->Left);
        DestroyTree(&(*tree)->Right);
        free(*tree);
    }
}

int main(void)
{
    int minValue = 1;
    TAVLTree tree = CreateMinTreeByHeight(10, &minValue);
    DestroyTree(&tree);
}