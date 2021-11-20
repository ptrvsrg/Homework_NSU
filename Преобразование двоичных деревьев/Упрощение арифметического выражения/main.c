#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct TbinTree
{
    char Value;
    struct TbinTree* Left;
    struct TbinTree* Right;
};

typedef struct TbinTree* TBinTree;

TBinTree CreateTree(char value, TBinTree left, TBinTree right)
{
    TBinTree tree = NULL;
    tree = malloc(sizeof(*tree));
    assert(tree);

    tree->Value = value;
    tree->Left = left;
    tree->Right = right;

    return tree;
}

bool IsOperator(char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
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
    if(!(*tree))
    {
        return;
    }
    if(IsOperator((*tree)->Value))
    {
        SimplifyExpression(&(*tree)->Left);
        SimplifyExpression(&(*tree)->Right);

        char left = (*tree)->Left->Value;
        char right = (*tree)->Right->Value;

        switch((*tree)->Value)
        {
            case '+':
                if(left == '0' || right == '0')
                {
                    DestroyTree(tree);
                    *tree = CreateTree((left == '0') ? right : left, NULL, NULL);
                }
                break;
            case '-':
                if(right == '0')
                {
                    DestroyTree(tree);
                    *tree = CreateTree(left, NULL, NULL);
                }
                break;
            case '*':
                if(left == '1' || right == '1')
                {
                    DestroyTree(tree);
                    *tree = CreateTree((left == '1') ? right : left, NULL, NULL);
                }
                else if(left == '0' || right == '0')
                {
                    DestroyTree(tree);
                    *tree = CreateTree('0', NULL, NULL);
                }
                break;
            case '/':
                assert(right != '0');

                if(right == '1')
                {
                    DestroyTree(tree);
                    *tree = CreateTree(left, NULL, NULL);
                }
                else if(left == '0')
                {
                    DestroyTree(tree);
                    *tree = CreateTree('0', NULL, NULL);
                }
        }
    }
    else
    {
        assert(!(*tree)->Left && !(*tree)->Right);
    }
}

int main()
{
    TBinTree tree1 = CreateTree('1', NULL, NULL);
    TBinTree tree2 = CreateTree('0', NULL, NULL);
    TBinTree tree3 = CreateTree('+', tree1, tree2);
    TBinTree tree4 = CreateTree('0', NULL, NULL);
    TBinTree tree5 = CreateTree('*', tree3, tree4);
    TBinTree tree6 = CreateTree('3', NULL, NULL);
    TBinTree tree7 = CreateTree('-', tree6, tree5);
    TBinTree tree8 = CreateTree('1', NULL, NULL);
    TBinTree tree9 = CreateTree('/', tree7, tree8);

    SimplifyExpression(&tree9);

    DestroyTree(&tree9);
}