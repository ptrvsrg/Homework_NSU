#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef char TValue;
struct TbinTree
{
    TValue Value;
    struct TbinTree* Left;
    struct TbinTree* Right;
};

typedef struct TbinTree* TBinTree;

TBinTree CreateLeaf(TValue value, TBinTree left, TBinTree right)
{
    TBinTree tree = NULL;
    tree = malloc(sizeof(*tree));
    assert(tree);

    tree->Value = value;
    tree->Left = left;
    tree->Right = right;

    return tree;
}

bool IsEmptyTree(TBinTree tree)
{
    return tree == NULL;
}

bool IsOperator(TValue symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

void RemoveBranch(bool isLeft, TBinTree* tree)
{
    TBinTree delete = *tree;
    free((isLeft) ? (*tree)->Left : (*tree)->Right);
    *tree = (isLeft) ? (*tree)->Right : (*tree)->Left;
    free(delete);
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

void SimplifyExpression(TBinTree* tree)
{
    if(IsEmptyTree(*tree))
    {
        return;
    }
    if(IsOperator((*tree)->Value))
    {
        SimplifyExpression(&(*tree)->Left);
        SimplifyExpression(&(*tree)->Right);

        TValue left = (*tree)->Left->Value;
        TValue right = (*tree)->Right->Value;

        switch((*tree)->Value)
        {
            case '+':
                if(left == '0' || right == '0')
                {
                    RemoveBranch(left == '0', tree);
                }
                break;
            case '-':
                if(right == '0')
                {
                    RemoveBranch(false, tree);
                }
                break;
            case '*':
                if(left == '1' || right == '1')
                {
                    RemoveBranch(left == '1', tree);
                }
                else if(left == '0' || right == '0')
                {
                    DestroyTree(tree);
                    *tree = CreateLeaf('0', NULL, NULL);
                }
                break;
            case '/':
                assert(right != '0');

                if(right == '1')
                {
                    RemoveBranch(false, tree);
                }
                else if(left == '0')
                {
                    DestroyTree(tree);
                    *tree = CreateLeaf('0', NULL, NULL);
                }
        }
    }
    else
    {
        assert(IsEmptyTree((*tree)->Left) && IsEmptyTree((*tree)->Right));
    }
}

int main()
{
    TBinTree tree1 = CreateLeaf('1', NULL, NULL);
    TBinTree tree2 = CreateLeaf('0', NULL, NULL);
    TBinTree tree3 = CreateLeaf('+', tree1, tree2);
    TBinTree tree4 = CreateLeaf('0', NULL, NULL);
    TBinTree tree5 = CreateLeaf('*', tree3, tree4);
    TBinTree tree6 = CreateLeaf('3', NULL, NULL);
    TBinTree tree7 = CreateLeaf('-', tree6, tree5);
    TBinTree tree8 = CreateLeaf('2', NULL, NULL);
    TBinTree tree9 = CreateLeaf('/', tree7, tree8);

    SimplifyExpression(&tree9);

    DestroyTree(&tree9);
}